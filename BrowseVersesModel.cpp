#include "BrowseVersesModel.h"
#include "TranslationManager.h"
#include "Translation.h"
#include "Verse.h"
#include "VerseTreeItem.h"
#include "VerseDisplay.h"

using namespace BibleStudy;

BrowseVersesModel::BrowseVersesModel(boost::shared_ptr<const TranslationManager> translation_manager, QObject *parent) :
    QAbstractItemModel(parent),
    m_translation_manager(translation_manager)
{
}

QVariant BrowseVersesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    VerseTreeItem* item = static_cast<VerseTreeItem*>(index.internalPointer());
    if (!item)
        return QVariant();

    boost::shared_ptr<const Translation> translation = m_translation_manager->at(item->get_translation_name());
    if (index.row() >= translation->num_entries())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
        {
            switch (item->get_item_type())
            {
                case VerseTreeItem::translation:
                    return translation->get_long_name().c_str();
                
                case VerseTreeItem::book:
                    return translation->get_entry(item->get_verse_id())->get_book().c_str();

                case VerseTreeItem::chapter:
                    return QString(tr("Chapter ")) + QVariant(translation->get_entry(item->get_verse_id())->get_chapter()).toString();

                case VerseTreeItem::verse:
                    return QVariant(translation->get_entry(item->get_verse_id())->get_verse()).toString() + QString(": ") + translation->get_entry(item->get_verse_id())->get_text().c_str();
                
                default:
                    return QVariant();
            }
        }
        else if (index.column() == 1 && item->get_item_type() == VerseTreeItem::verse)
        {
            return translation->get_entry(item->get_verse_id())->get_text().c_str();
        }
    }
    else if (role == Qt::ToolTipRole)
    {
        if (item->get_item_type() == VerseTreeItem::verse)
        {
            return verse_collection_to_title_and_string_wrapped(translation->get_entry(item->get_verse_id(), 0), translation).c_str();
        }
    }
    return QVariant();
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
            case 0:
                return tr("Location");
            
            case 1:
                return tr("Verse Text");

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

    VerseTreeItem* parentItem;

     if (!parent.isValid())
         parentItem = m_translation_manager->get_verse_item_tree().get();
     else
         parentItem = static_cast<VerseTreeItem*>(parent.internalPointer());

     boost::shared_ptr<VerseTreeItem> childItem = parentItem->get_child(row);
     if (childItem)
         return createIndex(row, column, childItem.get());
     else
         return QModelIndex();
}

QModelIndex BrowseVersesModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
         return QModelIndex();

     VerseTreeItem* childItem = static_cast<VerseTreeItem*>(index.internalPointer());
     VerseTreeItem* parentItem = childItem->get_parent();

     if (parentItem->get_verse_id() == -1)
         return QModelIndex();

     return createIndex(parentItem->num_children(), 0, parentItem);
}

int BrowseVersesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    VerseTreeItem* parentItem;
    if (!parent.isValid())
        parentItem = m_translation_manager->get_verse_item_tree().get();
    else
        parentItem = static_cast<VerseTreeItem*>(parent.internalPointer());

    return parentItem->num_children();
}

int BrowseVersesModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 1;
}

boost::shared_ptr<VerseDisplay> BrowseVersesModel::get_verse_display(const QModelIndex &index) const
{
    VerseTreeItem* item = static_cast<VerseTreeItem*>(index.internalPointer());
    if (item->get_item_type() == VerseTreeItem::verse)
        return boost::shared_ptr<VerseDisplay>(new VerseDisplay(item->get_translation_name(), item->get_verse_id(), 2));
    else
        return boost::shared_ptr<VerseDisplay>(new VerseDisplay(item->get_translation_name(), -1, -1));
}
