#ifndef __UI_BIBLE_STUDY_WIDGET
#define __UI_BIBLE_STUDY_WIDGET

#include <QWidget>
#include <boost/shared_ptr.hpp>

class QVBoxLayout;
class Translation;
class UISearchWidget;
class UISearchResultsWidget;

class UIBibleStudyWidget : public QWidget
{
    Q_OBJECT

public:
    UIBibleStudyWidget(boost::shared_ptr<Translation> translation, QWidget* parent = 0);

private:
    UISearchWidget* m_search;
    UISearchResultsWidget* m_results;
};

#endif //__UI_BIBLE_STUDY_WIDGET

