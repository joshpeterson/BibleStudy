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
#include "VerseTreeItem.h"

using namespace BibleStudy;

void Translation::search(std::vector<boost::shared_ptr<ISearchResults> >& results) const
{
    partial_search(m_verses.begin(), m_verses.end(), results[0]);
}

void Translation::partial_search(std::vector< boost::shared_ptr<Verse> >::const_iterator begin, 
                                 std::vector< boost::shared_ptr<Verse> >::const_iterator end,
                                 boost::shared_ptr<ISearchResults> query) const
{
    for (std::vector< boost::shared_ptr<Verse> >::const_iterator it = begin;
         it != end;
         ++it)
    {
        if ((*it)->match(query))
        {
            query->add_matching_verse(m_long_name, (*it)->get_unique_id());
        }
    }
}

std::vector<boost::shared_ptr<const Verse> > Translation::get_entry(int unique_id, int num_entries_context) const
{
    int requested_lower_bound = unique_id - num_entries_context;
    int lower_bound =  requested_lower_bound >= 0 ? requested_lower_bound : 0;
 
    int requested_upper_bound = unique_id + num_entries_context + 1;
    int upper_bound = requested_upper_bound <= static_cast<int>(m_verses.size()-1) ? requested_upper_bound : (m_verses.size()-1);

    std::vector<boost::shared_ptr<const Verse> > verses;
    std::copy(&m_verses[lower_bound], &m_verses[upper_bound], std::back_inserter(verses));

    return verses;
}

bool Translation::Save(const std::string &filename)
{
    BibleStudy::TranslationBuffer buffer;
    buffer.set_long_name(m_long_name);
    buffer.set_short_name(m_short_name);

    for (std::vector< boost::shared_ptr<Verse> >::const_iterator it = m_verses.begin();
         it != m_verses.end();
         ++it)
    {
        BibleStudy::VerseBuffer* verse_buffer = buffer.add_verse();
        verse_buffer->set_book((*it)->get_book());
        verse_buffer->set_chapter((*it)->get_chapter());
        verse_buffer->set_verse((*it)->get_verse());
        verse_buffer->set_text((*it)->get_text());
        verse_buffer->set_unique_id((*it)->get_unique_id());
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

    m_verse_tree = boost::shared_ptr<VerseTreeItem>(new VerseTreeItem(m_long_name, 0));
    VerseTreeItem* cur_verse_tree_root = m_verse_tree.get();
    //m_verse_tree = boost::shared_ptr<VerseTreeItem>(new VerseTreeItem("", -1));

    //boost::shared_ptr<VerseTreeItem> translation_item = boost::shared_ptr<VerseTreeItem>(new VerseTreeItem(m_long_name, 0));
    //m_verse_tree->add_child(translation_item, VerseTreeItem::translation);
    //VerseTreeItem* cur_verse_tree_root = translation_item.get();

    std::string cur_book;
    int cur_chapter = 0;

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
            cur_book = verse_buffer.book();
            cur_chapter = 1;

            if (cur_verse_tree_root->get_parent() != NULL && cur_verse_tree_root->get_parent()->get_parent() != NULL)
                cur_verse_tree_root = cur_verse_tree_root->get_parent()->get_parent();

            boost::shared_ptr<VerseTreeItem> book = boost::shared_ptr<VerseTreeItem>(new VerseTreeItem(m_long_name, i));
            cur_verse_tree_root->add_child(book, VerseTreeItem::book);

            cur_verse_tree_root = book.get();

            boost::shared_ptr<VerseTreeItem> chapter = boost::shared_ptr<VerseTreeItem>(new VerseTreeItem(m_long_name, i));
            cur_verse_tree_root->add_child(chapter, VerseTreeItem::chapter);
            
            cur_verse_tree_root = chapter.get();

            boost::shared_ptr<VerseTreeItem> verse = boost::shared_ptr<VerseTreeItem>(new VerseTreeItem(m_long_name, i));
            cur_verse_tree_root->add_child(verse, VerseTreeItem::verse);
        }
        else if (cur_chapter == 0 || cur_chapter != verse_buffer.chapter())
        {
            cur_chapter++;

            cur_verse_tree_root = cur_verse_tree_root->get_parent();

            boost::shared_ptr<VerseTreeItem> chapter = boost::shared_ptr<VerseTreeItem>(new VerseTreeItem(m_long_name, i));
            cur_verse_tree_root->add_child(chapter, VerseTreeItem::chapter);
            
            cur_verse_tree_root = chapter.get();

            boost::shared_ptr<VerseTreeItem> verse = boost::shared_ptr<VerseTreeItem>(new VerseTreeItem(m_long_name, i));
            cur_verse_tree_root->add_child(verse, VerseTreeItem::verse);

        }
        else
        {
            boost::shared_ptr<VerseTreeItem> verse = boost::shared_ptr<VerseTreeItem>(new VerseTreeItem(m_long_name, i));
            cur_verse_tree_root->add_child(verse, VerseTreeItem::verse);
        }
    }

    return true;
}

