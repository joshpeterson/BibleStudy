#ifndef __VERSE_H
#define __VERSE_H

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "BibleDatabaseExporter.h"

namespace BibleDatabase
{

class ISearchResults;

//! This class represents a single verse in a Translation object.
class Verse : private boost::noncopyable
{
public:
    //! Create a new instance of the Verse class.
    BIBLE_DATABASE_EXPORT Verse(const std::string& book, int chapter, int verse, const std::string& text, int unique_verse_id);

    //! Determine whether or not this verse matches the given query.
    BIBLE_DATABASE_EXPORT virtual bool match(boost::shared_ptr<ISearchResults> search_string) const;

    //! Get the ID for this verse, which is unique to the Translation where the verse lives.
    BIBLE_DATABASE_EXPORT virtual int get_unique_id() const {return m_unique_id; }

    //! Get the text of the verse.
    BIBLE_DATABASE_EXPORT virtual std::string get_text() const { return m_text; }

    //! Stream the verse to an output stream.
    BIBLE_DATABASE_EXPORT virtual void display(std::ostream& out) const;

    //! Get the book of this verse.
    BIBLE_DATABASE_EXPORT virtual std::string get_book() const { return m_book; }

    //! Get the chapter of this verse.
    BIBLE_DATABASE_EXPORT virtual int get_chapter() const { return m_chapter; }

    //! Get the verse number of this verse.
    BIBLE_DATABASE_EXPORT virtual int get_verse() const { return m_verse; }

private:
    std::string m_book;
    int m_chapter;
    int m_verse;
    std::string m_text;
    int m_unique_id;

    //! Prevent default construction of Verse objects.
    Verse() {};

};

}

#endif // __VERSE_H

