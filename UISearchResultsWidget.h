#ifndef __UI_SEARCH_RESULTS_WIDGET
#define __UI_SEARCH_RESULTS_WIDGET

#include <QWidget>
#include <boost/shared_ptr.hpp>

class QAbstractItemModel;
class QTableView;
class QVBoxLayout;
class Translation;
class ISearchResults;
class SearchResultsModel;

class UISearchResultsWidget : public QWidget
{
    Q_OBJECT

public:
    UISearchResultsWidget(boost::shared_ptr<Translation> translation, QWidget* parent = 0);

public slots:
    void display_search_results(boost::shared_ptr<ISearchResults> query);

private:
    QTableView* m_results_view;
    QVBoxLayout* m_layout;
    boost::shared_ptr<SearchResultsModel> m_results_model;
};

#endif //__UI_SEARCH_RESULTS_WIDGET
