#ifndef __PROJECT_FILE_DATA_H
#define __PROJECT_FILE_DATA_H

#include <vector>
#include <QString>

namespace BibleStudyGui
{

class SearchPersistenceState
{
public:
	SearchPersistenceState(QString search_string, bool match_case, bool whole_word, std::vector<QString> selected_translations);

	QString serialize() const;

private:
	QString m_search_string;
	bool m_match_case;
	bool m_whole_word;
	std::vector<QString> m_selected_translations;
};

}

#endif __PROJECT_FILE_DATA_H
