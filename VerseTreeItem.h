#ifndef __VERSE_TREE_ITEM_H
#define __VERSE_TREE_ITEM_H

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

namespace BibleStudy
{

//! This class is used to represent a verse and its relationship to other verses in a Translation object that allow it to be displayed in a tree view.
class VerseTreeItem
{
public:
    //! This is the type of this VerseTreeItem.
    enum ItemType
    {
        translation = 0,
        book = 1,
        chapter = 2,
        verse = 3
    };

    //! Create a new instance of the VerseTreeItem class. The translation_long_name should be an empty string and the verse_id -1 for a root node in the tree.
    VerseTreeItem(std::string translation_long_name, int verse_id);

    //! Add a child item to this node.
    void add_child(boost::shared_ptr<VerseTreeItem> child, ItemType item_type);

    //! Get the long name of the Translation object for this node.
    std::string get_translation_name() const;

    //! Get the verse ID for this node.
    int get_verse_id() const;

    //! Get the type of item for this node.
    ItemType get_item_type() const;

    //! Get the parent of this node.
    VerseTreeItem* get_parent() const;

    //! Get the number of children for this node.
    int num_children() const;

    //! Get the child node at the given index.
    boost::shared_ptr<VerseTreeItem> get_child(int child_index) const;

    //! Get the row of this element in its parent node.
    int row() const;

private:
    std::string m_translation_long_name;
    int m_verse_id;
    ItemType m_item_type;
    VerseTreeItem* m_parent;
    std::vector< boost::shared_ptr<VerseTreeItem> > m_children;

    //! Set the parent node for this node.
    void set_parent(VerseTreeItem* parent);
};

}

#endif // __VERSE_TREE_ITEM_H
