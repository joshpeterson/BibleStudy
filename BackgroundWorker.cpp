#include "BackgroundWorker.h"
#include "BibleDatabase/ICommand.h"

using namespace BibleStudy;
using namespace BibleDatabase;

BackgroundWorker::BackgroundWorker(ICommand* command) : m_command(command)
{
}

void BackgroundWorker::run()
{
    m_command->Execute();
}