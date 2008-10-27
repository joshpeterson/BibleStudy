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
    int requested_lower_bound = unique_id - num_entries_context;
    int lower_bound =  requested_lower_bound >= 0 ? requested_lower_bound : 0;
 
    int requested_upper_bound = unique_id + num_entries_context + 1;
    int upper_bound = requested_upper_bound <= static_cast<int>(m_verses.size()-1) ? requested_upper_bound : (m_verses.size()-1);

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

    m_meta_data = std::vector< boost::shared_ptr< std::vector<int> > >();

    std::string cur_book;
    int cur_chapter = 0;
    int num_verses_in_chapter = 0;
    boost::shared_ptr< std::vector<int> > cur_book_meta_data;

    int num_verses = buffer.verse_size();
    for (int i = 0; i < num_verses; ++i)
    {
        BibleStudy::VerseBuffer verse_buffer = buffer.verse(i);
        boost::shared_ptr<Verse> verse(new Verse(verse_buffer.book(), verse_buffer.chapter(),
                                                 verse_buffer.verse(), verse_buffer.text(),
                                                 verse_buffer.unique_id()));
        m_verses.push_back(verse);

        if (cur_book == "" || cur_book != verse_buffer.book())
        {
            if (cur_book_meta_data != NULL)
                m_meta_data.push_back(cur_book_meta_data);

            cur_book_meta_data = boost::shared_ptr< std::vector<int> >(new std::vector<int>());
            cur_chapter = 0;
            num_verses_in_chapter = 0;
         
            cur_book = verse_buffer.book();
            cur_chapter++;
            num_verses_in_chapter++;
        }
        else if (cur_chapter == 0 || cur_chapter != verse_buffer.chapter())
        {
            if (num_verses_in_chapter != 0)
                cur_book_meta_data->push_back(num_verses_in_chapter);

            num_verses_in_chapter = 0;

            cur_chapter++;
            num_verses_in_chapter++;
        }
        else
        {
            num_verses_in_chapter++;
        }
    }

    return true;
}

int Translation::num_books() const
{
    return static_cast<int>(m_meta_data.size());
}

int Translation::num_chapters(int book_index) const
{
    if (book_index >= 0 && book_index < num_books())
        return static_cast<int>(m_meta_data[book_index]->size());

    return -1;
}

int Translation::num_verses(int book_index, int chapter_index) const
{
    if (book_index >= 0 && book_index < num_books() &&
        chapter_index >=0 && chapter_index < m_meta_data[book_index]->size())
        return m_meta_data[book_index]->at(chapter_index);

    return -1;
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

