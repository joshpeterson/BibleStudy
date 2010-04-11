#include <boost/shared_ptr.hpp>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QTabWidget>
#include <QStatusBar>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QKeySequence>
#include <QMessageBox>
#include "SearchResultsModel.h"
#include "StarredVersesModel.h"
#include "BrowseVersesModel.h"
#include "UIBibleStudyWidget.h"
#include "UISearchWidget.h"
#include "UISearchResultsWidget.h"
#include "UIStarredVersesWidget.h"
#include "UITextViewWidget.h"
#include "UIBrowseVersesWidget.h"

using namespace BibleStudy;

UIBibleStudyWidget::UIBibleStudyWidget(boost::shared_ptr<const TranslationManager> translation_manager) :
    m_results_model(new SearchResultsModel(translation_manager)),
    m_starred_verses_model(new StarredVersesModel(translation_manager)),
    m_browse_verses_model(new BrowseVersesModel(translation_manager)),
    m_dummy_central_widget(new QWidget(this)),
    m_tabs(new QTabWidget()),
    m_search(new UISearchWidget(translation_manager)),
    m_results(new UISearchResultsWidget(m_results_model)),
    m_starred_verses(new UIStarredVersesWidget(m_starred_verses_model)),
    m_text(new UITextViewWidget(translation_manager, m_starred_verses_model)),
    m_browse(new UIBrowseVersesWidget(m_browse_verses_model)),
    m_exit_action(new QAction(tr("E&xit"), this)),
    m_about_action(new QAction(tr("&About"), this))
{
    this->connect_signals();
    this->set_font();
    this->initialize_widgets();
    this->initialize_status_bar();
    this->initialize_actions();
    this->initialize_menus();
}

void UIBibleStudyWidget::connect_signals()
{
    QObject::connect(m_search, SIGNAL(search_complete(boost::shared_ptr<ISearchResults>)), m_results, SLOT(display_search_results(boost::shared_ptr<ISearchResults>)));
    QObject::connect(m_search, SIGNAL(search_complete(boost::shared_ptr<ISearchResults>)), this, SLOT(raise_results()));
    QObject::connect(m_text, SIGNAL(verse_starred(boost::shared_ptr<VerseDisplay>)), m_starred_verses, SLOT(add_starred_verse(boost::shared_ptr<VerseDisplay>)));
    QObject::connect(m_text, SIGNAL(verse_starred(boost::shared_ptr<VerseDisplay>)), this, SLOT(raise_starred_verses()));
    QObject::connect(m_text, SIGNAL(verse_unstarred(boost::shared_ptr<VerseDisplay>)), m_starred_verses, SLOT(remove_starred_verse(boost::shared_ptr<VerseDisplay>)));
    QObject::connect(m_results, SIGNAL(verse_display_changed(boost::shared_ptr<VerseDisplay>)), m_text, SLOT(display_text(boost::shared_ptr<VerseDisplay>)));
    QObject::connect(m_browse, SIGNAL(verse_display_changed(boost::shared_ptr<VerseDisplay>)), m_text, SLOT(display_text(boost::shared_ptr<VerseDisplay>)));
    QObject::connect(m_starred_verses, SIGNAL(verse_display_changed(boost::shared_ptr<VerseDisplay>)), m_text, SLOT(display_text(boost::shared_ptr<VerseDisplay>)));
}

void UIBibleStudyWidget::set_font()
{
    QFont app_font = QApplication::font();
    app_font.setPointSize(12);
    app_font.setFamily("Bitstream Vera Sans");
    QApplication::setFont(app_font);
}

void UIBibleStudyWidget::initialize_widgets()
{
    m_tabs->addTab(m_browse, tr("&Verse Browser"));
    m_tabs->addTab(m_results, tr("Search &Results"));
    m_tabs->addTab(m_starred_verses, tr("&Starred Verses"));

    QHBoxLayout* bottom_row = new QHBoxLayout();
    bottom_row->addWidget(m_tabs);
    bottom_row->addWidget(m_text);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_search);
    mainLayout->addLayout(bottom_row);

    m_dummy_central_widget->setLayout(mainLayout);
    
    this->setCentralWidget(m_dummy_central_widget);
}

void UIBibleStudyWidget::initialize_status_bar()
{
    this->statusBar()->showMessage(tr("Ready"));
}

void UIBibleStudyWidget::initialize_actions()
{
    m_exit_action->setShortcuts(QKeySequence::Close);
    m_exit_action->setStatusTip(tr("Exit the BibleStudy"));
    connect(m_exit_action, SIGNAL(triggered()), this, SLOT(close()));

    m_about_action->setStatusTip(tr("Show the BibleStudy's About box"));
    connect(m_about_action, SIGNAL(triggered()), this, SLOT(about()));
}

void UIBibleStudyWidget::initialize_menus()
{
    m_file_menu = this->menuBar()->addMenu(tr("&File"));
    m_file_menu->addAction(m_exit_action);

    this->menuBar()->addSeparator();

    m_help_menu = menuBar()->addMenu(tr("&Help"));
    m_help_menu->addAction(m_about_action);
}

void UIBibleStudyWidget::raise_results()
{
    m_tabs->setCurrentWidget(m_results);
}

void UIBibleStudyWidget::raise_starred_verses()
{
    m_tabs->setCurrentWidget(m_starred_verses);
}

void UIBibleStudyWidget::about()
{
    QMessageBox::about(this, tr("About BibleStudy"), tr("This is the About box."));
}
