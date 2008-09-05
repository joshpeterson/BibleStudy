#ifndef __UI_SEARCH_RESULTS_WIDGET
#define __UI_SEARCH_RESULTS_WIDGET

#include <QWidget>
#include <boost/shared_ptr.hpp>

class QAbstractItemModel;
class QTableView;

class UISearchResultsWidget : public QWidget
{
    Q_OBJECT

public:
    UISearchResultsWidget(QWidget* parent = 0);

signals:
    void search_results_updated();

//public slots:
//    void display_search_results(boost::shared_ptr<QAbstractItemModel> model);

private:
    QTableView* m_table_view;
};

#endif //__UI_SEARCH_RESULTS_WIDGET
