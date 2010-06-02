#include <QLabel>
#include <QTextEdit>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "UITextViewWidget.h"
#include "BibleDatabase/TranslationManager.h"
#include "BibleDatabase/Translation.h"
#include "BibleDatabase/VerseDisplay.h"
#include "StarredVersesModel.h"

using namespace BibleStudy;

UITextViewWidget::UITextViewWidget(boost::shared_ptr<const TranslationManager> translation_manager,
                                   boost::shared_ptr<StarredVersesModel> starred_verses_model,
                                   QWidget* parent) :
    QWidget(parent),
    m_translation_manager(translation_manager),
    m_starred_verses_model(starred_verses_model),
    m_displayed_verse(new VerseDisplay("", -1, -1)),
    m_title(new QLabel()),
    m_text(new QTextEdit()),
    m_more_button(new QToolButton()),
    m_less_button(new QToolButton()),
    m_star_button(new QToolButton()),
    m_prev_button(new QToolButton()),
    m_next_button(new QToolButton())
{
    QObject::connect(m_more_button, SIGNAL(clicked()), this, SLOT(increase_displayed_context()));
    QObject::connect(m_less_button, SIGNAL(clicked()), this, SLOT(decrease_displayed_context()));
    QObject::connect(m_next_button, SIGNAL(clicked()), this, SLOT(display_next_verse()));
    QObject::connect(m_prev_button, SIGNAL(clicked()), this, SLOT(display_prev_verse()));
    QObject::connect(m_star_button, SIGNAL(clicked()), this, SLOT(change_star_button_icon()));
    QObject::connect(m_star_button, SIGNAL(clicked()), this, SLOT(change_starred_verse_state()));

    m_star_button->setEnabled(false);
    m_star_button->setIcon(QIcon("icons/star_off.png"));
    m_star_button->setToolTip(tr("Save this verse"));
    m_star_button->setCheckable(true);

    m_more_button->setEnabled(false);
    m_more_button->setIcon(QIcon("icons/plus.png"));
    m_more_button->setToolTip(tr("Show more context"));
    
    m_less_button->setEnabled(false);
    m_less_button->setIcon(QIcon("icons/minus.png"));
    m_less_button->setToolTip(tr("Show less context"));

    m_next_button->setEnabled(false);
    m_next_button->setIcon(QIcon("icons/next.png"));
    m_next_button->setToolTip(tr("Next verse"));

    m_prev_button->setEnabled(false);
    m_prev_button->setIcon(QIcon("icons/prev.png"));
    m_prev_button->setToolTip(tr("Previous verse"));

    QHBoxLayout* header_row = new QHBoxLayout;

    header_row->addWidget(m_title);
    header_row->addWidget(m_star_button);
    header_row->addWidget(m_less_button);
    header_row->addWidget(m_more_button);
    header_row->addWidget(m_prev_button);
    header_row->addWidget(m_next_button);

    m_text->setReadOnly(true);

    QVBoxLayout* layout = new QVBoxLayout;

    layout->addLayout(header_row);
    layout->addWidget(m_text);

    setLayout(layout);
}

void UITextViewWidget::display_text(boost::shared_ptr<VerseDisplay> verse)
{
    m_displayed_verse = verse;

    boost::shared_ptr<const Translation> translation = m_translation_manager->at(verse->get_translation());

    std::vector<boost::shared_ptr<const Verse> > verses = translation->get_verse(m_displayed_verse->get_verse_id(),
                                                                                 m_displayed_verse->get_num_verses_context());
    m_title->setText(verse_collection_title(verses, translation).c_str());
    m_text->setText(verse_collection_to_string(verses).c_str());

    m_star_button->setChecked(m_starred_verses_model->verse_starred(m_displayed_verse));

    change_star_button_icon();

    m_star_button->setEnabled(star_button_should_be_enabled());
    m_more_button->setEnabled(more_button_should_be_enabled());
    m_less_button->setEnabled(less_button_should_be_enabled());
    m_next_button->setEnabled(next_button_should_be_enabled());
    m_prev_button->setEnabled(prev_button_should_be_enabled());
}

void UITextViewWidget::increase_displayed_context()
{
    m_displayed_verse = boost::shared_ptr<VerseDisplay>(new VerseDisplay(m_displayed_verse->get_translation(), m_displayed_verse->get_verse_id(), 
                                                                         m_displayed_verse->get_num_verses_context() + 1));
    
    display_text(m_displayed_verse);
}

void UITextViewWidget::decrease_displayed_context()
{
    int requested_displayed_context = m_displayed_verse->get_num_verses_context() - 1;
    
    if (requested_displayed_context >= 0)
    {
        m_displayed_verse = boost::shared_ptr<VerseDisplay>(new VerseDisplay(m_displayed_verse->get_translation(), m_displayed_verse->get_verse_id(), 
                                                                             requested_displayed_context));
        display_text(m_displayed_verse);
    }
}

void UITextViewWidget::display_next_verse()
{
    int requested_next_verse = m_displayed_verse->get_verse_id() + 1;

    boost::shared_ptr<const Translation> translation = m_translation_manager->at(m_displayed_verse->get_translation());
    if (requested_next_verse < translation->num_entries()-1)
    {
        m_displayed_verse = boost::shared_ptr<VerseDisplay>(new VerseDisplay(m_displayed_verse->get_translation(), m_displayed_verse->get_verse_id() +1, 
                                                                             m_displayed_verse->get_num_verses_context()));
        display_text(m_displayed_verse);
        
        if (!next_button_should_be_enabled() && m_next_button->isEnabled())
            m_next_button->setEnabled(false);

        if (!m_prev_button->isEnabled())
            m_prev_button->setEnabled(true);
    }
}

void UITextViewWidget::display_prev_verse()
{
    int requested_next_verse = m_displayed_verse->get_verse_id() - 1;

    if (requested_next_verse >= 0)
    {
        m_displayed_verse = boost::shared_ptr<VerseDisplay>(new VerseDisplay(m_displayed_verse->get_translation(), m_displayed_verse->get_verse_id() - 1, 
                                                                             m_displayed_verse->get_num_verses_context()));
        display_text(m_displayed_verse);

        if (!prev_button_should_be_enabled() && m_prev_button->isEnabled())
            m_prev_button->setEnabled(false);
        
        if (!m_next_button->isEnabled())
            m_next_button->setEnabled(true);
    }
}

void UITextViewWidget::change_star_button_icon()
{
    if (m_star_button->isChecked())
        m_star_button->setIcon(QIcon("icons/star_on.png"));
    else
        m_star_button->setIcon(QIcon("icons/star_off.png"));
}

void UITextViewWidget::change_starred_verse_state()
{
    if (m_star_button->isChecked())
        emit verse_starred(m_displayed_verse);
    else
        emit verse_unstarred(m_displayed_verse);
}

bool UITextViewWidget::prev_button_should_be_enabled()
{
    return m_displayed_verse->get_verse_id() > 0;
}

bool UITextViewWidget::next_button_should_be_enabled()
{
    boost::shared_ptr<const Translation> translation = m_translation_manager->at(m_displayed_verse->get_translation());
    return m_displayed_verse->get_verse_id() != translation->num_entries()-1;
}

bool UITextViewWidget::more_button_should_be_enabled()
{
    return m_displayed_verse->get_verse_id() != -1;
}

bool UITextViewWidget::less_button_should_be_enabled()
{
    return m_displayed_verse->get_num_verses_context() > 0;
}

bool UITextViewWidget::star_button_should_be_enabled()
{
    return m_displayed_verse->get_verse_id() != -1;
}
