#ifndef __UI_BROWSE_VERSES_WIDGET_H
#define __UI_BROWSE_VERSES_WIDGET_H

#include <QWidget>
#include <QAbstractItemModel>
#include <boost/shared_ptr.hpp>

class QTreeView;

namespace BibleDatabase
{
class VerseDisplay;
}

namespace BibleStudy
{

class BrowseVersesModel;

//! This class is an implementation of a view from the Qt Model/View framework for a tree view that allows the user to browse the verses of all Translation objects.
class UIBrowseVersesWidget : public QWidget
{
    Q_OBJECT

public:
    //! Create a new instance of the UIBrowseVersesWidget class.
    UIBrowseVersesWidget(boost::shared_ptr<BrowseVersesModel> browse_model, QWidget* parent = 0);

public slots:
    //! Intialize the tree view with the browse verses model.
    void set_browse_verses_model();

    //! Get the verse at the given index and emit the verse_display_changed signal for that verse.
    void display_verse_text(const QModelIndex& index);

signals:
    //! Signal other widgets that a new verse should be displayed.
    void verse_display_changed(boost::shared_ptr<BibleDatabase::VerseDisplay> verse);

private:
    QTreeView* m_browse_view;
    boost::shared_ptr<BrowseVersesModel> m_browse_model;
};

}

#endif // __UI_BROWSE_VERSES_WIDGET_H
