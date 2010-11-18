#ifndef __TRANSLATION_LOADER_H
#define __TRANSLATION_LOADER_H

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

namespace BibleDatabase
{

class Translation;

//! This class represents the factory used to create Translation objects.
class TranslationLoader : private boost::noncopyable
{
public:
    //! Create a new instance of the TranslationLoader class with a given executable directory.
    TranslationLoader(std::string executable_directory);

    //! Get the executable directory for this TranslationLoader.
    std::string get_executable_directory() const;

    //! Create a Translation object from the given translation file, which must be relative to the given executable directory.
    boost::shared_ptr<const Translation> create_translation(std::string translation_file) const;

private:
    std::string m_executable_directory;

    TranslationLoader();
};

}

#endif // __TRANSLATION_LOADER_H