#include "BrowseVersesDelegate.h"
#include <QPainter>

BrowseVersesDelegate::BrowseVersesDelegate(QObject *parent) :
    QAbstractItemDelegate(parent)
{
}

void BrowseVersesDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    painter->save();

    if (option.state & QStyle::State_Selected)
        painter->setBrush(option.palette.highlightedText());
    else
        painter->setBrush(QBrush(Qt::red));

    painter->drawText(option.rect, Qt::AlignLeft, index.data().toString());

    painter->restore();
}

QSize BrowseVersesDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return QSize(option.rect.width() + 10, option.rect.height() + 10);
}