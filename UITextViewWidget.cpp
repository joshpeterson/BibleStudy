#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "UITextViewWidget.h"
#include "Translation.h"

UITextViewWidget::UITextViewWidget(boost::shared_ptr<Translation> translation, QWidget* parent) :
    QWidget(parent),
    m_displayed_id(-1),
    m_displayed_context(0),
    m_translation(translation),
    m_title(new QLabel()),
    m_text(new QTextEdit()),
    m_more_button(new QToolButton()),
    m_less_button(new QToolButton()),
    m_star_button(new QPushButton("Star")),
    m_prev_button(new QPushButton("Prev")),
    m_next_button(new QPushButton("Next"))
{
    QObject::connect(m_more_button, SIGNAL(clicked()), this, SLOT(increase_displayed_context()));
    QObject::connect(m_less_button, SIGNAL(clicked()), this, SLOT(decrease_displayed_context()));
    QObject::connect(m_next_button, SIGNAL(clicked()), this, SLOT(display_next_verse()));
    QObject::connect(m_prev_button, SIGNAL(clicked()), this, SLOT(display_prev_verse()));

    m_star_button->setEnabled(false);
    m_star_button->setToolTip(tr("Save this verse"));

    m_next_button->setEnabled(false);
    m_prev_button->setEnabled(false);

    m_more_button->setEnabled(false);
    m_more_button->setIcon(QIcon("icons/plus.png"));
    m_more_button->setToolTip(tr("Show more context"));
    
    m_less_button->setEnabled(false);
    m_less_button->setIcon(QIcon("icons/minus.png"));
    m_more_button->setToolTip(tr("Show less context"));

    QHBoxLayout* header_row = new QHBoxLayout;

    header_row->addWidget(m_title);
    header_row->addWidget(m_star_button);
    header_row->addWidget(m_less_button);
    header_row->addWidget(m_more_button);

    QHBoxLayout* footer_row = new QHBoxLayout;

    footer_row->addWidget(m_prev_button);
    footer_row->addWidget(m_next_button);

    m_text->setReadOnly(true);

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

    m_star_button->setEnabled(star_button_should_be_enabled());
    m_more_button->setEnabled(more_button_should_be_enabled());
    m_less_button->setEnabled(less_button_should_be_enabled());
    m_next_button->setEnabled(next_button_should_be_enabled());
    m_prev_button->setEnabled(prev_button_should_be_enabled());
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

void UITextViewWidget::display_next_verse()
{
    int requested_next_verse = m_displayed_id + 1;

    if (requested_next_verse < m_translation->num_entries()-1)
    {
        m_displayed_id += 1;
        display_text(m_displayed_id, m_displayed_context);
        
        if (!next_button_should_be_enabled() && m_next_button->isEnabled())
            m_next_button->setEnabled(false);

        if (!m_prev_button->isEnabled())
            m_prev_button->setEnabled(true);
    }
}

void UITextViewWidget::display_prev_verse()
{
    int requested_next_verse = m_displayed_id - 1;

    if (requested_next_verse >= 0)
    {
        m_displayed_id -= 1;
        display_text(m_displayed_id, m_displayed_context);

        if (!prev_button_should_be_enabled() && m_prev_button->isEnabled())
            m_prev_button->setEnabled(false);
        
        if (!m_next_button->isEnabled())
            m_next_button->setEnabled(true);
    }
}

bool UITextViewWidget::prev_button_should_be_enabled()
{
    return m_displayed_id > 0;
}

bool UITextViewWidget::next_button_should_be_enabled()
{
    return m_displayed_id != m_translation->num_entries()-1;
}

bool UITextViewWidget::more_button_should_be_enabled()
{
    return true;
}

bool UITextViewWidget::less_button_should_be_enabled()
{
    return m_displayed_context > 0;
}

bool UITextViewWidget::star_button_should_be_enabled()
{
    return true;
}