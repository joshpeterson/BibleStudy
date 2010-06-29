#include "TranslationLoader.h"

using namespace BibleDatabase;

TranslationLoader::TranslationLoader(std::string executable_directory) : m_executable_directory(executable_directory)
{
}

std::string TranslationLoader::get_executable_directory() const
{
    return m_executable_directory;
}