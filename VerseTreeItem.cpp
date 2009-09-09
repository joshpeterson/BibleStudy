#include "VerseTreeItem.h"

VerseTreeItem::VerseTreeItem(std::string translation_long_name, int verse_id) :
    m_translation_long_name(translation_long_name),
    m_verse_id(verse_id),
    m_parent(NULL)
{
}

void VerseTreeItem::add_child(boost::shared_ptr<VerseTreeItem> child, ItemType item_type)
{
    if (child != NULL)
    {
        child->set_parent(this);
        child->m_child_index = static_cast<int>(m_children.size());
        child->m_item_type = item_type;
        m_children.push_back(child);
    }
}

std::string VerseTreeItem::get_translation_name() const
{
    return m_translation_long_name;
}

int VerseTreeItem::get_verse_id() const
{
    return m_verse_id;
}

int VerseTreeItem::get_child_index() const
{
    return m_child_index;
}

VerseTreeItem::ItemType VerseTreeItem::get_item_type() const
{
    return m_item_type;
}

VerseTreeItem* VerseTreeItem::get_parent() const
{
    return m_parent;
}

int VerseTreeItem::num_children() const
{
    return static_cast<int>(m_children.size());
}

boost::shared_ptr<VerseTreeItem> VerseTreeItem::get_child(int child_index) const
{
    if (child_index < static_cast<int>(m_children.size()))
        return m_children[child_index];

    return boost::shared_ptr<VerseTreeItem>();
}

void VerseTreeItem::set_parent(VerseTreeItem* parent)
{
    m_parent = parent;
}
