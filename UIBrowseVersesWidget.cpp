#include "UIBrowseVersesWidget.h"
#include <QTreeView>
#include <QVBoxLayout>
#include <QLabel>
#include "BrowseVersesModel.h"
#include "VerseDisplay.h"
//#include "BrowseVersesDelegate.h"

UIBrowseVersesWidget::UIBrowseVersesWidget(boost::shared_ptr<BrowseVersesModel> browse_model, QWidget *parent) :
    QWidget(parent),
    m_browse_view(new QTreeView()),
    m_layout(new QVBoxLayout()),
    m_browse_model(browse_model)
{
    QObject::connect(m_browse_view, SIGNAL(clicked(QModelIndex)), this, SLOT(display_verse_text(QModelIndex)));

    m_browse_view->setModel(m_browse_model.get());

    /*BrowseVersesDelegate* browse_delegate = new BrowseVersesDelegate(this);
    m_browse_view->setItemDelegate(browse_delegate);*/
    
    QLabel* title = new QLabel(tr("Browse Verses"));

    m_layout->addWidget(title);
    m_layout->addWidget(m_browse_view);

    setLayout(m_layout);
}

void UIBrowseVersesWidget::display_verse_text(const QModelIndex& index)
{
    boost::shared_ptr<VerseDisplay> verse_to_display = m_browse_model->get_verse_display(index);
    if (verse_to_display->get_verse_id() != -1)
        emit verse_display_changed(verse_to_display);
}