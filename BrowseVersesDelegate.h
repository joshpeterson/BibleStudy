#ifndef __BROWSE_VERSES_DELEGATE_H
#define __BROWSE_VERSES_DELEGATE_H

#include <QAbstractItemDelegate>

class BrowseVersesDelegate : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    BrowseVersesDelegate(QObject* parent = 0);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex& index ) const;
};

#endif // __BROWSE_VERSES_DELEGATE_H
