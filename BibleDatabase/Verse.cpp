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

bool Verse::case_sensitive_whole_word_match(std::string search_string) const
{
    size_t position = m_text.find(search_string);
    while (position != std::string::npos)
    {
        if ((position == 0 || is_word_delimiter(m_text[position-1])) && 
            (position + search_string.size() == m_text.size() || is_word_delimiter(m_text[position + search_string.size()])))
        {
            return true;
        }

        position = m_text.find(search_string, position + 1);
    }

    return false;
}

bool Verse::case_insensitive_match(std::string search_string) const
{
    return std::search(m_text.begin(), m_text.end(), search_string.begin(), search_string.end(), case_insensitive_character_comparison) != m_text.end();
}

bool Verse::case_insensitive_whole_word_match(std::string search_string) const
{
    std::string::const_iterator position = std::search(m_text.begin(), m_text.end(), search_string.begin(), search_string.end(), case_insensitive_character_comparison);
    while (position != m_text.end())
    {
        if ((position == m_text.begin() || is_word_delimiter(*(position-1))) && 
            (position + search_string.size() == m_text.end() || is_word_delimiter(*(position + search_string.size()))))
        {
            return true;
        }

        position = std::search(position + 1, m_text.end(), search_string.begin(), search_string.end(), case_insensitive_character_comparison);
    }

    return false;
}

void Verse::display(std::ostream& out) const
{
    out << m_book << " " << m_chapter << ":" << m_verse << std::endl << m_text << std::endl;
}

bool Verse::is_word_delimiter(char character) const
{
    return character == ' ' || character == '.' || character == ',' || character == ';' || character == '?' || character == '!' || character == ':';
}

