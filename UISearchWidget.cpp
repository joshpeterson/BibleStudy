#include <boost/scoped_ptr.hpp>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "UISearchWidget.h"
#include "TranslationManager.h"
#include "CommandPerformSearch.h"
#include "Translation.h"
#include "TranslationIterator.h"

using namespace BibleStudy;

UISearchWidget::UISearchWidget(boost::shared_ptr<const TranslationManager> translation_manager, QWidget* parent) : 
    QWidget(parent),
    m_translation_manager(translation_manager),
    m_search_button(new QPushButton(tr("Search"))),
    m_search_input_field(new QLineEdit())
{
    QObject::connect(m_search_button, SIGNAL(clicked()), this, SLOT(perform_search()));
    QObject::connect(m_search_input_field, SIGNAL(returnPressed()), this, SLOT(perform_search()));

    QHBoxLayout* search_field_row = new QHBoxLayout;
    search_field_row->addWidget(m_search_input_field);
    search_field_row->addWidget(m_search_button);

    QHBoxLayout* translation_selection_row = new QHBoxLayout;

    for (TranslationIterator it = translation_manager->begin(); it != translation_manager->end(); ++it)
    {
        this->add_translation_check_box(translation_selection_row, *it);
    }
    
    QVBoxLayout* layout = new QVBoxLayout;

    layout->addLayout(search_field_row);
    layout->addLayout(translation_selection_row);
    setLayout(layout);
}

void UISearchWidget::perform_search()
{
    std::vector<std::string> selected_translations;

    for (std::vector<QCheckBox*>::const_iterator it = m_translation_checkboxes.begin(); it != m_translation_checkboxes.end(); ++it)
    {
        if ((*it)->isChecked())
        {
            selected_translations.push_back((*it)->text().toStdString());
        }
    }

    CommandPerformSearch search_command(m_translation_manager, selected_translations, m_search_input_field->text().toStdString());
    search_command.Execute();
    emit search_complete(search_command.get_results());
}

void UISearchWidget::add_translation_check_box(QHBoxLayout* translation_selection_row, boost::shared_ptr<const Translation> translation)
{
    QCheckBox* translation_check_box = new QCheckBox(translation->get_short_name().c_str());
    translation_selection_row->addWidget(translation_check_box);
    m_translation_checkboxes.push_back(translation_check_box);
}

