#ifndef __PROJECT_FILE_WRITER_H
#define __PROJECT_FILE_WRITER_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QFile>
#include <QString>
#include "BibleDatabase/VerseDisplay.h"

class QTimer;
class QFile;

namespace BibleStudyGui
{

//! This class writes the project file on a background thread.  Call QThread::start() to start it.
class ProjectFileWriter : public QThread
{
    Q_OBJECT

public:
    //! Create a new instance of the ProjectFileWriter class.  This should be called from the GUI thread.
	ProjectFileWriter();
	
	//! Cleanly stop the ProjectFileWriter background thread.  This should be called from the GUI thread.
	~ProjectFileWriter();

    //! This is the method which executes on the background thread.  It should be called only by Qt.
    void run();

	//! Set the project file path when the user does a save as operation.  This should be called from the GUI thread.
	void set_project_file_path(QString project_file_path);

	//! Set the search string when it changes.  This should be called from the GUI thread.
	void set_search_string(QString search_string);

	//! Set the selected search options when they change.  This should be called from the GUI thread.
	void set_search_options(bool match_case, bool whole_word);

	//! Set the selected translations when they change.  This should be called from the GUI thread.
	void set_selected_translations(std::vector<QString> selected_translations);

	//! Set the starred verses when they change.  This should be called from the GUI thread.
	void set_starred_verses(std::vector<BibleDatabase::VerseDisplay> starred_verses);

	//! Set the displayed verse when it changes.  This should be called from the GUI thread.
	void set_displayed_verse(boost::shared_ptr<BibleDatabase::VerseDisplay> displayed_verse);

private slots:
	void start_save_project_file();

signals:
	void project_file_save_failed(QString reason);

private:
	bool m_abort;
	QMutex m_save_project_file_mutex;
	QWaitCondition m_save_project_file_condition;

	boost::shared_ptr<QFile> m_project_file;
	const int m_project_file_version;

	QTimer* m_project_file_save_timer;
	const int m_project_file_save_timeout_ms;

	struct ProjectData
	{
		QString search_string;
		bool match_case_search_option;
		bool whole_word_search_option;
		std::vector<QString> selected_translations;
		std::vector<BibleDatabase::VerseDisplay> starred_verses;
		boost::shared_ptr<BibleDatabase::VerseDisplay> displayed_verse;
	} m_current_project_data;

	void save_project_file();
	void kick_project_file_save_timer();
};

}

#endif // __PROJECT_FILE_WRITER_H
