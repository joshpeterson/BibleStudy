#include "UIBrowseVersesWidget.h"
#include <QTreeView>
#include <QVBoxLayout>
#include <QLabel>
#include "BrowseVersesModel.h"
#include "../BibleDatabase/VerseDisplay.h"
#include "QtConnectHelper.h"
//#include "BrowseVersesDelegate.h"

using namespace BibleStudyGui;
using namespace BibleDatabase;

UIBrowseVersesWidget::UIBrowseVersesWidget(boost::shared_ptr<BrowseVersesModel> browse_model, QWidget *parent) :
    QWidget(parent),
    m_browse_view(new QTreeView()),
    m_browse_model(browse_model)
{
    QT_CONNECT(m_browse_view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(display_verse_text(QModelIndex)));

    /*BrowseVersesDelegate* browse_delegate = new BrowseVersesDelegate(this);
    m_browse_view->setItemDelegate(browse_delegate);*/

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(m_browse_view);

    setLayout(layout);
}

void UIBrowseVersesWidget::set_browse_verses_model()
{
    m_browse_view->setModel(m_browse_model.get());
}

void UIBrowseVersesWidget::display_verse_text(const QModelIndex& index)
{
    boost::shared_ptr<VerseDisplay> verse_to_display = m_browse_model->get_verse_display(index);
    if (verse_to_display->get_verse_id() != -1)
        emit verse_display_changed(verse_to_display);
}
