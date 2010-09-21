#include <QTextStream>
#include "../BibleDatabase/VerseDisplay.h"
#include "StarredVersesPersistenceState.h"

using namespace BibleDatabase;
using namespace BibleStudyGui;

StarredVersesPersistenceState::StarredVersesPersistenceState(std::vector<BibleDatabase::VerseDisplay> starred_verses) :
    m_starred_verses(starred_verses)
{
}

QString StarredVersesPersistenceState::serialize() const
{
    QString serialized_starred_verses_state;

    {
        QTextStream starred_verses_state_stream(&serialized_starred_verses_state);
        starred_verses_state_stream << "Starred verses: ";
        for (std::vector<BibleDatabase::VerseDisplay>::const_iterator it = m_starred_verses.begin(); it != m_starred_verses.end(); ++it)
        {
            starred_verses_state_stream << it->serialize().c_str() << " ";
        }
    }

    return serialized_starred_verses_state;
}
