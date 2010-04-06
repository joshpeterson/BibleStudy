#include <QListView>
#include <QVBoxLayout>
#include <QLabel>
#include "UIStarredVersesWidget.h"
#include "StarredVersesModel.h"
#include "VerseDisplay.h"

using namespace BibleStudy;

UIStarredVersesWidget::UIStarredVersesWidget(boost::shared_ptr<StarredVersesModel> starred_verses_model,
                                             QWidget* parent) :
    QWidget(parent),
    m_starred_verses_view(new QListView()),
    m_starred_verses_model(starred_verses_model)
{
    QObject::connect(m_starred_verses_view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(display_verse_text(QModelIndex)));

    m_starred_verses_view->setModel(m_starred_verses_model.get());

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addWidget(m_starred_verses_view);

    setLayout(layout);
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
