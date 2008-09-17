#include <boost/scoped_ptr.hpp>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "UISearchWidget.h"
#include "SearchResultsSerial.h"
#include "Translation.h"
#include "CommandPerformSearch.h"

UISearchWidget::UISearchWidget(boost::shared_ptr<Translation> translation, QWidget* parent) : 
    QWidget(parent),
    m_translation(translation),
    m_search_button(new QPushButton(tr("Search"))),
    m_search_input_field(new QLineEdit(tr("Search Text")))
{
    QObject::connect(m_search_button, SIGNAL(clicked()), this, SLOT(perform_search()));

    QHBoxLayout* search_field_row = new QHBoxLayout;
    search_field_row->addWidget(m_search_input_field);
    search_field_row->addWidget(m_search_button);

    QCheckBox* dr_check_box = new QCheckBox(tr("DR"));
    QCheckBox* ltv_check_box = new QCheckBox(tr("LTV"));
    QCheckBox* rsv_check_box = new QCheckBox(tr("RSV"));
    QCheckBox* nab_check_box = new QCheckBox(tr("NAB"));

    QHBoxLayout* translation_selection_row = new QHBoxLayout;

    translation_selection_row->addWidget(dr_check_box);
    translation_selection_row->addWidget(ltv_check_box);
    translation_selection_row->addWidget(rsv_check_box);
    translation_selection_row->addWidget(nab_check_box);

    QVBoxLayout* layout = new QVBoxLayout;

    layout->addLayout(search_field_row);
    layout->addLayout(translation_selection_row);
    setLayout(layout);
}

void UISearchWidget::perform_search()
{
    boost::scoped_ptr<CommandPerformSearch> search_command(m_translation, m_search_input_field->text().toStdString());
    search_command();
    emit search_complete(search_command->get_results());
//    boost::shared_ptr<ISearchResults> query(new SearchResultsSerial(m_search_input_field->text().toStdString()));
//    std::vector<boost::shared_ptr<ISearchResults> > results;
//    results.push_back(query);
//
//    m_translation->search(results);
//
//    emit search_complete(query);
//}

