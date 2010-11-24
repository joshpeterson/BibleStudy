#ifndef __SEARCH_STRING_PARSER_H
#define __SEARCH_STRING_PARSER_H

#include <vector>
#include <string>

namespace BibleDatabase
{

class SearchStringParser
{
public:
    SearchStringParser() {};

    std::vector<std::string> parse(std::string search_string) const;
};

}

#endif // __SEARCH_STRING_PARSER_H