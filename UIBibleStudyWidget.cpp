#include <boost/shared_ptr.hpp>
#include <QVBoxLayout>
#include "UIBibleStudyWidget.h"
#include "UISearchWidget.h"
#include "UISearchResultsWidget.h"

UIBibleStudyWidget::UIBibleStudyWidget(boost::shared_ptr<Translation> translation, QWidget *parent) :
    QWidget(parent),
    m_search(new UISearchWidget(translation)),
    m_results(new UISearchResultsWidget(translation))
{
    QObject::connect(m_search, SIGNAL(search_complete(boost::shared_ptr<ISearchResults>)),
                     m_results, SLOT(display_search_results(boost::shared_ptr<ISearchResults>)));

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addWidget(m_search);
    layout->addWidget(m_results);

    setLayout(layout);
}
