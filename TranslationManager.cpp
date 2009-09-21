#include "TranslationManager.h"
#include "Translation.h"
#include "VerseTreeItem.h"

using namespace BibleStudy;

TranslationManager::TranslationManager()
{
    m_verse_tree = boost::shared_ptr<VerseTreeItem>(new VerseTreeItem("", -1));
}

void TranslationManager::add_translation(boost::shared_ptr<const Translation> translation)
{
    if (!this->contains_translation(translation->get_long_name()))
    {
        m_translations[translation->get_long_name()] = translation;
        m_verse_tree->add_child(translation->get_verse_item_tree(), VerseTreeItem::translation);
    }
}

boost::shared_ptr<const Translation> TranslationManager::at(const std::string& translation_long_name) const
{
    if (this->contains_translation(translation_long_name))
    {
        return m_translations.find(translation_long_name)->second;
    }
    else
    {
        throw TranslationNotFound();
    }
}

boost::shared_ptr<VerseTreeItem> TranslationManager::get_verse_item_tree() const
{
    return m_verse_tree;
}

bool TranslationManager::contains_translation(const std::string& translation_long_name) const
{
    return m_translations.find(translation_long_name) != m_translations.end();
}

// This should really use boost iterator adpater to only return the Translation objects.
std::map<std::string, boost::shared_ptr<const Translation> >::const_iterator TranslationManager::begin() const
{
    return m_translations.begin();
}

std::map<std::string, boost::shared_ptr<const Translation> >::const_iterator TranslationManager::end() const
{
    return m_translations.end();
}

