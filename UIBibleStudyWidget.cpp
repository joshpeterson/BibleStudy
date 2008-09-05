#include <boost/shared_ptr.hpp>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include "UIBibleStudyWidget.h"
#include "UISearchWidget.h"
#include "UISearchResultsWidget.h"

UIBibleStudyWidget::UIBibleStudyWidget(boost::shared_ptr<Translation> translation, QWidget *parent) :
    QWidget(parent),
    m_search(new UISearchWidget(translation)),
    m_results(new QTableView),
    m_layout(new QVBoxLayout)
{
    QObject::connect(m_search, SIGNAL(search_complete(boost::shared_ptr<QAbstractItemModel>)),
                     this, SLOT(display_search_results(boost::shared_ptr<QAbstractItemModel>)));
    
    //QObject::connect(m_results, SIGNAL(search_results_updated()), this, SLOT(refresh_search_results()));

    m_results->setSortingEnabled(true);
    m_results->setShowGrid(false);
    QHeaderView* header = m_results->horizontalHeader();
    header->setResizeMode(QHeaderView::ResizeToContents);
    header->setStretchLastSection(true);

    m_layout->addWidget(m_search);
    m_layout->addWidget(m_results);

    //m_results->hide();

    setLayout(m_layout);
}

void UIBibleStudyWidget::display_search_results(boost::shared_ptr<QAbstractItemModel> model)
{
    m_results->setModel(model.get());
    //m_table_view->show();

    //emit search_results_updated();
}

void UIBibleStudyWidget::refresh_search_results()
{
    //m_results->updateGeometry();
    //m_results->show();
}