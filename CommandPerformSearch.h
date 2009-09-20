#ifndef __COMMAND_PERFORM_SEARCH_H
#define __COMMAND_PERFORM_SEARCH_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "ICommand.h"

class TranslationManager;
class ISearchResults;

//! This class represents a command that searches the translations for a given string.
class CommandPerformSearch : public ICommand
{
public:
    //! Create a new instance of the CommandPerformSearch command.
    CommandPerformSearch(boost::shared_ptr<const TranslationManager> translation_manager, std::string search_string);
    
    //! Get the results of the search.
    boost::shared_ptr<ISearchResults> get_results();

    // ICommand
    
    //! Execute the search.
    void Execute();

private:
    boost::shared_ptr<const TranslationManager> m_translation_manager;
    std::string m_search_string;
    boost::shared_ptr<ISearchResults> m_search_results;
    std::vector<boost::shared_ptr<ISearchResults> > m_search_queries;

    void parse_search_string();
};

#endif // __COMMAND_PERFORM_SEARCH_H
