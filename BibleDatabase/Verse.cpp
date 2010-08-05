#include <iostream>
#include <algorithm>
#include <cctype>
#include "Verse.h"

using namespace BibleDatabase;

namespace BibleDatabase
{

bool case_insensitive_character_comparison(char character1, char character2)
{
    return std::toupper(character1) == std::toupper(character2);
}

}

Verse::Verse(const std::string& book, int chapter, int verse, const std::string& text,
             int unqiue_verse_id) :
    m_book(book),
    m_chapter(chapter),
    m_verse(verse),
    m_text(text),
    m_unique_id(unqiue_verse_id)
{
}

bool Verse::case_sensitive_match(std::string search_string) const
{
    return m_text.find(search_string) != std::string::npos;
}

bool Verse::case_insensitive_match(std::string search_string) const
{
    return std::search(m_text.begin(), m_text.end(), search_string.begin(), search_string.end(), case_insensitive_character_comparison) != m_text.end();
}

void Verse::display(std::ostream& out) const
{
    out << m_book << " " << m_chapter << ":" << m_verse << std::endl << m_text << std::endl;
}

