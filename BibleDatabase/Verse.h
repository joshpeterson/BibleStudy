#ifndef __VERSE_H
#define __VERSE_H

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace BibleDatabase
{

bool case_insensitive_character_comparison(char character1, char character2);

//! This class represents a single verse in a Translation object.
class Verse : private boost::noncopyable
{
public:
    //! Create a new instance of the Verse class.
    Verse(const std::string& book, int chapter, int verse, const std::string& text, int unique_verse_id);

    //! Determine whether or not this verse matches the given string, including the casing of the string.
    virtual bool case_sensitive_match(std::string search_string) const;

    //! Determine whether or not this verse matches the given string, using whole words only and including the casing of the string.
    virtual bool case_sensitive_whole_word_match(std::string search_string) const;

    //! Determine whether or not this verse matches the given string, not including the casing of the string.
    virtual bool case_insensitive_match(std::string search_string) const;

    //! Determine whether or not this verse matches the given string, using whole words only and not including the casing of the string.
    virtual bool case_insensitive_whole_word_match(std::string search_string) const;

    //! Get the ID for this verse, which is unique to the Translation where the verse lives.
    virtual int get_unique_id() const {return m_unique_id; }

    //! Get the text of the verse.
    virtual std::string get_text() const { return m_text; }

    //! Stream the verse to an output stream.
    virtual void display(std::ostream& out) const;

    //! Get the book of this verse.
    virtual std::string get_book() const { return m_book; }

    //! Get the chapter of this verse.
    virtual int get_chapter() const { return m_chapter; }

    //! Get the verse number of this verse.
    virtual int get_verse() const { return m_verse; }

private:
    std::string m_book;
    int m_chapter;
    int m_verse;
    std::string m_text;
    int m_unique_id;

    bool is_word_delimiter(char character) const;

    //! Prevent default construction of Verse objects.
    Verse() {};

};

}

#endif // __VERSE_H

