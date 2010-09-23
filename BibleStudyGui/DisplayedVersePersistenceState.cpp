#include <QTextStream>
#include "../BibleDatabase/VerseDisplay.h"
#include "DisplayedVersePersistenceState.h"

using namespace BibleDatabase;
using namespace BibleStudyGui;

DisplayedVersePersistenceState::DisplayedVersePersistenceState(BibleDatabase::VerseDisplay displayed_verse):
    m_displayed_verse(displayed_verse)
{
}

QString DisplayedVersePersistenceState::serialize() const
{
    QString serialized_displayed_verse_state;

    {
        QTextStream displayed_verse_state_stream(&serialized_displayed_verse_state);
        displayed_verse_state_stream << "Displayed verse: " << m_displayed_verse.serialize().c_str();
    }

    return serialized_displayed_verse_state;
}