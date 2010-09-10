#ifndef __PROJECT_FILE_DATA_H
#define __PROJECT_FILE_DATA_H

#include <vector>
#include <QString>
#include "ISerializable.h"

namespace BibleStudyGui
{

//! This class stores all of the data necessary to persist the state of the search GUI.
class SearchPersistenceState : public ISerializable
{
public:
	//! Create a new instance of the SearchPersistenceState class.
	SearchPersistenceState(QString search_string, bool match_case, bool whole_word, std::vector<QString> selected_translations);

	// ISerializable

	//! This method is the implementation of ISerializable.  It serializes the object to a string.
	QString serialize() const;

private:
	QString m_search_string;
	bool m_match_case;
	bool m_whole_word;
	std::vector<QString> m_selected_translations;
};

}

#endif __PROJECT_FILE_DATA_H
