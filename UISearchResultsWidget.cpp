#include <QAbstractItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include "UISearchResultsWidget.h"
#include "SearchResultsModel.h"

UISearchResultsWidget::UISearchResultsWidget(boost::shared_ptr<Translation> translation, QWidget *parent) :
    QWidget(parent),
    m_results_view(new QTableView),
    m_layout(new QVBoxLayout),
    m_results_model(new SearchResultsModel(translation.get(), NULL))
{
    m_results_view->setSortingEnabled(true);
    m_results_view->setShowGrid(false);
    QHeaderView* header = m_results_view->horizontalHeader();
    header->setResizeMode(QHeaderView::ResizeToContents);
    header->setStretchLastSection(true);

    m_results_view->setModel(m_results_model.get());
    
    QLabel* title = new QLabel(tr("Search Results"));

    m_layout->addWidget(title);
    m_layout->addWidget(m_results_view);

    m_results_view->hide();
    
    setLayout(m_layout);
}

void UISearchResultsWidget::display_search_results(boost::shared_ptr<ISearchResults> query)
{
    m_results_model->SetResults(query);
    m_results_view->show();
}
