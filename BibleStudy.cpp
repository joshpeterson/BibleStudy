#include <fstream>
#include <iostream>
#include "IEntry.h"
#include "IVerse.h"
#include "Translation.h"
#include "SearchResultsSerial.h"
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

    test->Resume("c:\\Documents and Settings\\Josh\\My Documents\\BibleStudy\\trunk\\Translations\\DR.buf");
    
    UIBibleStudyWidget study(test);

    study.show();

   /* std::string user_query;
    std::cout << "Enter search: ";
    std::getline(std::cin, user_query);
    std::cout << std::endl;*/
    /*
    IEntry::ISearchResultsPtr query(new SearchResultsSerial("my disciple"));
    IEntry::ISearchResultsCol results;
    results.push_back(query);

    test.search(results);
    */

    /*int displayed_verses = 0;
    const int max_displayed_verses = 5;
    for (IEntry::ISearchResultsCol::const_iterator it = results.begin();
         it != results.end();
         ++it)
    {
        std::cout << "Results for query: " << (*it)->get_search_string() << std::endl << std::endl;
        for (std::vector<int>::iterator jit = (*it)->begin();
             jit != (*it)->end();
             ++jit)
        {
            test.get_entry(*jit)->display(std::cout);
            displayed_verses++;
            if (displayed_verses == max_displayed_verses)
            {
                std::cout << "More...";
                char junk;
                std::cin >> &junk;
                displayed_verses = 0;
            }
        }
    }
    std::cout << std::endl;*/

    /*
    QAbstractItemModel* model = new SearchResultsModel(&test, query);
    QTableView* table_view = new QTableView;
    table_view->setModel(model);
    table_view->setSortingEnabled(true);
    table_view->setShowGrid(false);
    QHeaderView* header = table_view->horizontalHeader();
    header->setResizeMode(QHeaderView::ResizeToContents);
    header->setStretchLastSection(true);
    table_view->show();
    */
    //UISearchWidget search;

    //search.show();

    return app.exec();

}

