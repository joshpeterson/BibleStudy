#ifndef __DISPLAYED_VERSE_PERSISTENCE_STATE_H
#define __DISPLAYED_VERSE_PERSISTENCE_STATE_H

#include <QString>

namespace BibleDatabase
{
class VerseDisplay;
}

namespace BibleStudyGui
{

class DisplayedVersePersistenceState
{
public:
	DisplayedVersePersistenceState(BibleDatabase::VerseDisplay displayed_verse);

	QString serialize() const;

private:
	BibleDatabase::VerseDisplay m_displayed_verse;
};

}

#endif // __DISPLAYED_VERSE_PERSISTENCE_STATE_H
