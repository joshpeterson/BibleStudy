#ifndef __VERSE_TREE_ITEM_H
#define __VERSE_TREE_ITEM_H

#include <vector>
#include <boost/shared_ptr.hpp>

class VerseTreeItem
{
public:
    enum ItemType
    {
        translation = 0,
        book = 1,
        chapter = 2,
        verse = 3
    };

    VerseTreeItem(int verse_id);
    void add_child(boost::shared_ptr<VerseTreeItem> child, ItemType item_type);
    int get_verse_id() const;
    int get_child_index() const;
    ItemType get_item_type() const;
    VerseTreeItem* get_parent() const;
    int num_children() const;
    boost::shared_ptr<VerseTreeItem> get_child(int child_index) const;

private:
    int m_verse_id;
    int m_child_index;
    ItemType m_item_type;
    VerseTreeItem* m_parent;
    std::vector< boost::shared_ptr<VerseTreeItem> > m_children;

    void set_parent(VerseTreeItem* parent);
};

#endif // __VERSE_TREE_ITEM_H
