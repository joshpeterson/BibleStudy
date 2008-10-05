#include "VerseDisplay.h"    

VerseDisplay::VerseDisplay(std::string translation, int verse_id, int num_verses_context) :
    m_translation(translation),
    m_verse_id(verse_id),
    m_num_verses_context(num_verses_context)
{
}
std::string VerseDisplay::get_translation() const
{
    return m_translation;
}

int VerseDisplay::get_verse_id() const
{
    return m_verse_id;
}

int VerseDisplay::get_num_verses_context() const
{
    return m_num_verses_context;
}

bool VerseDisplay::operator==(const VerseDisplay& other) const
{
    return m_verse_id == other.get_verse_id() && m_translation == other.get_translation();
}