#include "CommandLoadTranslation.h"
#include "TranslationLoader.h"

using namespace BibleDatabase;

CommandLoadTranslation::CommandLoadTranslation(boost::shared_ptr<const TranslationLoader> translation_loader, std::string translation_file) :
    m_translation_loader(translation_loader),
    m_translation_file(translation_file)
{
}

boost::shared_ptr<const Translation> CommandLoadTranslation::get_translation() const
{
    return m_translation;
}

void CommandLoadTranslation::Execute()
{
    m_translation = m_translation_loader->create_translation(m_translation_file);
}