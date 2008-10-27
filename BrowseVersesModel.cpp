#include "BrowseVersesModel.h"
#include "Translation.h"

BrowseVersesModel::BrowseVersesModel(boost::shared_ptr<Translation> translation, QObject *parent) :
    QAbstractItemModel(parent),
    m_translation(translation)
{
}

QVariant BrowseVersesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_translation->num_entries())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
            case translation_column:
                return QString("Douay-Rheims");
            
            case book_column:
                return m_translation->get_entry(index.row())->get_book().c_str();

            case chapter_column:
                return m_translation->get_entry(index.row())->get_chapter();

            case verse_column:
                return m_translation->get_entry(index.row())->get_verse();

            case text_column:
                return m_translation->get_entry(index.row())->get_text().c_str();
            
            default:
                return QVariant();
        }
    }
    else if (role == Qt::ToolTipRole)
    {
        switch (index.column())
        {
            case text_column:
                return verse_collection_to_string(m_translation->get_entry(index.row(), 2)).c_str();
            default:
                return QVariant();
        }
    }
    else
    {
        return QVariant();
    }
}

//Do I need this method?
Qt::ItemFlags BrowseVersesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
         return 0;

     return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant BrowseVersesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        switch (section)
        {
            case translation_column:
                return tr("Translation");
            
            case book_column:
                return tr("Book");

            case chapter_column:
                return tr("Chapter");

            case verse_column:
                return tr("Verse");

            case text_column:
                return tr("Text");

            default:
                return QVariant();
        }
    else
        return QString("%1").arg(section);
}

QModelIndex BrowseVersesModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex BrowseVersesModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int BrowseVersesModel::rowCount(const QModelIndex &parent) const
{
    return m_translation->num_entries();
}

int BrowseVersesModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}