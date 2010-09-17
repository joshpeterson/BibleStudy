#include <algorithm>
#include <string>
#include <boost/scoped_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "UISearchWidget.h"
#include "../BibleDatabase/TranslationManager.h"
#include "../BibleDatabase/CommandPerformSearch.h"
#include "../BibleDatabase/Translation.h"
#include "../BibleDatabase/TranslationIterator.h"
#include "QtConnectHelper.h"
#include "BackgroundWorker.h"
#include "ISerializable.h"
#include "SearchPersistenceState.h"

using namespace BibleStudyGui;
using namespace BibleDatabase;

UISearchWidget::UISearchWidget(boost::shared_ptr<const TranslationManager> translation_manager, QWidget* parent) : 
    QWidget(parent),
    m_translation_manager(translation_manager),
    m_search_button(new QPushButton(tr("Search"))),
    m_search_input_field(new QLineEdit()),
    m_translation_selection_row(new QHBoxLayout),
    m_match_case_checkbox(new QCheckBox(tr("Match case"))),
    m_match_whole_word_checkbox(new QCheckBox(tr("Whole words")))
{
    QT_CONNECT(m_search_button, SIGNAL(clicked()), this, SLOT(on_perform_search()));
    QT_CONNECT(m_search_input_field, SIGNAL(returnPressed()), this, SLOT(on_perform_search()));

    QT_CONNECT(m_search_input_field, SIGNAL(textChanged(const QString&)), this, SLOT(on_persisted_widget_state_changed()));
    QT_CONNECT(m_match_case_checkbox, SIGNAL(stateChanged(int)), this, SLOT(on_persisted_widget_state_changed()));
    QT_CONNECT(m_match_whole_word_checkbox, SIGNAL(stateChanged(int)), this, SLOT(on_persisted_widget_state_changed()));

    m_match_case_checkbox->setChecked(true);
    m_match_whole_word_checkbox->setChecked(false);

    QVBoxLayout* search_options = new QVBoxLayout;
    search_options->addWidget(m_match_case_checkbox);
    search_options->addWidget(m_match_whole_word_checkbox);

    QHBoxLayout* search_field_row = new QHBoxLayout;
    search_field_row->addWidget(m_search_input_field);
    search_field_row->addWidget(m_search_button);
    search_field_row->addLayout(search_options);

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

void UISearchWidget::on_perform_search()
{
    if (!m_search_input_field->text().isEmpty())
    {
        emit search_started(m_search_input_field->text());

		std::vector<std::string> selected_translations;
		std::vector<QString> temporary_selected_translations = this->get_selected_translations();
		std::transform(temporary_selected_translations.begin(), temporary_selected_translations.end(), std::back_inserter(selected_translations), boost::bind(&QString::toStdString, boost::lambda::_1));

        int search_option = CaseSensitive;
        if (m_match_case_checkbox->checkState() == Qt::Unchecked)
        {
            search_option = CaseInsensitive;
        }

        if (m_match_whole_word_checkbox->checkState() == Qt::Checked)
        {
            search_option |= MatchWholeWord;
        }

        m_command_perform_search = boost::shared_ptr<ICommand>(new CommandPerformSearch(m_translation_manager, selected_translations, m_search_input_field->text().toStdString(), search_option));
        m_search_worker = boost::make_shared<BackgroundWorker>(m_command_perform_search);

        QT_CONNECT(m_search_worker.get(), SIGNAL(finished()), this, SLOT(on_search_worker_finished()));
        
        m_search_worker->start();
    }
}

void UISearchWidget::on_search_worker_finished()
{
    QT_DISCONNECT(m_search_worker.get(), SIGNAL(finished()), this, SLOT(on_search_worker_finished()));

    boost::shared_ptr<CommandPerformSearch> command_perform_search = boost::dynamic_pointer_cast<CommandPerformSearch>(m_command_perform_search);
    emit search_complete(command_perform_search->get_results());
}

void UISearchWidget::on_persisted_widget_state_changed()
{
	boost::shared_ptr<ISerializable> current_search_state = this->get_persisted_state();
	emit persistence_state_changed(current_search_state);
}

void UISearchWidget::add_translation_check_box(boost::shared_ptr<const Translation> translation)
{
    QCheckBox* translation_check_box = new QCheckBox(translation->get_short_name().c_str());
    translation_check_box->setCheckState(Qt::Checked);
    m_translation_selection_row->addWidget(translation_check_box);
    m_translation_checkboxes.push_back(translation_check_box);

	QT_CONNECT(translation_check_box, SIGNAL(stateChanged(int)), this, SLOT(on_persisted_widget_state_changed()));
}

boost::shared_ptr<ISerializable> UISearchWidget::get_persisted_state() const
{
	std::vector<QString> selected_translations = this->get_selected_translations();
	boost::shared_ptr<ISerializable> persistence_state = boost::shared_ptr<ISerializable>(new SearchPersistenceState(m_search_input_field->text(), m_match_case_checkbox->isChecked(), m_match_whole_word_checkbox->isChecked(), selected_translations));

	return persistence_state;
}

std::vector<QString> UISearchWidget::get_selected_translations() const
{
	std::vector<QString> selected_translations;

    for (std::vector<QCheckBox*>::const_iterator it = m_translation_checkboxes.begin(); it != m_translation_checkboxes.end(); ++it)
    {
        if ((*it)->isChecked())
        {
            selected_translations.push_back((*it)->text());
        }
    }

	return selected_translations;
}