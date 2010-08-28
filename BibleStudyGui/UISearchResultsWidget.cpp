#include <algorithm>
#include <QAbstractItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include <QKeyEvent>
#include <QApplication>
#include <QClipboard>
#include <QPoint>
#include <QMenu>
#include <QKeySequence>
#include "UISearchResultsWidget.h"
#include "SearchResultsModel.h"
#include "../BibleDatabase/VerseDisplay.h"
#include "QtConnectHelper.h"

using namespace BibleStudyGui;
using namespace BibleDatabase;

UISearchResultsWidget::UISearchResultsWidget(boost::shared_ptr<SearchResultsModel> results_model,
                                             QWidget *parent) :
    QWidget(parent),
    m_results_view(new QTableView),
    m_results_status(new QLabel),
    m_filter_text(new QLineEdit),
    m_filter_delay_timer(new QTimer),
    m_filter_delay_typing_timeout_ms(500),
    m_proxy_model(new QSortFilterProxyModel(this)),
    m_results_model(results_model)
{
    QT_CONNECT(m_results_view, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(display_verse_text(const QModelIndex&)));
    QT_CONNECT(m_results_view, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(display_results_context_menu(const QPoint&)));
    QT_CONNECT(m_filter_text, SIGNAL(textChanged(QString)), this, SLOT(update_search_results_filter_delay_timer()));
    QT_CONNECT(m_filter_delay_timer, SIGNAL(timeout()), this, SLOT(change_search_results_filter()));

    QHeaderView* header = m_results_view->horizontalHeader();
    header->setResizeMode(QHeaderView::ResizeToContents);
    header->setStretchLastSection(true);

    m_results_view->setShowGrid(false);
    m_results_view->setTextElideMode(Qt::ElideNone);
    m_results_view->setSortingEnabled(false);
    m_results_view->setContextMenuPolicy(Qt::CustomContextMenu);
    
    m_proxy_model->setDynamicSortFilter(true);
    m_proxy_model->setFilterKeyColumn(SearchResultsModel::text_column);
    m_proxy_model->setSourceModel(m_results_model.get());
    m_results_view->setModel(m_proxy_model);

    m_results_status->setText(tr("No matches"));
    
    QLabel* filter_title = new QLabel(tr("Filter results:"));

    QGridLayout* top_line = new QGridLayout;
    top_line->setColumnMinimumWidth(1, 250);
    top_line->addWidget(m_results_status, 0, 0);
    top_line->addWidget(filter_title, 0, 2);
    top_line->addWidget(m_filter_text, 0, 3);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(top_line);
    layout->addWidget(m_results_view);

    setLayout(layout);
}

void UISearchResultsWidget::keyPressEvent(QKeyEvent* key_event)
{
    if ((key_event->key() == Qt::Key_C) && (key_event->modifiers() & Qt::ControlModifier))
    {
        copy_selected_search_results();
    }
    else
    {
        QWidget::keyPressEvent(key_event);
    }
}

void UISearchResultsWidget::display_search_results(boost::shared_ptr<ISearchResults> query)
{
    if (!m_filter_text->text().isEmpty())
    {
        m_filter_text->setText(QString());
    }
    m_results_model->SetResults(query);
    m_results_view->resizeRowsToContents();
    update_results_status();
}

void UISearchResultsWidget::display_verse_text(const QModelIndex& index)
{
    QModelIndex actualIndex = m_proxy_model->mapToSource(index);
    boost::shared_ptr<VerseDisplay> verse_to_display = m_results_model->get_verse_display(actualIndex);
    if (verse_to_display->get_verse_id() != -1)
        emit verse_display_changed(verse_to_display);
}

void UISearchResultsWidget::update_search_results_filter_delay_timer()
{
    m_filter_delay_timer->start(m_filter_delay_typing_timeout_ms);
}

void UISearchResultsWidget::change_search_results_filter()
{
    emit results_filter_started(m_filter_text->text());

    m_filter_delay_timer->stop();
    m_proxy_model->setFilterRegExp(QRegExp(m_filter_text->text()));
    m_results_view->resizeRowsToContents();
    update_results_status();

    emit results_filter_completed();
}

void UISearchResultsWidget::copy_selected_search_results()
{
    QItemSelectionModel* selection_model = m_results_view->selectionModel();
    if (selection_model)
    {
        QItemSelection item_selection = m_proxy_model->mapSelectionToSource(selection_model->selection());
        QModelIndexList selected_indexes = item_selection.indexes();

        std::sort(selected_indexes.begin(), selected_indexes.end());
        
        QModelIndex previous_index;
        QString text_to_paste;

        foreach (const QModelIndex& current_index, selected_indexes)
        {
            if (previous_index.row() != -1)
            {
                if (current_index.row() == previous_index.row())
                {
                    text_to_paste.append("\t");
                }
                else
                {
                    text_to_paste.append("\n");
                }
            }

            QVariant data = m_results_model->data(current_index, Qt::DisplayRole);
            text_to_paste.append(data.toString());
            
            previous_index = current_index;
        }
        QApplication::clipboard()->setText(text_to_paste);
    }
}

void UISearchResultsWidget::select_all_search_results()
{
    m_results_view->selectAll();
}

void UISearchResultsWidget::display_results_context_menu(const QPoint& position)
{
    QMenu *menu = new QMenu;
    menu->addAction(tr("Copy"), this, SLOT(copy_selected_search_results()), QKeySequence::Copy);
    menu->addSeparator();
    menu->addAction(tr("Select All"), this, SLOT(select_all_search_results()), QKeySequence::SelectAll);
    menu->exec(m_results_view->mapToGlobal(position + QPoint(42,30)));
}

void UISearchResultsWidget::update_results_status()
{
    int numberOfRowsFound = m_results_model->rowCount();
    int numberOfRowsDisplayed = m_proxy_model->rowCount();
    if (numberOfRowsFound == 0)
    {
        m_results_status->setText(tr("No matches"));
    }
    else if (numberOfRowsFound == 1)
    {
        if (numberOfRowsFound != numberOfRowsDisplayed)
        {
            m_results_status->setText(tr("%1 of %2 match").arg(numberOfRowsDisplayed).arg(numberOfRowsFound));
        }
        else
        {
            m_results_status->setText(tr("%1 match").arg(numberOfRowsFound));
        }
    }
    else
    {
        if (numberOfRowsFound != numberOfRowsDisplayed)
        {
            m_results_status->setText(tr("%1 of %2 matches").arg(numberOfRowsDisplayed).arg(numberOfRowsFound));
        }
        else
        {
            m_results_status->setText(tr("%1 matches").arg(numberOfRowsFound));
        }
    }
}

