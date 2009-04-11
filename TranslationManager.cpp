#include "TranslationManager.h"
#include "Translation.h"

void TranslationManager::add_translation(boost::shared_ptr<const Translation> translation)
{
    if (!this->contains_translation(translation->get_long_name()))
    {
        m_translations[translation->get_long_name()] = translation;
    }
}

const Translation& TranslationManager::operator[](const std::string& translation_long_name) const
{
    if (this->contains_translation(translation_long_name))
    {
        return m_translations[translation_long_name];
    }
    else
    {
        // throw exception here
    }
}

bool TranslationManager::contains_translation(const std::string& translation_long_name) const
{
    return m_translations.find(translation_long_name) != m_translations.end();
}