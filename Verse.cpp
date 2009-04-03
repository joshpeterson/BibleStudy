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

void Verse::match(boost::shared_ptr<ISearchResults> search_string) const
{
    if (m_text.find(search_string->get_search_string()) != std::string::npos)
        search_string->add_matching_verse(m_unique_id);
}

void Verse::display(std::ostream& out) const
{
    out << m_book << " " << m_chapter << ":" << m_verse << std::endl << m_text << std::endl;
}

