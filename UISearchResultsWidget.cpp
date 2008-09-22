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
    QObject::connect(m_results_view, SIGNAL(doubleClicked(QModelIndex)), m_results_model.get(), SLOT(get_verse_display(QModelIndex)));
    QObject::connect(m_results_model.get(), SIGNAL(verse_display_changed(int, int)), this, SLOT(change_verse_display(int, int)));

    m_results_view->setSortingEnabled(true);
    m_results_view->setShowGrid(false);
    QHeaderView* header = m_results_view->horizontalHeader();
    header->setResizeMode(QHeaderView::ResizeToContents);
    header->setStretchLastSection(true);

    m_results_view->setModel(m_results_model.get());
    
    QLabel* title = new QLabel(tr("Search Results"));

    m_layout->addWidget(title);
    m_layout->addWidget(m_results_view);

    setLayout(m_layout);
}

void UISearchResultsWidget::display_search_results(boost::shared_ptr<ISearchResults> query)
{
    m_results_model->SetResults(query);
}

void UISearchResultsWidget::change_verse_display(int verse_id, int num_verses_context)
{
    emit verse_display_changed(verse_id, num_verses_context);
}
