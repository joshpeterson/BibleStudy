#ifndef __STARRED_VERSES_PERSISTENCE_STATE_H
#define __STARRED_VERSES_PERSISTENCE_STATE_H

#include <vector>
#include <QString>

namespace BibleDatabase
{
class VerseDisplay;
}

namespace BibleStudyGui
{

class StarredVersesPersistenceState
{
public:
	StarredVersesPersistenceState(std::vector<BibleDatabase::VerseDisplay> starred_verses);

	QString serialize() const;

private:
	std::vector<BibleDatabase::VerseDisplay> m_starred_verses;
};

}

#endif // __STARRED_VERSES_PERSISTENCE_STATE_H
