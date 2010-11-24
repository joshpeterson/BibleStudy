#ifndef __VERSE_DISPLAY_H
#define __VERSE_DISPLAY_H

#include <string>

namespace BibleDatabase
{

//! This class respresents the information necessary to display a given verse.  This include the verse ID, the number of context verses, and Translation object.
class VerseDisplay
{
public:
    //! Create a new instance of the VerseDisplay class.
    VerseDisplay(std::string translation, int verse_id, int num_verses_context);

    //! Get the long name of the Translation object for this instance.
    std::string get_translation() const;

    //! Get the unique ID of the verse for this instance.
    int get_verse_id() const;

    //! Get the number of verses of context that should be displayed with this verse.
    int get_num_verses_context() const;

    //! Determine if this VerseDisplay instance has the same data as another instance.  Note that this does not test the number of context verses.
    bool operator==(const VerseDisplay& other) const;

private:
    std::string m_translation;
    int m_verse_id;
    int m_num_verses_context;

    //! Prevent default construction.
    VerseDisplay() {}
};

}

#endif //__VERSE_DISPLAY_H

