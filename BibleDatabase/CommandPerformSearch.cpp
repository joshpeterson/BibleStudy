#include "CommandPerformSearch.h"
#include "TranslationManager.h"
#include "Translation.h"
#include "SearchResultsSerial.h"
#include "TranslationIterator.h"

using namespace BibleDatabase;

CommandPerformSearch::CommandPerformSearch(boost::shared_ptr<const TranslationManager> translation_manager, const std::vector<std::string>& translations_to_search, std::string search_string, SearchOption search_option) :
    m_translation_manager(translation_manager),
    m_translations_to_search(translations_to_search),
    m_search_query(new SearchResultsSerial(search_string)),
    m_search_option(search_option)
{
}

void CommandPerformSearch::Execute()
{
    for (TranslationIterator translation = m_translation_manager->begin(); translation != m_translation_manager->end(); ++translation)
    {
        if (std::find(m_translations_to_search.begin(), m_translations_to_search.end(), (*translation)->get_short_name()) != m_translations_to_search.end())
        {
            (*translation)->search(m_search_query, m_search_option);
        }
    }
}

boost::shared_ptr<ISearchResults> CommandPerformSearch::get_results()
{
    return m_search_query;
}
