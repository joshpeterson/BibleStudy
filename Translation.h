#ifndef __TRANSLATION_H
#define __TRANSLATION_H

#include <string>
#include <vector>
#include <iostream>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "IDocument.h"
#include "IVerse.h"

class Translation : public IDocument, private boost::noncopyable
{
public:
    Translation() {};

    //IDocument
    virtual std::string get_long_name() const { return m_long_name; }
    virtual std::string get_short_name() const { return m_short_name; }
    virtual void search(std::vector<boost::shared_ptr<ISearchResults> >& results) const;
    virtual const IVerse* get_entry(int unique_id) const { return m_verses[unique_id].get(); }
    virtual int num_entries() const { return static_cast<int>(m_verses.size()); }
    virtual bool Save(const std::string& filename);
    virtual bool Resume(const std::string& filename);

    std::vector<boost::shared_ptr<const IVerse> > get_entry(int unique_id, int num_entries_context) const;
    bool Import(const std::string& long_name, const std::string& short_name, const std::string& filename);

private:
    std::string m_long_name;
    std::string m_short_name;
    std::vector< boost::shared_ptr<IVerse> > m_verses;

    void partial_search(std::vector< boost::shared_ptr<IVerse> >::const_iterator begin, 
                        std::vector< boost::shared_ptr<IVerse> >::const_iterator end,
                        boost::shared_ptr<ISearchResults> query) const;

};

std::string verse_collection_to_string(const std::vector<boost::shared_ptr<const IVerse> >& verse_collection);
std::string verse_collection_title(const std::vector<boost::shared_ptr<const IVerse> >& verse_collection);

#endif //__TRANSLATION_H
