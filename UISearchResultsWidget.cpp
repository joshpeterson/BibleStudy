#include <QAbstractItemModel>
#include <QTableView>
#include <QHeaderView>
#include "UISearchResultsWidget.h"

UISearchResultsWidget::UISearchResultsWidget(QWidget *parent) :
    QWidget(parent),
    m_table_view(new QTableView)
{
    m_table_view->setSortingEnabled(true);
    m_table_view->setShowGrid(false);
    QHeaderView* header = m_table_view->horizontalHeader();
    header->setResizeMode(QHeaderView::ResizeToContents);
    header->setStretchLastSection(true);
}

void UISearchResultsWidget::display_search_results(boost::shared_ptr<QAbstractItemModel> model)
{
    m_table_view->setModel(model.get());

    emit search_results_updated();
}