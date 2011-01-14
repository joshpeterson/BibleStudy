#include <QListView>
#include <QVBoxLayout>
#include <QLabel>
#include <QClipboard>
#include <QPoint>
#include <QMenu>
#include <QKeySequence>
#include <QKeyEvent>
#include <QApplication>
#include "UIStarredVersesWidget.h"
#include "StarredVersesModel.h"
#include "../BibleDatabase/VerseDisplay.h"
#include "QtConnectHelper.h"

using namespace BibleStudyGui;
using namespace BibleDatabase;

UIStarredVersesWidget::UIStarredVersesWidget(boost::shared_ptr<StarredVersesModel> starred_verses_model,
                                             QWidget* parent) :
    QWidget(parent),
    m_starred_verses_view(new QListView()),
    m_starred_verses_model(starred_verses_model)
{
    QT_CONNECT(m_starred_verses_view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(display_verse_text(QModelIndex)));
    QT_CONNECT(m_starred_verses_view, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(display_starred_verses_context_menu(const QPoint&)));

    m_starred_verses_view->setModel(m_starred_verses_model.get());
    m_starred_verses_view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_starred_verses_view->setContextMenuPolicy(Qt::CustomContextMenu);

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addWidget(m_starred_verses_view);

    setLayout(layout);
}

void UIStarredVersesWidget::keyPressEvent(QKeyEvent* key_event)
{
    if ((key_event->key() == Qt::Key_C) && (key_event->modifiers() & Qt::ControlModifier))
    {
        copy_selected_verses();
    }
    else
    {
        QWidget::keyPressEvent(key_event);
    }
}

void UIStarredVersesWidget::add_starred_verse(boost::shared_ptr<VerseDisplay> verse)
{
    m_starred_verses_model->add_starred_verse(verse);
}

void UIStarredVersesWidget::remove_starred_verse(boost::shared_ptr<VerseDisplay> verse)
{
    m_starred_verses_model->remove_starred_verse(verse);
}

void UIStarredVersesWidget::display_verse_text(const QModelIndex& index)
{
    boost::shared_ptr<VerseDisplay> verse_to_display = m_starred_verses_model->get_verse_display(index);
    if (verse_to_display->get_verse_id() != -1)
        emit verse_display_changed(verse_to_display);
}

void UIStarredVersesWidget::copy_selected_verses()
{
    QItemSelectionModel* selection_model = m_starred_verses_view->selectionModel();
    if (selection_model)
    {
        QModelIndexList selected_indexes = selection_model->selectedIndexes();

        std::sort(selected_indexes.begin(), selected_indexes.end());
        
        QModelIndex previous_index;
        QString text_to_paste;

        foreach (const QModelIndex& current_index, selected_indexes)
        {
            if (previous_index.row() != -1)
            {
                text_to_paste.append("\n");
            }

            QVariant data = m_starred_verses_model->data(current_index, Qt::DisplayRole);
            text_to_paste.append(data.toString());
            
            previous_index = current_index;
        }
        QApplication::clipboard()->setText(text_to_paste);
    }
}

void UIStarredVersesWidget::select_all_verses()
{
    m_starred_verses_view->selectAll();
}

void UIStarredVersesWidget::display_starred_verses_context_menu(const QPoint& position)
{
    QMenu *menu = new QMenu;
    menu->addAction(tr("Copy"), this, SLOT(copy_selected_verses()), QKeySequence::Copy);
    menu->addSeparator();
    menu->addAction(tr("Select All"), this, SLOT(select_all_verses()), QKeySequence::SelectAll);
    menu->exec(m_starred_verses_view->mapToGlobal(position + QPoint(10, 5)));
}
