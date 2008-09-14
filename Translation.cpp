#include <fstream>
#include <string>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/iostreams/code_converter.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include "Translation.h"
#include "Verse.h"
#include "TranslationBuffer.pb.h"

void Translation::search(IEntry::ISearchResultsCol& results) const
{
    for (std::vector< boost::shared_ptr<IVerse> >::const_iterator it = m_verses.begin();
         it != m_verses.end();
         ++it)
    {
        (*it)->match(results);
    }
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

