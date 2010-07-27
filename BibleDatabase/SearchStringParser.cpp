#include "SearchStringParser.h"
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace BibleDatabase;

std::vector<std::string> SearchStringParser::parse(std::string search_string) const
{
    std::vector<std::string> search_terms;

    boost::algorithm::trim(search_string);
    
    bool start_new_term = true;
    bool in_quoted_string = false;
    std::string::const_iterator start_of_term;
    std::string::const_iterator end_of_term;

    std::string::const_iterator end_of_search_string = search_string.end();

    for (std::string::const_iterator character = search_string.begin(); character != end_of_search_string; ++character)
    {
        if (*character == '"')
        {
            if (in_quoted_string)
            {
                end_of_term = character;
                std::string term = std::string(start_of_term, end_of_term);
                search_terms.push_back(term);
                start_new_term = true;
            }

            in_quoted_string = !in_quoted_string;
        }
        else if (*character == ' ')
        {
            if (!in_quoted_string)
            {
                end_of_term = character;
                std::string term = std::string(start_of_term, end_of_term);
                search_terms.push_back(term);
                start_new_term = true;
            }
        }
        else if ((character + 1) == end_of_search_string)
        {
            if (!in_quoted_string)
            {
                end_of_term = character + 1;
                std::string term = std::string(start_of_term, end_of_term);
                search_terms.push_back(term);
                break;
            }
        }
        else if (start_new_term)
        {
            start_of_term = character;
            start_new_term = false;
        }
    }
    
    return search_terms;
}
