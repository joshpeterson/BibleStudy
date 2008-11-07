#include <boost/shared_ptr.hpp>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "SearchResultsModel.h"
#include "StarredVersesModel.h"
#include "BrowseVersesModel.h"
#include "UIBibleStudyWidget.h"
#include "UISearchWidget.h"
#include "UISearchResultsWidget.h"
#include "UIStarredVersesWidget.h"
#include "UITextViewWidget.h"
#include "UIBrowseVersesWidget.h"

UIBibleStudyWidget::UIBibleStudyWidget(boost::shared_ptr<Translation> translation, QWidget *parent) :
    QWidget(parent),
    m_results_model(new SearchResultsModel(translation.get(), NULL)),
    m_starred_verses_model(new StarredVersesModel(translation)),
    m_browse_verses_model(new BrowseVersesModel(translation)),
    m_search(new UISearchWidget(translation)),
    m_results(new UISearchResultsWidget(translation, m_results_model)),
    m_starred_verses(new UIStarredVersesWidget(translation, m_starred_verses_model)),
    m_text(new UITextViewWidget(translation, m_starred_verses_model)),
    m_browse(new UIBrowseVersesWidget(m_browse_verses_model))
{
    QObject::connect(m_search, SIGNAL(search_complete(boost::shared_ptr<ISearchResults>)),
                     m_results, SLOT(display_search_results(boost::shared_ptr<ISearchResults>)));

    QObject::connect(m_text, SIGNAL(verse_starred(boost::shared_ptr<VerseDisplay>)), m_starred_verses, SLOT(add_starred_verse(boost::shared_ptr<VerseDisplay>)));
    QObject::connect(m_text, SIGNAL(verse_unstarred(boost::shared_ptr<VerseDisplay>)), m_starred_verses, SLOT(remove_starred_verse(boost::shared_ptr<VerseDisplay>)));
    QObject::connect(m_results, SIGNAL(verse_display_changed(boost::shared_ptr<VerseDisplay>)), m_text, SLOT(display_text(boost::shared_ptr<VerseDisplay>)));
    QObject::connect(m_starred_verses, SIGNAL(verse_display_changed(boost::shared_ptr<VerseDisplay>)), m_text, SLOT(display_text(boost::shared_ptr<VerseDisplay>)));

    QVBoxLayout* left_column = new QVBoxLayout();

    left_column->addWidget(m_browse);
    left_column->addWidget(m_starred_verses);

    QVBoxLayout* right_column = new QVBoxLayout();

    right_column->addWidget(m_search);
    right_column->addWidget(m_results);
    right_column->addWidget(m_text);

    QHBoxLayout* layout = new QHBoxLayout();

    layout->addLayout(left_column);
    layout->addLayout(right_column);

    setLayout(layout);
}
