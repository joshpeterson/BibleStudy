#include "SearchStringParser.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace BibleDatabase;

std::vector<std::string> SearchStringParser::parse(std::string search_string) const
{
    std::vector<std::string> search_terms;
    boost::algorithm::split(search_terms, search_string, boost::algorithm::is_any_of(" "));
    
    return search_terms;
}
