#include <boost/shared_ptr.hpp>
#include <QVBoxLayout>
#include "UIBibleStudyWidget.h"
#include "UISearchWidget.h"
#include "UISearchResultsWidget.h"
#include "UITextViewWidget.h"

UIBibleStudyWidget::UIBibleStudyWidget(boost::shared_ptr<Translation> translation, QWidget *parent) :
    QWidget(parent),
    m_search(new UISearchWidget(translation)),
    m_results(new UISearchResultsWidget(translation)),
    m_text(new UITextViewWidget(translation))
{
    QObject::connect(m_search, SIGNAL(search_complete(boost::shared_ptr<ISearchResults>)),
                     m_results, SLOT(display_search_results(boost::shared_ptr<ISearchResults>)));

    QObject::connect(m_results, SIGNAL(verse_display_changed(int, int)), m_text, SLOT(display_text(int, int)));

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addWidget(m_search);
    layout->addWidget(m_results);
    layout->addWidget(m_text);

    setLayout(layout);
}
