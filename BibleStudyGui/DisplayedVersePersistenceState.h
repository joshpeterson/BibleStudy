#ifndef __DISPLAYED_VERSE_PERSISTENCE_STATE_H
#define __DISPLAYED_VERSE_PERSISTENCE_STATE_H

#include <QString>
#include "ISerializable.h"

namespace BibleDatabase
{
class VerseDisplay;
}

namespace BibleStudyGui
{

//! This class stores all of the data necessary to persist the state of the currently displayed verse.
class DisplayedVersePersistenceState : public ISerializable
{
public:
    //! Create a new instance of the DisplayedVersePersistenceState class.
    DisplayedVersePersistenceState(BibleDatabase::VerseDisplay displayed_verse);
    
    // ISerializable

    //! This method is the implementation of ISerializable.  It serializes the object to a string.
    QString serialize() const;

private:
    BibleDatabase::VerseDisplay m_displayed_verse;
};

}

#endif // __DISPLAYED_VERSE_PERSISTENCE_STATE_H
