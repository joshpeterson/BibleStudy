#ifndef __UI_BIBLE_STUDY_WIDGET
#define __UI_BIBLE_STUDY_WIDGET

#include <stack>
#include <QMainWindow>
#include <boost/shared_ptr.hpp>

class QWidget;
class QTabWidget;
class QAction;
class QMenu;
class QTimer;

namespace BibleDatabase
{
class TranslationManager;
class TranslationLoader;
class VerseDisplay;
}

namespace BibleStudy
{

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
    UIBibleStudyWidget(boost::shared_ptr<BibleDatabase::TranslationManager> translation_manager, boost::shared_ptr<const BibleDatabase::TranslationLoader> translation_loader);

private slots:
    //! Bring the search results widget to the top of the tab widgets.
    void raise_results();

    //! Bring the starred verses widget to the top of the tab widgets.
    void raise_starred_verses();

    //! Show the About box for the application.
    void about();

    //! Display a specific status bar message when a search starts.
    void display_search_status_bar_message(QString search_text);

    //! Display a specific status bar message when a search results filter starts.
    void display_search_results_filter_status_bar_message(QString filter_text);

    //! Put the given message on the status bar and add it to the status bar message stack.
    void push_status_bar_message(QString message);

    //! Pop the last status bar message off the stack, and write the new message on the top of the stack to the status bar.
    void pop_status_bar_message(); 

    //! Load the translations from the bible database.
    void load_translations();

signals:
    //! Inform other widgets that all translations have been loaded.
    void translations_loaded();

private:
    boost::shared_ptr<BibleDatabase::TranslationManager> m_translation_manager;
    boost::shared_ptr<const BibleDatabase::TranslationLoader> m_translation_loader;

    QTimer* m_translation_load_timer;
    const int m_translation_load_timeout_ms;

    boost::shared_ptr<SearchResultsModel> m_results_model;
    boost::shared_ptr<StarredVersesModel> m_starred_verses_model;
    boost::shared_ptr<BrowseVersesModel> m_browse_verses_model;

    QWidget* m_dummy_central_widget;
    QTabWidget* m_tabs;
    UISearchWidget* m_search;
    UISearchResultsWidget* m_results;
    UIStarredVersesWidget* m_starred_verses;
    UITextViewWidget* m_text;
    UIBrowseVersesWidget* m_browse;

    QAction* m_exit_action;
    QAction* m_about_action;

    QMenu* m_file_menu;
    QMenu* m_help_menu;

    std::stack<QString> m_status_bar_messages;

    void connect_signals();
    void set_font();
    void initialize_widgets();
    void initialize_status_bar();
    void initialize_actions();
    void initialize_menus();
};

}

#endif //__UI_BIBLE_STUDY_WIDGET

