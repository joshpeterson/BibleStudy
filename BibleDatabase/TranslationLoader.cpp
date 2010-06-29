#include <boost/filesystem.hpp>
#include "TranslationLoader.h"
#include "Translation.h"

using namespace BibleDatabase;

TranslationLoader::TranslationLoader(std::string executable_directory) : m_executable_directory(executable_directory)
{
}

std::string TranslationLoader::get_executable_directory() const
{
    return m_executable_directory;
}

boost::shared_ptr<const Translation> TranslationLoader::create_translation(std::string translation_file) const
{
    boost::filesystem::path translation_path(m_executable_directory);
    translation_path /= translation_file;

    boost::shared_ptr<Translation> translation(new Translation);
    if (translation->Resume(translation_path.string()))
    {
        return translation;
    }

    return boost::shared_ptr<const Translation>();
}