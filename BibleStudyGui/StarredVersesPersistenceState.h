#ifndef __STARRED_VERSES_PERSISTENCE_STATE_H
#define __STARRED_VERSES_PERSISTENCE_STATE_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include <QString>
#include "ISerializable.h"

namespace BibleDatabase
{
class VerseDisplay;
}

namespace BibleStudyGui
{

//! This class stores all of the data necessary to persist the state of the starred verses.
class StarredVersesPersistenceState : public ISerializable
{
public:
    //! Create a new instance of the StarredVersesPersistenceState class.
    StarredVersesPersistenceState(std::vector<boost::shared_ptr<BibleDatabase::VerseDisplay> > starred_verses);
    
    // ISerializable

    //! This method is the implementation of ISerializable.  It serializes the object to a string.
    QString serialize() const;

private:
    std::vector<boost::shared_ptr<BibleDatabase::VerseDisplay> > m_starred_verses;
};

}

#endif // __STARRED_VERSES_PERSISTENCE_STATE_H
