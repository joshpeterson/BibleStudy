#ifndef __UI_SEARCH_RESULTS_WIDGET
#define __UI_SEARCH_RESULTS_WIDGET

#include <QWidget>
#include <QAbstractItemModel>
#include <boost/shared_ptr.hpp>

class QAbstractItemModel;
class QTableView;
class QVBoxLayout;
class Translation;
class ISearchResults;
class SearchResultsModel;
class VerseDisplay;

//! This class is an implementation of a view from the Qt Model/View framework for a table view which displays the results of a text search.
class UISearchResultsWidget : public QWidget
{
    Q_OBJECT

public:
    UISearchResultsWidget(boost::shared_ptr<SearchResultsModel> results_model, QWidget* parent = 0);

public slots:
    void display_search_results(boost::shared_ptr<ISearchResults> query);
    void display_verse_text(const QModelIndex& index);

signals:
    void verse_display_changed(boost::shared_ptr<VerseDisplay> verse);

private:
    QTableView* m_results_view;
    QVBoxLayout* m_layout;
    boost::shared_ptr<SearchResultsModel> m_results_model;
};

#endif //__UI_SEARCH_RESULTS_WIDGET
