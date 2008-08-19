#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "UISearchWidget.h"

UISearchWidget::UISearchWidget(QWidget* parent) : QWidget(parent)
{
    QPushButton* search_button = new QPushButton(tr("Search"));
    QLineEdit* search_input_field = new QLineEdit(tr("Search Text"));

    QHBoxLayout* search_field_row = new QHBoxLayout;
    search_field_row->addWidget(search_input_field);
    search_field_row->addWidget(search_button);

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