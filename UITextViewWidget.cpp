#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "UITextViewWidget.h"

UITextViewWidget::UITextViewWidget(boost::shared_ptr<Translation> translation, QWidget* parent) :
    QWidget(parent),
    m_displayed_id(-1),
    m_displayed_context(0),
    m_translation(translation),
    m_title(new QLabel("Verse Title")),
    m_text(new QLabel("Verse text goes here.")),
    m_more_button(new QPushButton("More")),
    m_less_button(new QPushButton("Less")),
    m_star_button(new QPushButton("Star")),
    m_prev_button(new QPushButton("Prev")),
    m_next_button(new QPushButton("Next"))
{
    QHBoxLayout* header_row = new QHBoxLayout;

    header_row->addWidget(m_title);
    header_row->addWidget(m_star_button);
    header_row->addWidget(m_less_button);
    header_row->addWidget(m_more_button);

    QHBoxLayout* footer_row = new QHBoxLayout;

    footer_row->addWidget(m_prev_button);
    footer_row->addWidget(m_next_button);

    QVBoxLayout* layout = new QVBoxLayout;

    layout->addLayout(header_row);
    layout->addWidget(m_text);
    layout->addLayout(footer_row);

    setLayout(layout);
}

void UITextViewWidget::display_text(int unique_id, int num_entries_context)
{
}

