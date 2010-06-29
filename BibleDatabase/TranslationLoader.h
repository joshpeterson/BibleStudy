#ifndef __TRANSLATION_LOADER_H
#define __TRANSLATION_LOADER_H

#include <string>
#include "BibleDatabaseExporter.h"

namespace BibleDatabase
{

class TranslationLoader
{
public:
    BIBLE_DATABASE_EXPORT TranslationLoader(std::string executable_directory);

    BIBLE_DATABASE_EXPORT std::string get_executable_directory() const;

private:
    std::string m_executable_directory;
};

}

#endif // __TRANSLATION_LOADER_H