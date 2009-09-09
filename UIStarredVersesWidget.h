#ifndef __UI_STARRED_VERSES_WIDGET_H
#define __UI_STARRED_VERSES_WIDGET_H

#include <QWidget>
#include <QAbstractItemModel>
#include <boost/shared_ptr.hpp>

class QListView;
class StarredVersesModel;
class VerseDisplay;

class UIStarredVersesWidget : public QWidget
{
    Q_OBJECT

public:
    UIStarredVersesWidget(boost::shared_ptr<StarredVersesModel> starred_verses_model, QWidget* parent = 0);

public slots:
    void add_starred_verse(boost::shared_ptr<VerseDisplay> verse);
    void remove_starred_verse(boost::shared_ptr<VerseDisplay> verse);
    void display_verse_text(const QModelIndex& index);

signals:
    void verse_display_changed(boost::shared_ptr<VerseDisplay> verse);

private:
    QListView* m_starred_verses_view;
    boost::shared_ptr<StarredVersesModel> m_starred_verses_model;
};

#endif // __UI_STARRED_VERSES_WIDGET_H