bool Translation::Import(const std::string& long_name, const std::string& short_name, const std::string& filename)
{
    this->m_long_name = long_name;
    this->m_short_name = short_name;
    std::ifstream raw_text;

    raw_text.open(filename.c_str());

    std::string line;
    while (getline(raw_text, line))
    {
        std::vector<std::string> parts;
        boost::algorithm::split(parts, line, boost::algorithm::is_any_of("*"));

        boost::shared_ptr<Verse> verse(new Verse(parts[1], boost::lexical_cast<int>(parts[2]),
                                                 boost::lexical_cast<int>(parts[3]), parts[4],
                                                 boost::lexical_cast<int>(parts[0])));
        m_verses.push_back(verse);
    }

    return true;
}


boost::shared_ptr<VerseTreeItem> Translation::get_verse_item_tree() const
{
    return m_verse_tree;
}

namespace BibleStudy
{

// Free functions
std::string verse_collection_to_title_and_string_wrapped(const std::vector<boost::shared_ptr<const Verse> >& verse_collection, boost::shared_ptr<const Translation> translation)
{
    std::string verse_collection_string = verse_collection_to_string(verse_collection);

    int line_length = 80;

    size_t cur_line_length = line_length;
    while (verse_collection_string.length() > cur_line_length)
    {
        size_t space_pos = verse_collection_string.find_last_of(" ", cur_line_length);
        if (space_pos != std::string::npos)
            verse_collection_string.replace(space_pos, 1, "\n");

        cur_line_length += line_length;
    }

    return verse_collection_title(verse_collection, translation) + "\n\n" + verse_collection_string;
}

std::string verse_collection_to_string(const std::vector<boost::shared_ptr<const Verse> >& verse_collection)
{
    std::string verse_string;

    std::vector<boost::shared_ptr<const Verse> >::const_iterator it = verse_collection.begin();
    std::vector<boost::shared_ptr<const Verse> >::const_iterator end = verse_collection.end();
    for (; it != end; ++it)
    {
        verse_string += (*it)->get_text();
        if (std::distance(it, end) != 1)
            verse_string += " ";
    }

    return verse_string;
}

std::string verse_collection_title(const std::vector<boost::shared_ptr<const Verse> >& verse_collection, boost::shared_ptr<const Translation> translation)
{
    std::string title;

    std::string cur_book;
    int cur_chapter = 0;
    int cur_verse = 0;
    int last_verse = 0;

    std::vector<boost::shared_ptr<const Verse> >::const_iterator it = verse_collection.begin();
    std::vector<boost::shared_ptr<const Verse> >::const_iterator end = verse_collection.end();
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

    title += " (";
    title += translation->get_short_name();
    title += ")";

    return title;
}

}
