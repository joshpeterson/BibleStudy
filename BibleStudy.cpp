#include <iostream>
#include "BibleDatabase/Translation.h"
#include "BibleDatabase/TranslationManager.h"
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
    QApplication app(argc, argv);

    boost::shared_ptr<Translation> test(new Translation);

    //test->Import("King James Version", "KJV", "c:\\Documents and Settings\\Josh\\Desktop\\KJV.txt");

    //test->Save("c:\\Documents and Settings\\Josh\\Desktop\\KJV.buf");

    test->Resume("Translations/DR.buf");

    boost::shared_ptr<Translation> test2(new Translation);
    test2->Resume("Translations/KJV.buf");

    boost::shared_ptr<TranslationManager> manager(new TranslationManager);
    manager->add_translation(test);
    manager->add_translation(test2);
    
    UIBibleStudyWidget study(manager);

    study.show();

    return app.exec();

}

