#include "CommandPerformSearch.h"
#include "TranslationManager.h"
#include "Translation.h"
#include "SearchResultsSerial.h"
#include "TranslationIterator.h"

using namespace BibleStudy;

CommandPerformSearch::CommandPerformSearch(boost::shared_ptr<const TranslationManager> translation_manager, std::string search_string) :
    m_translation_manager(translation_manager),
    m_search_string(search_string)
{
}

void CommandPerformSearch::Execute()
{
    parse_search_string();

    for (std::map<std::string, boost::shared_ptr<const Translation> >::const_iterator it = m_translation_manager->begin(); it != m_translation_manager->end(); ++it)
    {
        (*it->second).search(m_search_queries);
    }

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
