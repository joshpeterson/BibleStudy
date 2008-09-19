#include "CommandPerformSearch.h"
#include "Translation.h"
#include "SearchResultsSerial.h"

CommandPerformSearch::CommandPerformSearch(boost::shared_ptr<Translation> translation, std::string search_string) :
    m_translation(translation),
    m_search_string(search_string)
{
}

void CommandPerformSearch::Execute()
{
    parse_search_string();

    m_translation->search(m_search_queries);

    std::vector<boost::shared_ptr<ISearchResults> >::const_iterator end = m_search_queries.end();
    if (m_search_queries.begin() != end)
        m_search_results = *(--end);
}

boost::shared_ptr<ISearchResults> CommandPerformSearch::get_results()
{
    return m_search_results;
}

void CommandPerformSearch::parse_search_string()
{
    boost::shared_ptr<ISearchResults> query(new SearchResultsSerial(m_search_string));
    m_search_queries.push_back(query);
}