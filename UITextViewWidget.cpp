#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "UITextViewWidget.h"
#include "Translation.h"

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
    QObject::connect(m_more_button, SIGNAL(clicked()), this, SLOT(increase_displayed_context()));
    QObject::connect(m_less_button, SIGNAL(clicked()), this, SLOT(decrease_displayed_context()));

    QHBoxLayout* header_row = new QHBoxLayout;

    header_row->addWidget(m_title);
    header_row->addWidget(m_star_button);
    header_row->addWidget(m_less_button);
    header_row->addWidget(m_more_button);

    QHBoxLayout* footer_row = new QHBoxLayout;

    footer_row->addWidget(m_prev_button);
    footer_row->addWidget(m_next_button);

    m_text->setWordWrap(true);

    QVBoxLayout* layout = new QVBoxLayout;

    layout->addLayout(header_row);
    layout->addWidget(m_text);
    layout->addLayout(footer_row);

    setLayout(layout);
}

void UITextViewWidget::display_text(int unique_id, int num_entries_context)
{
    m_displayed_id = unique_id;
    m_displayed_context = num_entries_context;

    std::vector<boost::shared_ptr<const IVerse> > verses = m_translation->get_entry(unique_id, num_entries_context);
    m_title->setText(verse_collection_title(verses).c_str());
    m_text->setText(verse_collection_to_string(verses).c_str());
}

void UITextViewWidget::increase_displayed_context()
{
    m_displayed_context += 1;
    
    display_text(m_displayed_id, m_displayed_context);
}

void UITextViewWidget::decrease_displayed_context()
{
    int requested_displayed_context = m_displayed_context - 1;
    
    if (requested_displayed_context >= 0)
        m_displayed_context = requested_displayed_context;
    
    display_text(m_displayed_id, m_displayed_context);
}

