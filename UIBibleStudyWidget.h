#ifndef __UI_BIBLE_STUDY_WIDGET
#define __UI_BIBLE_STUDY_WIDGET

#include <QWidget>
#include <boost/shared_ptr.hpp>

class QVBoxLayout;
class Translation;
class VerseDisplay;
class SearchResultsModel;
class StarredVersesModel;
class BrowseVersesModel;
class UISearchWidget;
class UISearchResultsWidget;
class UIStarredVersesWidget;
class UITextViewWidget;
class UIBrowseVersesWidget;

class UIBibleStudyWidget : public QWidget
{
    Q_OBJECT

public:
    UIBibleStudyWidget(boost::shared_ptr<Translation> translation, QWidget* parent = 0);

private:
    boost::shared_ptr<SearchResultsModel> m_results_model;
    boost::shared_ptr<StarredVersesModel> m_starred_verses_model;
    boost::shared_ptr<BrowseVersesModel> m_browse_verses_model;

    UISearchWidget* m_search;
    UISearchResultsWidget* m_results;
    UIStarredVersesWidget* m_starred_verses;
    UITextViewWidget* m_text;
    UIBrowseVersesWidget* m_browse;
};

#endif //__UI_BIBLE_STUDY_WIDGET

