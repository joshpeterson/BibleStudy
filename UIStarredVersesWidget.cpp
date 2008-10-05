#include <QListView>
#include <QVBoxLayout>
#include <QLabel>
#include "UIStarredVersesWidget.h"
#include "Translation.h"
#include "StarredVersesModel.h"

UIStarredVersesWidget::UIStarredVersesWidget(boost::shared_ptr<Translation> translation, QWidget* parent) :
    QWidget(parent),
    m_translation(translation),
    m_starred_verses_view(new QListView()),
    m_starred_verses_model(new StarredVersesModel(translation))
{
    QLabel* title = new QLabel(tr("Starred Verses"));

    m_starred_verses_view->setModel(m_starred_verses_model.get());

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addWidget(title);
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
