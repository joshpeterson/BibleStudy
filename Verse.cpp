#include "Verse.h"
#include "ISearchResults.h"

Verse::Verse(const std::string& book, int chapter, int verse, const std::string& text,
             int unqiue_verse_id) :
    m_book(book),
    m_chapter(chapter),
    m_verse(verse),
    m_text(text),
    m_unique_id(unqiue_verse_id)
{
}

// IEntry
void Verse::match(ISearchResultsCol& search_strings) const
{
    ISearchResultsCol::iterator search_string = search_strings.begin();
    ISearchResultsCol::iterator search_string_end = search_strings.end();
    for(; search_string != search_string_end; ++search_string)
    {
        if (m_text.find((*search_string)->get_search_string()) != std::string::npos)
            (*search_string)->add_matching_verse(m_unique_id);
    }
}

void Verse::display(std::ostream& out) const
{
    out << m_book << " " << m_chapter << ":" << m_verse << std::endl << m_text << std::endl;
}

