#ifndef __COMMAND_PERFORM_SEARCH_H
#define __COMMAND_PERFORM_SEARCH_H

#include <string>
#include <boost/shared_ptr.hpp>
#include "ICommand.h"
#include "BibleDatabaseExporter.h"

namespace BibleDatabase
{

class TranslationLoader;
class Translation;

//! This class represents a command that loads a translation.
class CommandLoadTranslation : public ICommand
{
public:
    //! Create a new instance of the CommandLoadTranslation command.
    BIBLE_DATABASE_EXPORT CommandLoadTranslation(boost::shared_ptr<const TranslationLoader> translation_loader, std::string translation_file);

    //! Get the translation that was loaded.
    BIBLE_DATABASE_EXPORT boost::shared_ptr<const Translation> get_translation() const;
    
    // ICommand
    
    //! Execute the translaton load.
    BIBLE_DATABASE_EXPORT void Execute();

private:
    boost::shared_ptr<const TranslationLoader> m_translation_loader;
    std::string m_translation_file;
    boost::shared_ptr<const Translation> m_translation;
};

}

#endif // __COMMAND_PERFORM_SEARCH_H