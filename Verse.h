#ifndef __VERSE_H
#define __VERSE_H

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

class ISearchResults;

class Verse : private boost::noncopyable
{
public:
    Verse(const std::string& book, int chapter, int verse, const std::string& text, int unique_verse_id);

    virtual bool match(boost::shared_ptr<ISearchResults> search_string) const;
    virtual int get_unqiue_id() const {return m_unique_id; }
    virtual std::string get_text() const { return m_text; }
    virtual void display(std::ostream& out) const;

    virtual std::string get_book() const { return m_book; }
    virtual int get_chapter() const { return m_chapter; }
    virtual int get_verse() const { return m_verse; }
    virtual int get_unique_id() const { return m_unique_id; } 

private:
    std::string m_book;
    int m_chapter;
    int m_verse;
    std::string m_text;
    int m_unique_id;

    Verse() {};

};

#endif // __VERSE_H

