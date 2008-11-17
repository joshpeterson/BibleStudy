#ifndef __UI_BROWSE_VERSES_WIDGET_H
#define __UI_BROWSE_VERSES_WIDGET_H

#include <QWidget>
#include <QAbstractItemModel>
#include <boost/shared_ptr.hpp>

class QVBoxLayout;
class QTreeView;
class Translation;
class BrowseVersesModel;
class VerseDisplay;

class UIBrowseVersesWidget : public QWidget
{
    Q_OBJECT

public:
    UIBrowseVersesWidget(boost::shared_ptr<BrowseVersesModel> browse_model, QWidget* parent = 0);

public slots:
    void display_verse_text(const QModelIndex& index);

signals:
    void verse_display_changed(boost::shared_ptr<VerseDisplay> verse);

private:
    QTreeView* m_browse_view;
    QVBoxLayout* m_layout;
    boost::shared_ptr<BrowseVersesModel> m_browse_model;
};

#endif // __UI_BROWSE_VERSES_WIDGET_H
