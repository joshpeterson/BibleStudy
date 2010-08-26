#include "BackgroundWorker.h"
#include "../BibleDatabase/ICommand.h"

using namespace BibleStudy;
using namespace BibleDatabase;

BackgroundWorker::BackgroundWorker(boost::shared_ptr<ICommand> command) : m_command(command)
{
}

void BackgroundWorker::run()
{
    m_command->Execute();
}