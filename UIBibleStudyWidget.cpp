#include <boost/shared_ptr.hpp>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDockWidget>
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
    m_search(new UISearchWidget(translation_manager)),
    m_results_dock(new QDockWidget(tr("Search Results"), this)),
    m_results(new UISearchResultsWidget(m_results_model, m_results_dock)),
    m_starred_verses_dock(new QDockWidget(tr("Starred Verses"), this)),
    m_starred_verses(new UIStarredVersesWidget(m_starred_verses_model, m_starred_verses_dock)),
    m_text_dock(new QDockWidget(tr("Verse Text"), this)),
    m_text(new UITextViewWidget(translation_manager, m_starred_verses_model, m_text_dock)),
    m_browse_dock(new QDockWidget(tr("Verse Browser"), this)),
    m_browse(new UIBrowseVersesWidget(m_browse_verses_model, m_browse_dock))
{
    QObject::connect(m_search, SIGNAL(search_complete(boost::shared_ptr<ISearchResults>)), m_results, SLOT(display_search_results(boost::shared_ptr<ISearchResults>)));
    QObject::connect(m_search, SIGNAL(search_complete(boost::shared_ptr<ISearchResults>)), this, SLOT(raise_results()));
    QObject::connect(m_text, SIGNAL(verse_starred(boost::shared_ptr<VerseDisplay>)), m_starred_verses, SLOT(add_starred_verse(boost::shared_ptr<VerseDisplay>)));
    QObject::connect(m_text, SIGNAL(verse_unstarred(boost::shared_ptr<VerseDisplay>)), m_starred_verses, SLOT(remove_starred_verse(boost::shared_ptr<VerseDisplay>)));
    QObject::connect(m_results, SIGNAL(verse_display_changed(boost::shared_ptr<VerseDisplay>)), m_text, SLOT(display_text(boost::shared_ptr<VerseDisplay>)));
    QObject::connect(m_results, SIGNAL(verse_display_changed(boost::shared_ptr<VerseDisplay>)), this, SLOT(raise_text()));
    QObject::connect(m_browse, SIGNAL(verse_display_changed(boost::shared_ptr<VerseDisplay>)), m_text, SLOT(display_text(boost::shared_ptr<VerseDisplay>)));
    QObject::connect(m_browse, SIGNAL(verse_display_changed(boost::shared_ptr<VerseDisplay>)), this, SLOT(raise_text()));
    QObject::connect(m_starred_verses, SIGNAL(verse_display_changed(boost::shared_ptr<VerseDisplay>)), m_text, SLOT(display_text(boost::shared_ptr<VerseDisplay>)));
    QObject::connect(m_starred_verses, SIGNAL(verse_display_changed(boost::shared_ptr<VerseDisplay>)), this, SLOT(raise_text()));

    QFont app_font = QApplication::font();
    app_font.setPointSize(12);
    app_font.setFamily("Bitstream Vera Sans");
    QApplication::setFont(app_font);

    m_search->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_results_dock->setWidget(m_results);
    m_starred_verses_dock->setWidget(m_starred_verses);
    m_text_dock->setWidget(m_text);
    m_browse_dock->setWidget(m_browse);
    
    this->addDockWidget(Qt::BottomDockWidgetArea, m_browse_dock);
    this->tabifyDockWidget(m_browse_dock, m_starred_verses_dock);
    this->tabifyDockWidget(m_browse_dock, m_results_dock);
    this->tabifyDockWidget(m_browse_dock, m_text_dock);
    
    this->setCentralWidget(m_search);
}

void UIBibleStudyWidget::raise_text()
{
    m_text_dock->raise();
}

void UIBibleStudyWidget::raise_results()
{
    m_results_dock->raise();
}