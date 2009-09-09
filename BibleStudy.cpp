#include <fstream>
#include <iostream>
#include "Translation.h"
#include "TranslationManager.h"
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

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    //std::ifstream raw_text;

    //raw_text.open("c:\\Documents and Settings\\Josh\\Desktop\\DR.txt");

    boost::shared_ptr<Translation> test(new Translation);

    //test.Import("Douay-Rheims", "DR", "c:\\Documents and Settings\\Josh\\Desktop\\DR.txt");

    //test.Save("c:\\Documents and Settings\\Josh\\Desktop\\DR.buf");

    test->Resume("Translations/DR.buf");

    boost::shared_ptr<TranslationManager> manager(new TranslationManager);
    manager->add_translation(test);
    
    UIBibleStudyWidget study(manager);

    study.show();

    return app.exec();

}

