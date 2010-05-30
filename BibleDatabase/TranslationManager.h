#ifndef __TRANSLATION_MANAGER_H
#define __TRANSLATION_MANAGER_H

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "BibleDatabaseExporter.h"

namespace BibleStudy
{

class Translation;
class VerseTreeItem;
class TranslationIterator;

//! This class represents a collection of read-only translations.
class TranslationManager : private boost::noncopyable
{
public:
    //! Create a new instance of the TranslationManager class.
    BIBLE_DATABASE_EXPORT TranslationManager();

    //! Add a translation to the TranslationManager.
    BIBLE_DATABASE_EXPORT void add_translation(boost::shared_ptr<const Translation> translation);

    //! Get the Translation with the given name.
    BIBLE_DATABASE_EXPORT boost::shared_ptr<const Translation> at(const std::string& translation_long_name) const;

    //! Get the VerseTreeItem for the TranslationManager.  This object represents the root of the verse tree used for browsing.
    BIBLE_DATABASE_EXPORT boost::shared_ptr<VerseTreeItem> get_verse_item_tree() const;

    //! Get the starting iterator in the collection of Translation objects.
    BIBLE_DATABASE_EXPORT TranslationIterator begin() const;

    //! Get the end iterator in the collection of Translation objects.
    BIBLE_DATABASE_EXPORT TranslationIterator end() const;

private:
    std::map<std::string, boost::shared_ptr<const Translation> > m_translations;
    boost::shared_ptr<VerseTreeItem> m_verse_tree;

    bool contains_translation(const std::string& translation_long_name) const;
};

//! This class represents an exception that is thrown when a Translation object of the given name is not found in the TranslationManager.
class TranslationNotFound : public std::exception
{
};

}

#endif // __TRANSLATION_MANAGER_H
