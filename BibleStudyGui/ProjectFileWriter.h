#ifndef __PROJECT_FILE_WRITER_H
#define __PROJECT_FILE_WRITER_H

#include <map>
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

class ISerializable;

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

public slots:
    //! Set the state of the search GUI when the user actual performs a search.  This is used to restore the search results.  This should be called from the GUI thread.
    void set_last_searched_search_state(boost::shared_ptr<ISerializable> last_searched_search_state);

    //! Set the current state of the search GUI when it changes.  This should be called from the GUI thread.
    void set_current_search_state(boost::shared_ptr<ISerializable> current_search_state);

    //! Set the starred verses state when it changes.  This should be called from the GUI thread.
    void set_starred_verses_state(boost::shared_ptr<ISerializable> starred_verses_state);

    //! Set the displayed verse when it changes.  This should be called from the GUI thread.
    void set_displayed_verse_state(boost::shared_ptr<ISerializable> displayed_verse_state);

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

    std::map<QString, boost::shared_ptr<const ISerializable> > m_current_project_data;

    void save_project_file();
    void kick_project_file_save_timer();
};

}

#endif // __PROJECT_FILE_WRITER_H
