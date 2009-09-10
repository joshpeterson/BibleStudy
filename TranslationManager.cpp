#include "TranslationManager.h"
#include "Translation.h"

void TranslationManager::add_translation(boost::shared_ptr<const Translation> translation)
{
    if (!this->contains_translation(translation->get_long_name()))
    {
        m_translations[translation->get_long_name()] = translation;
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

