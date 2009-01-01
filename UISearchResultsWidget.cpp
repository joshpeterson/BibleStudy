#include <QAbstractItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include "UISearchResultsWidget.h"
#include "SearchResultsModel.h"
#include "VerseDisplay.h"

UISearchResultsWidget::UISearchResultsWidget(boost::shared_ptr<SearchResultsModel> results_model,
                                             QWidget *parent) :
    QWidget(parent),
    m_results_view(new QTableView),
    m_layout(new QVBoxLayout),
    m_results_model(results_model)
{
    QObject::connect(m_results_view, SIGNAL(clicked(QModelIndex)), this, SLOT(display_verse_text(QModelIndex)));

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

void UISearchResultsWidget::display_verse_text(const QModelIndex& index)
{
    boost::shared_ptr<VerseDisplay> verse_to_display = m_results_model->get_verse_display(index);
    if (verse_to_display->get_verse_id() != -1)
        emit verse_display_changed(verse_to_display);
}
