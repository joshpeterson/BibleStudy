#include "CommandPerformSearch.h"
#include "TranslationManager.h"
#include "Translation.h"
#include "SearchResultsSerial.h"
#include "TranslationIterator.h"

using namespace BibleStudy;

CommandPerformSearch::CommandPerformSearch(boost::shared_ptr<const TranslationManager> translation_manager, std::string search_string) :
    m_translation_manager(translation_manager),
    m_search_query(new SearchResultsSerial(search_string))
{
}

void CommandPerformSearch::Execute()
{
    for (TranslationIterator translation = m_translation_manager->begin(); translation != m_translation_manager->end(); ++translation)
    {
        (*translation)->search(m_search_query);
    }
}

boost::shared_ptr<ISearchResults> CommandPerformSearch::get_results()
{
    return m_search_query;
}
