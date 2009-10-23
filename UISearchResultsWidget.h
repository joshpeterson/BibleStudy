#ifndef __UI_SEARCH_RESULTS_WIDGET
#define __UI_SEARCH_RESULTS_WIDGET

#include <QWidget>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>
#include <boost/shared_ptr.hpp>

class QAbstractItemModel;
class QTableView;
class QLineEdit;
class QSortFilterProxyModel;
class QTimer;
class QLabel;
class QKeyEvent;

namespace BibleStudy
{

class Translation;
class ISearchResults;
class SearchResultsModel;
class VerseDisplay;

//! This class is an implementation of a view from the Qt Model/View framework for a table view which displays the results of a text search.
class UISearchResultsWidget : public QWidget
{
    Q_OBJECT

public:
    //! Create a new instance of the UISearchResultsWidget class.
    UISearchResultsWidget(boost::shared_ptr<SearchResultsModel> results_model, QWidget* parent = 0);

    void keyPressEvent(QKeyEvent *event);

public slots:
    //! Set the results object which the widget should display.
    void display_search_results(boost::shared_ptr<ISearchResults> query);

    //! Get the verse at the given index and emit the verse_display_changed signal for that verse.
    void display_verse_text(const QModelIndex& index);

    //! When the user types text in the search results filter, restart the timer which waits for the typing to be complete.
    void update_search_results_filter_delay_timer();

    //! Get the new filter text and apply it to the search results.
    void change_search_results_filter();

signals:
    //! Signal other widgets that a new verse should be displayed.
    void verse_display_changed(boost::shared_ptr<VerseDisplay> verse);

private:
    QTableView* m_results_view;
    QLabel* m_results_status;
    QLineEdit* m_filter_text;
    QTimer* m_filter_delay_timer;
    const int m_filter_delay_typing_timeout_ms;
    QSortFilterProxyModel* m_proxy_model;
    boost::shared_ptr<SearchResultsModel> m_results_model;

    void update_results_status();
};

}

#endif //__UI_SEARCH_RESULTS_WIDGET
