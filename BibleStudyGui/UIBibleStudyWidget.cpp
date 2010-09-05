#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/pointer_cast.hpp>
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
#include <QTimer>
#include "../BibleDatabase/Translation.h"
#include "../BibleDatabase/TranslationManager.h"
#include "../BibleDatabase/TranslationLoader.h"
#include "../BibleDatabase/ICommand.h"
#include "../BibleDatabase/CommandLoadTranslation.h"
#include "SearchResultsModel.h"
#include "StarredVersesModel.h"
#include "BrowseVersesModel.h"
#include "UIBibleStudyWidget.h"
#include "UISearchWidget.h"
#include "UISearchResultsWidget.h"
#include "UIStarredVersesWidget.h"
#include "UITextViewWidget.h"
#include "UIBrowseVersesWidget.h"
#include "QtConnectHelper.h"
#include "BackgroundWorker.h"
#include "ProjectFileWriter.h"

using namespace BibleStudyGui;
using namespace BibleDatabase;

UIBibleStudyWidget::UIBibleStudyWidget(boost::shared_ptr<TranslationManager> translation_manager, boost::shared_ptr<const BibleDatabase::TranslationLoader> translation_loader) :
    m_translation_manager(translation_manager),
    m_translation_loader(translation_loader),
    m_translation_load_timer(new QTimer),
    m_translation_load_timeout_ms(500),
    m_results_model(new SearchResultsModel(translation_manager)),
    m_starred_verses_model(new StarredVersesModel(translation_manager)),
    m_browse_verses_model(new BrowseVersesModel(translation_manager)),
    m_project_file_writer(new ProjectFileWriter),
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

    m_project_file_writer->start();

    m_translation_load_timer->start(m_translation_load_timeout_ms);
}

