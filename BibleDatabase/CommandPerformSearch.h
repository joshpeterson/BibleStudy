#ifndef __COMMAND_PERFORM_SEARCH_H
#define __COMMAND_PERFORM_SEARCH_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "ICommand.h"
#include "BibleDatabaseExporter.h"
#include "Translation.h"

namespace BibleDatabase
{

class TranslationManager;
class ISearchResults;

//! This class represents a command that searches the translations for a given string.
class CommandPerformSearch : public ICommand
{
public:
    //! Create a new instance of the CommandPerformSearch command.
    BIBLE_DATABASE_EXPORT CommandPerformSearch(boost::shared_ptr<const TranslationManager> translation_manager, const std::vector<std::string>& translations_to_search, std::string search_string, int search_option);
    
    //! Get the results of the search.
    BIBLE_DATABASE_EXPORT boost::shared_ptr<ISearchResults> get_results();

    // ICommand
    
    //! Execute the search.
    BIBLE_DATABASE_EXPORT void Execute();

private:
    boost::shared_ptr<const TranslationManager> m_translation_manager;
    std::vector<std::string> m_translations_to_search;
    boost::shared_ptr<ISearchResults> m_search_query;
    int m_search_option;
};

}

#endif // __COMMAND_PERFORM_SEARCH_H
