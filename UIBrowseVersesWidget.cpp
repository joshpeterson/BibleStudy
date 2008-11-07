#include "UIBrowseVersesWidget.h"
#include <QTreeView>
#include <QVBoxLayout>
#include <QLabel>
#include "BrowseVersesModel.h"

UIBrowseVersesWidget::UIBrowseVersesWidget(boost::shared_ptr<BrowseVersesModel> browse_model, QWidget *parent) :
    QWidget(parent),
    m_browse_view(new QTreeView()),
    m_layout(new QVBoxLayout()),
    m_browse_model(browse_model)
{
    m_browse_view->setModel(m_browse_model.get());
    
    QLabel* title = new QLabel(tr("Browse Verses"));

    m_layout->addWidget(title);
    m_layout->addWidget(m_browse_view);

    setLayout(m_layout);
}