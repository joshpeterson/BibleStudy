#include <boost/scoped_ptr.hpp>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "UISearchWidget.h"
#include "BibleDatabase/TranslationManager.h"
#include "BibleDatabase/CommandPerformSearch.h"
#include "BibleDatabase/Translation.h"
#include "BibleDatabase/TranslationIterator.h"
#include "QtConnectHelper.h"

using namespace BibleStudy;
using namespace BibleDatabase;

UISearchWidget::UISearchWidget(boost::shared_ptr<const TranslationManager> translation_manager, QWidget* parent) : 
    QWidget(parent),
    m_translation_manager(translation_manager),
    m_search_button(new QPushButton(tr("Search"))),
    m_search_input_field(new QLineEdit()),
    m_translation_selection_row(new QHBoxLayout)
{
    QT_CONNECT(m_search_button, SIGNAL(clicked()), this, SLOT(perform_search()));
    QT_CONNECT(m_search_input_field, SIGNAL(returnPressed()), this, SLOT(perform_search()));

    QHBoxLayout* search_field_row = new QHBoxLayout;
    search_field_row->addWidget(m_search_input_field);
    search_field_row->addWidget(m_search_button);

    QVBoxLayout* layout = new QVBoxLayout;

    layout->addLayout(search_field_row);
    layout->addLayout(m_translation_selection_row);
    setLayout(layout);
}

void UISearchWidget::display_translation_check_boxes()
{
    for (TranslationIterator it = m_translation_manager->begin(); it != m_translation_manager->end(); ++it)
    {
        this->add_translation_check_box(*it);
    }
 
    m_translation_selection_row->addStretch(1);
}

void UISearchWidget::perform_search()
{
    if (!m_search_input_field->text().isEmpty())
    {
        emit search_started(m_search_input_field->text());

        std::vector<std::string> selected_translations;

        for (std::vector<QCheckBox*>::const_iterator it = m_translation_checkboxes.begin(); it != m_translation_checkboxes.end(); ++it)
        {
            if ((*it)->isChecked())
            {
                selected_translations.push_back((*it)->text().toStdString());
            }
        }

        CommandPerformSearch search_command(m_translation_manager, selected_translations, m_search_input_field->text().toStdString(), CaseSensitiveSearch);
        search_command.Execute();

        emit search_complete(search_command.get_results());
    }
}

void UISearchWidget::add_translation_check_box(boost::shared_ptr<const Translation> translation)
{
    QCheckBox* translation_check_box = new QCheckBox(translation->get_short_name().c_str());
    translation_check_box->setCheckState(Qt::Checked);
    m_translation_selection_row->addWidget(translation_check_box);
    m_translation_checkboxes.push_back(translation_check_box);
}

