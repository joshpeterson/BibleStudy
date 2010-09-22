#include <boost/make_shared.hpp>
#include <QFile>
#include <QTimer>
#include <QIODevice>
#include <QTextStream>
#include "ProjectFileWriter.h"
#include "QtConnectHelper.h"
#include "QMutexLocker.h"
#include "ISerializable.h"

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

void ProjectFileWriter::set_last_searched_search_state(boost::shared_ptr<ISerializable> last_searched_search_state)
{
    QMutexLocker lock(&m_save_project_file_mutex);
    m_current_project_data["Last used search"] = last_searched_search_state;

    kick_project_file_save_timer();
}

void ProjectFileWriter::set_current_search_state(boost::shared_ptr<ISerializable> current_search_state)
{
    QMutexLocker lock(&m_save_project_file_mutex);
    m_current_project_data["Current search"] = current_search_state;
    
    kick_project_file_save_timer();
}

void ProjectFileWriter::set_starred_verses_state(boost::shared_ptr<ISerializable> starred_verses_state)
{
    QMutexLocker lock(&m_save_project_file_mutex);
    m_current_project_data["Starred verses"] = starred_verses_state;

    kick_project_file_save_timer();
}

void ProjectFileWriter::set_displayed_verse_state(boost::shared_ptr<ISerializable> displayed_verse_state)
{
    QMutexLocker lock(&m_save_project_file_mutex);
    m_current_project_data["Displayed verse"] = displayed_verse_state;

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

            for (std::map<QString, boost::shared_ptr<const ISerializable> >::const_iterator it = m_current_project_data.begin(); it != m_current_project_data.end(); ++it)
            {
                project_stream << it->first << ":\n" << it->second->serialize() << "\n";
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