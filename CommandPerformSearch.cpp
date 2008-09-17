#include "CommandPerformSearch.h"
#include "Translation.h"
#include "SearchResultsSerial.h"

CommandPerformSearch::CommandPerformSearch(boost::shared_ptr<Translation> translation, std::string search_string) :
    m_translation(translation),
    m_search_string(search_string),
    m_search_results(NULL)
{
}

void CommandPerformSearch::operator()()
{
    parse_search_string();

    m_translation->search(m_search_queries);

    m_search_results = m_search_queries[0];
}

void CommandPerformSearch::get_results()
{
    return m_search_results;
}

void CommandPerformSearch::parse_search_string()
{
    m_search_queries.push_back(new SearchResultsSerial(m_search_string));
}