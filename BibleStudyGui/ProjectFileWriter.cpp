#include <boost/make_shared.hpp>
#include <QFile>
#include <QTimer>
#include <QIODevice>
#include <QTextStream>
#include "ProjectFileWriter.h"
#include "QtConnectHelper.h"
#include "QMutexLocker.h"

using namespace BibleDatabase;
using namespace BibleStudyGui;

ProjectFileWriter::ProjectFileWriter() :
	m_abort(false),
	m_project_file_version(1),
	m_project_file_save_timer(new QTimer),
    m_project_file_save_timeout_ms(1000)
{
	QT_CONNECT(m_project_file_save_timer, SIGNAL(timeout()), this, SLOT(start_save_project_file()));
}

ProjectFileWriter::~ProjectFileWriter()
 {
	 {
		QMutexLocker lock(&m_save_project_file_mutex);
		m_abort = true;
		m_save_project_file_condition.wakeOne();
	 }

     wait();
 }

void ProjectFileWriter::run()
{
	while (1)
	{
		QMutexLocker lock(&m_save_project_file_mutex);
		m_save_project_file_condition.wait(&m_save_project_file_mutex);

		if (m_abort)
		{
			return;
		}

		if (m_project_file != NULL)
		{
			save_project_file();
		}
	}
}

void ProjectFileWriter::set_project_file_path(QString project_file_path)
{
	QMutexLocker lock(&m_save_project_file_mutex);

	if (m_project_file != NULL)
	{
		m_project_file->copy(project_file_path);
	}

	m_project_file = boost::make_shared<QFile>(project_file_path);
}

void ProjectFileWriter::set_search_string(QString search_string)
{
	QMutexLocker lock(&m_save_project_file_mutex);
	m_current_project_data.search_string = search_string;
	
	kick_project_file_save_timer();
}

void ProjectFileWriter::set_search_options(bool match_case, bool whole_word)
{
	QMutexLocker lock(&m_save_project_file_mutex);
	m_current_project_data.match_case_search_option = match_case;
	m_current_project_data.whole_word_search_option = whole_word;

	kick_project_file_save_timer();
}

void ProjectFileWriter::set_selected_translations(std::vector<QString> selected_translations)
{
	QMutexLocker lock(&m_save_project_file_mutex);
	m_current_project_data.selected_translations = selected_translations;

	kick_project_file_save_timer();
}

void ProjectFileWriter::set_starred_verses(std::vector<VerseDisplay> starred_verses)
{
	QMutexLocker lock(&m_save_project_file_mutex);
	m_current_project_data.starred_verses = starred_verses;

	kick_project_file_save_timer();
}

void ProjectFileWriter::set_displayed_verse(boost::shared_ptr<VerseDisplay> displayed_verse)
{
	QMutexLocker lock(&m_save_project_file_mutex);
	m_current_project_data.displayed_verse = displayed_verse;

	kick_project_file_save_timer();
}

void ProjectFileWriter::start_save_project_file()
{
	m_save_project_file_condition.wakeOne();
}

void ProjectFileWriter::save_project_file()
{
	if (m_project_file->open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
	{
		// This additional scope is used to make sure the QTextStream object is flushed before we close the file.
		{
			QTextStream project_stream(m_project_file.get());

			project_stream << "Version: " << m_project_file_version << "\n";

			for (std::map<QString, boost::shared_ptr<const ISeriaizable> >::const_iterator it = m_current_project_data.begin(); it != m_current_project_data.end(); ++it)
			{
				project_stream << it->first << ": " << it->second->serialize() << "\n";
			}
		}

		m_project_file->close();
	}
	else
	{
		emit project_file_save_failed(tr("Unable to access file ") + m_project_file->fileName());
	}
}

void ProjectFileWriter::kick_project_file_save_timer()
{
	m_project_file_save_timer->start(m_project_file_save_timeout_ms);
}