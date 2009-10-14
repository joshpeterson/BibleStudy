#include <QAbstractItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include "UISearchResultsWidget.h"
#include "SearchResultsModel.h"
#include "VerseDisplay.h"

using namespace BibleStudy;

UISearchResultsWidget::UISearchResultsWidget(boost::shared_ptr<SearchResultsModel> results_model,
                                             QWidget *parent) :
    QWidget(parent),
    m_results_view(new QTableView),
    m_filter_text(new QLineEdit),
    m_proxy_model(new QSortFilterProxyModel(this)),
    m_filter_delay_timer(new QTimer),
    m_results_model(results_model),
    m_filter_delay_typing_timeout_ms(500)
{
    QObject::connect(m_results_view, SIGNAL(clicked(QModelIndex)), this, SLOT(display_verse_text(QModelIndex)));
    QObject::connect(m_filter_text, SIGNAL(textChanged(QString)), this, SLOT(update_search_results_filter_delay_timer()));
    QObject::connect(m_filter_delay_timer, SIGNAL(timeout()), this, SLOT(change_search_results_filter()));

    QHeaderView* header = m_results_view->horizontalHeader();
    header->setResizeMode(QHeaderView::ResizeToContents);
    header->setStretchLastSection(true);

    m_results_view->setShowGrid(false);
    m_results_view->setTextElideMode(Qt::ElideNone);
    m_results_view->setSortingEnabled(true);
    
    m_proxy_model->setDynamicSortFilter(true);
    m_proxy_model->setFilterKeyColumn(SearchResultsModel::text_column);
    m_proxy_model->setSourceModel(m_results_model.get());
    m_results_view->setModel(m_proxy_model);
    
    QLabel* results_title = new QLabel(tr("Search Results"));
    QLabel* filter_title = new QLabel(tr("Filter results:"));

    QGridLayout* top_line = new QGridLayout;
    top_line->setColumnMinimumWidth(1, 250);
    top_line->addWidget(results_title,0,0);
    top_line->addWidget(filter_title,0,2);
    top_line->addWidget(m_filter_text,0,3);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(top_line);
    layout->addWidget(m_results_view);

    setLayout(layout);
}

void UISearchResultsWidget::display_search_results(boost::shared_ptr<ISearchResults> query)
{
    m_results_model->SetResults(query);
    m_results_view->resizeRowsToContents();
}

void UISearchResultsWidget::display_verse_text(const QModelIndex& index)
{
    boost::shared_ptr<VerseDisplay> verse_to_display = m_results_model->get_verse_display(index);
    if (verse_to_display->get_verse_id() != -1)
        emit verse_display_changed(verse_to_display);
}

void UISearchResultsWidget::update_search_results_filter_delay_timer()
{
    m_filter_delay_timer->start(m_filter_delay_typing_timeout_ms);
}

void UISearchResultsWidget::change_search_results_filter()
{
    m_filter_delay_timer->stop();
    m_proxy_model->setFilterRegExp(QRegExp(m_filter_text->text()));
    m_results_view->resizeRowsToContents();
}

