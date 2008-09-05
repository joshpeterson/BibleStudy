#ifndef __UI_BIBLE_STUDY_WIDGET
#define __UI_BIBLE_STUDY_WIDGET

#include <QWidget>
#include <boost/shared_ptr.hpp>

class QVBoxLayout;
class QTableView;
class QAbstractItemModel;
class Translation;
class UISearchWidget;
class UISearchResultsWidget;

class UIBibleStudyWidget : public QWidget
{
    Q_OBJECT

public:
    UIBibleStudyWidget(boost::shared_ptr<Translation> translation, QWidget* parent = 0);

public slots:
    void refresh_search_results();
    void display_search_results(boost::shared_ptr<QAbstractItemModel> model);

private:
    UISearchWidget* m_search;
    QTableView* m_results;
    QVBoxLayout* m_layout;
};

#endif //__UI_BIBLE_STUDY_WIDGET

