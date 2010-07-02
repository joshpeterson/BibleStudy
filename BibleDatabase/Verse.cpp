#include <iostream>
#include "Verse.h"

using namespace BibleDatabase;

Verse::Verse(const std::string& book, int chapter, int verse, const std::string& text,
             int unqiue_verse_id) :
    m_book(book),
    m_chapter(chapter),
    m_verse(verse),
    m_text(text),
    m_unique_id(unqiue_verse_id)
{
}

    bool Verse::match(std::string search_string) const
{
    return m_text.find(search_string) != std::string::npos;
}

void Verse::display(std::ostream& out) const
{
    out << m_book << " " << m_chapter << ":" << m_verse << std::endl << m_text << std::endl;
}

