#ifndef __BROWSE_VERSES_MODEL_H
#define __BROWSE_VERSES_MODEL_H

#include <boost/shared_ptr.hpp>
#include <QAbstractItemModel>

class Translation;

class BrowseVersesModel : QAbstractItemModel
{
    Q_OBJECT

public:
    BrowseVersesModel(boost::shared_ptr<Translation> translation, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:
    boost::shared_ptr<Translation> m_translation;

    enum ColumnType
    {
        translation_column = 0,
        book_column = 1,
        chapter_column = 2,
        verse_column = 3,
        text_column = 4
    };

};

#endif //__BROWSE_VERSES_MODEL_H
