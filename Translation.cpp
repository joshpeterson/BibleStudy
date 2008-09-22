#include <fstream>
#include <string>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/iostreams/code_converter.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include "Translation.h"
#include "Verse.h"
#include "TranslationBufferNoWarnings.pb.h"

void Translation::search(std::vector<boost::shared_ptr<ISearchResults> >& results) const
{
    partial_search(m_verses.begin(), m_verses.end(), results[0]);
}

void Translation::partial_search(std::vector< boost::shared_ptr<IVerse> >::const_iterator begin, 
                                 std::vector< boost::shared_ptr<IVerse> >::const_iterator end,
                                 boost::shared_ptr<ISearchResults> query) const
{
    for (std::vector< boost::shared_ptr<IVerse> >::const_iterator it = begin;
         it != end;
         ++it)
    {
        (*it)->match(query);
    }
}

std::vector<boost::shared_ptr<const IVerse> > Translation::get_entry(int unique_id, int num_entries_context) const
{
    size_t requested_lower_bound = unique_id - num_entries_context;
    size_t lower_bound =  requested_lower_bound >= 0 ? requested_lower_bound : 0;
 
    size_t requested_upper_bound = unique_id + num_entries_context + 1;
    size_t upper_bound = requested_upper_bound <= (m_verses.size()-1) ? requested_upper_bound : (m_verses.size()-1);

    std::vector<boost::shared_ptr<const IVerse> > verses;
    std::copy(&m_verses[lower_bound], &m_verses[upper_bound], std::back_inserter(verses));

    return verses;
}

bool Translation::Save(const std::string &filename)
{
    BibleStudy::TranslationBuffer buffer;
    buffer.set_long_name(m_long_name);
    buffer.set_short_name(m_short_name);

    for (std::vector< boost::shared_ptr<IVerse> >::const_iterator it = m_verses.begin();
         it != m_verses.end();
         ++it)
    {
        BibleStudy::VerseBuffer* verse_buffer = buffer.add_verse();
        verse_buffer->set_book((*it)->get_book());
        verse_buffer->set_chapter((*it)->get_chapter());
        verse_buffer->set_verse((*it)->get_verse());
        verse_buffer->set_text((*it)->get_text());
        verse_buffer->set_unique_id((*it)->get_unqiue_id());
    }

    std::fstream output(filename.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
    if (!buffer.SerializeToOstream(&output))
        return false;
    output.close();

    return true;
}

bool Translation::Resume(const std::string &filename)
{
    BibleStudy::TranslationBuffer buffer;

    std::fstream input(filename.c_str(), std::ios::in | std::ios::binary);
    if (!input || !buffer.ParseFromIstream(&input)) 
        return false;

    input.close();

    m_long_name = buffer.long_name();
    m_short_name = buffer.short_name();

    int num_verses = buffer.verse_size();
    for (int i = 0; i < num_verses; ++i)
    {
        BibleStudy::VerseBuffer verse_buffer = buffer.verse(i);
        boost::shared_ptr<Verse> verse(new Verse(verse_buffer.book(), verse_buffer.chapter(),
                                                 verse_buffer.verse(), verse_buffer.text(),
                                                 verse_buffer.unique_id()));
        m_verses.push_back(verse);
    }

    return true;
}

// Free functions
std::string verse_collection_to_string(const std::vector<boost::shared_ptr<const IVerse> >& verse_collection)
{
    std::string verse_string;

    std::vector<boost::shared_ptr<const IVerse> >::const_iterator it = verse_collection.begin();
    std::vector<boost::shared_ptr<const IVerse> >::const_iterator end = verse_collection.end();
    for (; it != end; ++it)
    {
        verse_string += (*it)->get_text();
        if (std::distance(it, end) != 1)
            verse_string += " ";
    }

    return verse_string;
}

std::string verse_collection_title(const std::vector<boost::shared_ptr<const IVerse> >& verse_collection)
{
    std::string title;

    std::string cur_book;
    int cur_chapter = 0;
    int cur_verse = 0;
    int last_verse = 0;

    std::vector<boost::shared_ptr<const IVerse> >::const_iterator it = verse_collection.begin();
    std::vector<boost::shared_ptr<const IVerse> >::const_iterator end = verse_collection.end();
    for (; it != end; ++it)
    {
        if (cur_book.size() == 0)
        {
            title += (*it)->get_book() + " ";
            cur_book = (*it)->get_book();
            cur_chapter = 0;
        }
        else if (cur_book != (*it)->get_book())
        {
            title += ";";
            title += (*it)->get_book() + " ";
            cur_book = (*it)->get_book();
            cur_chapter = 0;
        }
        
        if (cur_chapter == 0)
        {
            title += boost::lexical_cast<std::string>((*it)->get_chapter()) + ":";
            cur_chapter = (*it)->get_chapter();
            cur_verse = 0;
        }
        else if (cur_chapter != (*it)->get_chapter())
        {
            if (cur_verse != last_verse)
            {
                title += "-";
                title += boost::lexical_cast<std::string>(cur_verse);
                last_verse = cur_verse;
            }

            title += ",";
            title += boost::lexical_cast<std::string>((*it)->get_chapter()) + ":";
            cur_chapter = (*it)->get_chapter();
            cur_verse = 0;
        }

        if (cur_verse == 0)
        {
            title += boost::lexical_cast<std::string>((*it)->get_verse());
            cur_verse = (*it)->get_verse();
            last_verse = cur_verse;
        }
        else if (cur_verse != (*it)->get_verse())
        {
            cur_verse = (*it)->get_verse();
        }
    }

    if (cur_verse != 0 && it != verse_collection.begin())
    {
        if (cur_verse != last_verse)
        {
            title += "-";
            title += boost::lexical_cast<std::string>((*--it)->get_verse());
        }
    }

    return title;
}

