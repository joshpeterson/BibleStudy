#ifndef __UI_BIBLE_STUDY_WIDGET
#define __UI_BIBLE_STUDY_WIDGET

#include <QWidget>
#include <boost/shared_ptr.hpp>
#include "IEntry.h"

class QVBoxLayout;
class QTableView;
class QAbstractItemModel;
class Translation;
class UISearchWidget;
class UISearchResultsWidget;
class SearchResultsModel;

class UIBibleStudyWidget : public QWidget
{
    Q_OBJECT

public:
    UIBibleStudyWidget(boost::shared_ptr<Translation> translation, QWidget* parent = 0);

public slots:
    void refresh_search_results();
    void display_search_results(IEntry::ISearchResultsPtr query);

private:
    UISearchWidget* m_search;
    QTableView* m_results_view;
    QVBoxLayout* m_layout;
    boost::shared_ptr<SearchResultsModel> m_results_model;
};

#endif //__UI_BIBLE_STUDY_WIDGET

