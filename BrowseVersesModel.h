#ifndef __BROWSE_VERSES_MODEL_H
#define __BROWSE_VERSES_MODEL_H

#include <boost/shared_ptr.hpp>
#include <QAbstractItemModel>

class TranslationManager;
class VerseDisplay;

class BrowseVersesModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    BrowseVersesModel(boost::shared_ptr<const TranslationManager> translation_manager, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    boost::shared_ptr<VerseDisplay> get_verse_display(const QModelIndex &index) const;

private:
    boost::shared_ptr<const TranslationManager> m_translation_manager;
};

#endif //__BROWSE_VERSES_MODEL_H
