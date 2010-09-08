#include <QTextStream>
#include "SearchPersistenceState.h"

SearchPersistenceState(QString search_string, bool match_case, bool whole_word, std::vector<QString> selected_translations) :
	m_selected_translations(search_string),
	m_match_case(match_case),
	m_whole_word(whole_word),
	m_selected_translations(selected_translations)
{
}

QString serialize() const
{
	QString serialized_search_state;

	{
		QTextStream search_state_stream(serialized_search_state);
		search_state_stream << "Search string: " << m_search_string << "\n";
		search_state_stream << "Match case: " << m_match_case << "\n";
		search_state_stream << "Whole word: " << m_whole_word << "\n";

		search_state_stream << "Selected translations: ";
		for (std::vector<QString>::const_iterator it = m_selected_translations.begin(); it != m_selected_translations.end(); ++it)
		{
			search_state_stream << *it << " ";
		}

		search_state_stream << "\n";
	}

	return serialized_search_state;
}