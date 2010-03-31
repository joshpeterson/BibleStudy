#ifndef __UI_BIBLE_STUDY_WIDGET
#define __UI_BIBLE_STUDY_WIDGET

#include <QMainWindow>
#include <boost/shared_ptr.hpp>

class QDockWidget;

namespace BibleStudy
{

class TranslationManager;
class VerseDisplay;
class SearchResultsModel;
class StarredVersesModel;
class BrowseVersesModel;
class UISearchWidget;
class UISearchResultsWidget;
class UIStarredVersesWidget;
class UITextViewWidget;
class UIBrowseVersesWidget;

//! This class is the GUI respresentation of the top level widget for the application.
/*!
    This widget owns all of the other widgets in the application.  It also defines the layout
    of the application.
*/
class UIBibleStudyWidget : public QMainWindow
{
    Q_OBJECT

public:
    //! Create a new instance of the UIBibleStudyWidget class.
    UIBibleStudyWidget(boost::shared_ptr<const TranslationManager> translation_manager);

private:
    boost::shared_ptr<SearchResultsModel> m_results_model;
    boost::shared_ptr<StarredVersesModel> m_starred_verses_model;
    boost::shared_ptr<BrowseVersesModel> m_browse_verses_model;

    UISearchWidget* m_search;
    QDockWidget* m_results_dock;
    UISearchResultsWidget* m_results;
    QDockWidget* m_starred_verses_dock;
    UIStarredVersesWidget* m_starred_verses;
    QDockWidget* m_text_dock;
    UITextViewWidget* m_text;
    QDockWidget* m_browse_dock;
    UIBrowseVersesWidget* m_browse;
};

}

#endif //__UI_BIBLE_STUDY_WIDGET

