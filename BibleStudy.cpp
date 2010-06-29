#include <iostream>
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
    QApplication app(argc, argv);

    boost::shared_ptr<const TranslationLoader> translation_loader = boost::shared_ptr<const TranslationLoader>(new TranslationLoader(QCoreApplication::applicationDirPath().toStdString()));

    boost::shared_ptr<const Translation> dr = translation_loader->create_translation("../Translations/DR.buf");
    boost::shared_ptr<const Translation> kjv = translation_loader->create_translation("../Translations/KJV.buf");
    
    boost::shared_ptr<TranslationManager> manager(new TranslationManager);
    manager->add_translation(dr);
    manager->add_translation(kjv);
    
    UIBibleStudyWidget study(manager);

    study.show();

    return app.exec();

}

