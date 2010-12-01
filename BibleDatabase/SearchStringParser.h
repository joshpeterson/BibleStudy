#ifndef __SEARCH_STRING_PARSER_H
#define __SEARCH_STRING_PARSER_H

#include <vector>
#include <string>
#include "BibleDatabaseExporter.h"

namespace BibleDatabase
{

class SearchStringParser
{
public:
    BIBLE_DATABASE_EXPORT SearchStringParser() {};

    BIBLE_DATABASE_EXPORT std::vector<std::string> parse(std::string search_string) const;
};

}

#endif // __SEARCH_STRING_PARSER_H