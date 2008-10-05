#ifndef __VERSE_DISPLAY_H
#define __VERSE_DISPLAY_H

#include <string>

class VerseDisplay
{
public:
    VerseDisplay(std::string translation, int verse_id, int num_verses_context);
    std::string get_translation() const;
    int get_verse_id() const;
    int get_num_verses_context() const;
    bool operator==(const VerseDisplay& other) const;

private:
    std::string m_translation;
    int m_verse_id;
    int m_num_verses_context;
};

#endif //__VERSE_DISPLAY_H