void UIBibleStudyWidget::connect_signals()
{
    // Translation loading connections
    QT_CONNECT(m_translation_load_timer, SIGNAL(timeout()), this, SLOT(load_translations()));
    QT_CONNECT(this, SIGNAL(translations_loaded()), m_search, SLOT(display_translation_check_boxes()));
    QT_CONNECT(this, SIGNAL(translations_loaded()), m_browse, SLOT(set_browse_verses_model()));

    // UISearchWidget connections
    QT_CONNECT(m_search, SIGNAL(search_started(QString)), this, SLOT(display_search_status_bar_message(QString)));
    QT_CONNECT(m_search, SIGNAL(search_complete(boost::shared_ptr<BibleDatabase::ISearchResults>)), m_results, SLOT(display_search_results(boost::shared_ptr<BibleDatabase::ISearchResults>)));
    QT_CONNECT(m_search, SIGNAL(search_complete(boost::shared_ptr<BibleDatabase::ISearchResults>)), this, SLOT(raise_results()));
    QT_CONNECT(m_search, SIGNAL(search_complete(boost::shared_ptr<BibleDatabase::ISearchResults>)), this, SLOT(pop_status_bar_message()));

    // UITextViewWidget connections
    QT_CONNECT(m_text, SIGNAL(verse_starred(boost::shared_ptr<BibleDatabase::VerseDisplay>)), m_starred_verses, SLOT(add_starred_verse(boost::shared_ptr<BibleDatabase::VerseDisplay>)));
    QT_CONNECT(m_text, SIGNAL(verse_starred(boost::shared_ptr<BibleDatabase::VerseDisplay>)), this, SLOT(raise_starred_verses()));
    QT_CONNECT(m_text, SIGNAL(verse_unstarred(boost::shared_ptr<BibleDatabase::VerseDisplay>)), m_starred_verses, SLOT(remove_starred_verse(boost::shared_ptr<BibleDatabase::VerseDisplay>)));

    // UISearchResultsWidget connections
    QT_CONNECT(m_results, SIGNAL(verse_display_changed(boost::shared_ptr<BibleDatabase::VerseDisplay>)), m_text, SLOT(display_text(boost::shared_ptr<BibleDatabase::VerseDisplay>)));
    QT_CONNECT(m_results, SIGNAL(results_filter_started(QString)), this, SLOT(display_search_results_filter_status_bar_message(QString)));
    QT_CONNECT(m_results, SIGNAL(results_filter_completed()), this, SLOT(pop_status_bar_message()));

    // UIBrowseVersesWidget connections
    QT_CONNECT(m_browse, SIGNAL(verse_display_changed(boost::shared_ptr<BibleDatabase::VerseDisplay>)), m_text, SLOT(display_text(boost::shared_ptr<BibleDatabase::VerseDisplay>)));

    // UIStarredVersesWidget connections
    QT_CONNECT(m_starred_verses, SIGNAL(verse_display_changed(boost::shared_ptr<BibleDatabase::VerseDisplay>)), m_text, SLOT(display_text(boost::shared_ptr<BibleDatabase::VerseDisplay>)));
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
    this->push_status_bar_message(tr("Ready"));
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

void UIBibleStudyWidget::display_search_status_bar_message(QString search_text)
{
    this->push_status_bar_message(tr("Searching for ") + search_text);
}

void UIBibleStudyWidget::display_search_results_filter_status_bar_message(QString filter_text)
{
    if (!filter_text.isEmpty())
    {
        this->push_status_bar_message(tr("Filtering search results based on ") + filter_text);
    }
    else
    {
        this->push_status_bar_message(tr("Removing search results filter"));
    }
}

void UIBibleStudyWidget::push_status_bar_message(QString message)
{
    m_status_bar_messages.push(message);
    this->statusBar()->showMessage(message);
}

void UIBibleStudyWidget::pop_status_bar_message()
{
    if (!m_status_bar_messages.empty())
    {
        m_status_bar_messages.pop();
        this->statusBar()->showMessage(m_status_bar_messages.top());
    }
    else
    {
        this->statusBar()->clearMessage();
    }
}

void UIBibleStudyWidget::load_translations()
{
    m_translation_load_timer->stop();

    TranslationLoadInformation dr_load_information = {"Douay-Rheims", "../Translations/DR.buf" };
    TranslationLoadInformation kjv_load_information = {"King James Version", "../Translations/KJV.buf" };
    
    m_translations_to_load.push_back(dr_load_information);
    m_translations_to_load.push_back(kjv_load_information);

    if (!m_translations_to_load.empty())
    {
        this->setEnabled(false);
        start_next_translation_load();
    }
}

void UIBibleStudyWidget::translation_loaded()
{
    QT_DISCONNECT(m_load_translation_worker.get(), SIGNAL(finished()), this, SLOT(translation_loaded()));

    boost::shared_ptr<CommandLoadTranslation> command_load_translation = boost::dynamic_pointer_cast<CommandLoadTranslation>(m_command_load_translation);
    boost::shared_ptr<const Translation> translation = command_load_translation->get_translation();
    m_translation_manager->add_translation(translation);
    this->pop_status_bar_message();

    if (!m_translations_to_load.empty())
    {
        start_next_translation_load();
    }
    else
    {
        this->setEnabled(true);
        emit translations_loaded();
    }
}

void UIBibleStudyWidget::start_next_translation_load()
{
    TranslationLoadInformation load_information = m_translations_to_load.front();
    m_translations_to_load.pop_front();

    this->push_status_bar_message(tr("Loading translation ") + tr(load_information.translation_long_name.c_str()));
    m_command_load_translation = boost::shared_ptr<ICommand>(new CommandLoadTranslation(m_translation_loader, load_information.translation_file));
    m_load_translation_worker = boost::make_shared<BackgroundWorker>(m_command_load_translation);

    QT_CONNECT(m_load_translation_worker.get(), SIGNAL(finished()), this, SLOT(translation_loaded()));

    m_load_translation_worker->start();
}