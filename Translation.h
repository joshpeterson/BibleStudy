#ifndef __TRANSLATION_H
#define __TRANSLATION_H

#include <string>
#include <vector>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "ISearchResults.h"

class Verse;
class VerseTreeItem;

class Translation : private boost::noncopyable
{
public:
    Translation() {};

    std::string get_long_name() const { return m_long_name; }
    std::string get_short_name() const { return m_short_name; }
    void search(std::vector<boost::shared_ptr<ISearchResults> >& results) const;
    const Verse* get_entry(int unique_id) const { return m_verses[unique_id].get(); }
    int num_entries() const { return static_cast<int>(m_verses.size()); }
    bool Save(const std::string& filename);
    bool Resume(const std::string& filename);

    std::vector<boost::shared_ptr<const Verse> > get_entry(int unique_id, int num_entries_context) const;
    bool Import(const std::string& long_name, const std::string& short_name, const std::string& filename);
    boost::shared_ptr<VerseTreeItem> get_verse_item_tree() const;

private:
    std::string m_long_name;
    std::string m_short_name;
    std::vector< boost::shared_ptr<Verse> > m_verses;
    boost::shared_ptr<VerseTreeItem> m_verse_tree;

    void partial_search(std::vector< boost::shared_ptr<Verse> >::const_iterator begin, 
                        std::vector< boost::shared_ptr<Verse> >::const_iterator end,
                        boost::shared_ptr<ISearchResults> query) const;

};

std::string verse_collection_to_title_and_string_wrapped(const std::vector<boost::shared_ptr<const Verse> >& verse_collection, boost::shared_ptr<const Translation> translation);
std::string verse_collection_to_string(const std::vector<boost::shared_ptr<const Verse> >& verse_collection);
std::string verse_collection_title(const std::vector<boost::shared_ptr<const Verse> >& verse_collection, boost::shared_ptr<const Translation> translation);

#endif //__TRANSLATION_H
