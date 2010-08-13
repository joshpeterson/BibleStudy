#ifndef __BACKGROUND_WORKER_H
#define __BACKGROUND_WORKER_H

#include <boost/shared_ptr.hpp>
#include <QThread>

namespace BibleDatabase
{
    class ICommand;
}

namespace BibleStudy
{

//! This class executes a given command on a background thread.  Call QThread::start() to start the worker.
class BackgroundWorker : public QThread
{
    Q_OBJECT

public:
    //! Create a new instance of the BackgroundWorker class.
    BackgroundWorker(boost::shared_ptr<BibleDatabase::ICommand> command);

    //! Execute the given command.  This method should be called by Qt.
    void run();

private:
    boost::shared_ptr<BibleDatabase::ICommand> m_command;
};

}

#endif // __BACKGROUND_WORKER_H
