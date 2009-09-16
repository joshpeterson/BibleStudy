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

//! This class represents a specific translation of the Bible.
/*!
    A Translation object is a list of verses with given long and short names that can imported from a text file,
    saved to and resumed from a binary buffer, directly indexed, and searched.
*/
class Translation : private boost::noncopyable
{
public:
    //! Get the full name of the translation.
    std::string get_long_name() const { return m_long_name; }

    //! Get the abbreviated name of the translation.
    std::string get_short_name() const { return m_short_name; }

    //! Iterate the verses in this translation and add the ones which match the query to the results object.
    void search(std::vector<boost::shared_ptr<ISearchResults> >& results) const;

    //! Get a specific verse from the translation based on its verse ID.
    const Verse* get_entry(int unique_id) const { return m_verses[unique_id].get(); }
    
    //! Get a specific verse and a given number of context verses (both before and after the desired verse) from the translation.
    std::vector<boost::shared_ptr<const Verse> > get_entry(int unique_id, int num_entries_context) const;

    //! Get the number of verses in the translation.
    int num_entries() const { return static_cast<int>(m_verses.size()); }

    //! Get the root item of the tree representation of this translation.
    boost::shared_ptr<VerseTreeItem> get_verse_item_tree() const;

    //! Save the translation to a platform independent binary file.
    bool Save(const std::string& filename);

    //! Resume the translation from a platform independent binary file.
    bool Resume(const std::string& filename);
    
    //! Import a translation of a given name from a text file.
    /*!
        The text file for the translation must be in the following format, with each line representing
        one verse:

        Unique ID*Book*Chapter*Verse number*Verse text

        Example:

        0*Genesis*1*1*In the beginning God created heaven, and earth.

        1*Genesis*1*2*And the earth was void and empty, and darkness was upon the face of the deep; and the spirit of God moved over the waters.

        2*Genesis*1*3*And God said: Be light made. And light was made.

        Note that after an import, a translation is not ready to be used.  It must be saved to and resumed from a binary file first.
    */
    bool Import(const std::string& long_name, const std::string& short_name, const std::string& filename);

private:
    std::string m_long_name;
    std::string m_short_name;
    std::vector< boost::shared_ptr<Verse> > m_verses;
    boost::shared_ptr<VerseTreeItem> m_verse_tree;

    //! Add the verses in the range that match the search query to the query object.
    void partial_search(std::vector< boost::shared_ptr<Verse> >::const_iterator begin, 
                        std::vector< boost::shared_ptr<Verse> >::const_iterator end,
                        boost::shared_ptr<ISearchResults> query) const;

};

//! Get the text representation and title of a collection of verses.
std::string verse_collection_to_title_and_string_wrapped(const std::vector<boost::shared_ptr<const Verse> >& verse_collection, boost::shared_ptr<const Translation> translation);

//! Get the text representation of a collection of verses.
std::string verse_collection_to_string(const std::vector<boost::shared_ptr<const Verse> >& verse_collection);

//! Get the title of a collection of verses.
std::string verse_collection_title(const std::vector<boost::shared_ptr<const Verse> >& verse_collection, boost::shared_ptr<const Translation> translation);

#endif //__TRANSLATION_H
