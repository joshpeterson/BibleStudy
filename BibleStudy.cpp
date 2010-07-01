#include <iostream>
#include <stdexcept>
#include "BibleDatabase/Translation.h"
#include "BibleDatabase/TranslationManager.h"
#include "BibleDatabase/TranslationLoader.h"
#include "UISearchWidget.h"
#include "SearchResultsModel.h"
#include "UISearchResultsWidget.h"
#include "UIBibleStudyWidget.h"
#include <QApplication>
#include <QPushButton>
#include <QAbstractItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>

using namespace BibleStudy;
using namespace BibleDatabase;

int main(int argc, char* argv[])
{
    try
    {
        QApplication app(argc, argv);

        boost::shared_ptr<const TranslationLoader> translation_loader = boost::shared_ptr<const TranslationLoader>(new TranslationLoader(QCoreApplication::applicationDirPath().toStdString()));
        boost::shared_ptr<TranslationManager> manager(new TranslationManager);
        
        UIBibleStudyWidget study(manager, translation_loader);

        study.show();

        return app.exec();
    }
    catch (std::exception& e)
    {
        std::cout << "Uh-oh, something very bad happened." << std::endl;
        std::cout << "These details might help (or they might not):\n\n" << e.what() << std::endl;
    }
}

