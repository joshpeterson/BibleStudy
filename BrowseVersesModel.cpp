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
    if (!hasIndex(row, column, parent))
         return QModelIndex();

     IVerse* parentItem;

     if (!parent.isValid())
         parentItem = m_translation->get_entry(0);
     else
         parentItem = static_cast<IVerse*>(parent.internalPointer());

     IVerse* childItem = get_child(parentItem, row, column);
     if (childItem)
         return createIndex(row, column, childItem);
     else
         return QModelIndex();
}

QModelIndex BrowseVersesModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
         return QModelIndex();

     IVerse* childItem = static_cast<IVerse*>(index.internalPointer());
     IVerse* parentItem = get_parent(childItem, index.column());

     if (parentItem->get_unique_id() == 0)
         return QModelIndex();

     return createIndex(get_row(parentItem, index.column()), 0, parentItem);
}

int BrowseVersesModel::rowCount(const QModelIndex &parent) const
{
    return m_translation->num_books();
}

int BrowseVersesModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

IVerse* BrowseVersesModel::get_child(IVerse* parentItem, int row, int column) const
{
    int cur_verse_id = parentItem->get_unique_id();

    if (cur_verse_id >= m_translation->num_entries())
        return null;

    if (column == translation_column)
    {
        return null;    // Change this once we have more than one translation.
    }
    else if (column == book_column)
    {
        int next_verse_id = cur_verse_id + (row * m_translation->num_books());
        if (next_verse_id >= m_translation->num_entries())
            return null;    
        
        return m_translation->get_entry(next_verse_id);
    }
    else if (column == chapter_column)
    {
        int next_verse_id = cur_verse_id + (row * m_translation->num_chapters());
        if (next_verse_id >= m_translation->num_entries())
            return null;    
        
        return m_translation->get_entry(next_verse_id);
    }
    else if (column == verse_column)
    {
        int next_verse_id = cur_verse_id + row;
        if (next_verse_id >= m_translation->num_entries())
            return null;    
        
        return m_translation->get_entry(next_verse_id);
    }

    return null;
}

IVerse* BrowseVersesModel::get_parent(IVerse* childItem, int column) const
{
    int cur_verse_id = childItem->get_unique_id();

    if (column == translation_column)
    {
        return null;    // Change this once we have more than one translation.
    }
    else if (column == book_column)
    {   
        return m_translation->get_entry(0);
    }
    else if (column == chapter_column)
    {       
        return m_translation->get_entry(childItem->get_first_verse_in_book(cur_verse_id));
    }
    else if (column == verse_column)
    {
        return m_translation->get_entry(childItem->get_first_verse_in_chapter(cur_verse_id));
    }

    return null;
}

int BrowseVersesModel::get_row(IVerse* item, int column) const
{
    if (column == translation_column)
    {
        return null;    // Change this once we have more than one translation.
    }
    else if (column == book_column)
    {   
        return m_translation->get_entry(0);
    }
    else if (column == chapter_column)
    {       
        return m_translation->get_entry(childItem->get_first_verse_in_book(cur_verse_id));
    }
    else if (column == verse_column)
    {
        return m_translation->get_entry(childItem->get_first_verse_in_chapter(cur_verse_id));
    }
}
