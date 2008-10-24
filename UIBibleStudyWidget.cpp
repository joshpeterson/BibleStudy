#include <boost/shared_ptr.hpp>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "SearchResultsModel.h"
#include "StarredVersesModel.h"
#include "UIBibleStudyWidget.h"
#include "UISearchWidget.h"
#include "UISearchResultsWidget.h"
#include "UIStarredVersesWidget.h"
#include "UITextViewWidget.h"

UIBibleStudyWidget::UIBibleStudyWidget(boost::shared_ptr<Translation> translation, QWidget *parent) :
    QWidget(parent),
    m_results_model(new SearchResultsModel(translation.get(), NULL)),
    m_starred_verses_model(new StarredVersesModel(translation)),
    m_search(new UISearchWidget(translation)),
    m_results(new UISearchResultsWidget(translation, m_results_model)),
    m_starred_verses(new UIStarredVersesWidget(translation, m_starred_verses_model)),
    m_text(new UITextViewWidget(translation, m_starred_verses_model))
{
    QObject::connect(m_search, SIGNAL(search_complete(boost::shared_ptr<ISearchResults>)),
                     m_results, SLOT(display_search_results(boost::shared_ptr<ISearchResults>)));

    QObject::connect(m_text, SIGNAL(verse_starred(boost::shared_ptr<VerseDisplay>)), m_starred_verses, SLOT(add_starred_verse(boost::shared_ptr<VerseDisplay>)));
    QObject::connect(m_text, SIGNAL(verse_unstarred(boost::shared_ptr<VerseDisplay>)), m_starred_verses, SLOT(remove_starred_verse(boost::shared_ptr<VerseDisplay>)));
    QObject::connect(m_results, SIGNAL(verse_display_changed(boost::shared_ptr<VerseDisplay>)), m_text, SLOT(display_text(boost::shared_ptr<VerseDisplay>)));
    QObject::connect(m_starred_verses, SIGNAL(verse_display_changed(boost::shared_ptr<VerseDisplay>)), m_text, SLOT(display_text(boost::shared_ptr<VerseDisplay>)));

    QHBoxLayout* bottom_row = new QHBoxLayout();

    bottom_row->addWidget(m_starred_verses);
    bottom_row->addWidget(m_text);

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addWidget(m_search);
    layout->addWidget(m_results);
    layout->addLayout(bottom_row);

    setLayout(layout);
}
