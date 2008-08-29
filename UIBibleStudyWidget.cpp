#include <boost/shared_ptr.hpp>
#include <QVBoxLayout>
#include "UIBibleStudyWidget.h"
#include "UISearchWidget.h"
#include "UISearchResultsWidget.h"

UIBibleStudyWidget::UIBibleStudyWidget(boost::shared_ptr<Translation> translation, QWidget *parent) :
    QWidget(parent),
    m_search(new UISearchWidget(translation)),
    m_results(new UISearchResultsWidget),
    m_layout(new QVBoxLayout)
{
    QObject::connect(m_search, SIGNAL(search_complete(boost::shared_ptr<QAbstractItemModel>)),
                     m_results, SLOT(display_search_results(boost::shared_ptr<QAbstractItemModel>)));
    
    QObject::connect(m_results, SIGNAL(search_results_updated()), this, SLOT(refresh_search_results()));

    m_layout->addWidget(m_search);
    m_layout->addWidget(m_results);

    //m_results->hide();

    setLayout(m_layout);
}

void UIBibleStudyWidget::refresh_search_results()
{
    m_results->show();
}