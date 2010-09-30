#ifndef __UI_STARRED_VERSES_WIDGET_H
#define __UI_STARRED_VERSES_WIDGET_H

#include <QWidget>
#include <QAbstractItemModel>
#include <boost/shared_ptr.hpp>

class QListView;

namespace BibleDatabase
{
class VerseDisplay;
}

namespace BibleStudyGui
{

class ISerializable;

class StarredVersesModel;

//! This class is an implementation of a view from the Qt Model/View framework for a list view which represents the verses the user has starred.
class UIStarredVersesWidget : public QWidget
{
    Q_OBJECT

public:
    //! Create a new instance of the UIStarredVersesWidget class.
    UIStarredVersesWidget(boost::shared_ptr<StarredVersesModel> starred_verses_model, QWidget* parent = 0);

    //! Listen to and process key presses.
    void keyPressEvent(QKeyEvent* key_event);

public slots:
    //! Add a verse to the collection of starred verses.
    void add_starred_verse(boost::shared_ptr<BibleDatabase::VerseDisplay> verse);

    //! Remove a verse from the collection of starred verses.
    void remove_starred_verse(boost::shared_ptr<BibleDatabase::VerseDisplay> verse);

    //! Get the verse at the given index and emit the verse_display_changed signal for that verse.
    void display_verse_text(const QModelIndex& index);

    //! Copies the selected verses in the starred verses to the clipboard.
    void copy_selected_verses();

    //! Select all starred verses.
    void select_all_verses();

    //! Build and display context menu when the user right clicks on the search results.
    void display_starred_verses_context_menu(const QPoint& position);

signals:
    //! Signal other widgets that a new verse should be displayed.
    void verse_display_changed(boost::shared_ptr<BibleDatabase::VerseDisplay> verse);

    //! Inform other widgets when the persisted parts of the starred verses widget have changed.
    void persistence_state_changed(boost::shared_ptr<ISerializable> starred_verses_state);

private:
    QListView* m_starred_verses_view;
    boost::shared_ptr<StarredVersesModel> m_starred_verses_model;

    void set_persistence_state();
};

}

#endif // __UI_STARRED_VERSES_WIDGET_H
