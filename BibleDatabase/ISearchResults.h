#ifndef __ISEARCH_RESULTS_H
#define __ISEARCH_RESULTS_H

#include <vector>
#include "VerseDisplay.h"

namespace BibleStudy
{

//! This class represents an interface for accumulating translation search results.
class ISearchResults
{
public:
    //! Add the given verse from the given translation to the list of matching verses.
    virtual void add_matching_verse(std::string translation_long_name, int unique_verse_id) = 0;

    //! Get the string to match against verses.
    virtual std::string get_search_string() const = 0;

    //! Get the number of matching verses for this search string.
    virtual int num_results() const = 0;

    //! Get the verse ID of the matching verse at the given index within these search results.
    virtual int at(int index) const = 0;

    //! Get the translation of the matching verse at the given index within these search results.
    virtual std::string translation_at(int index) const = 0;

    //! Get the starting iterator of the collection of matching verses.
    virtual std::vector<VerseDisplay>::iterator begin() = 0;

    //! Get the end iterator of the collection of matching verses.
    virtual std::vector<VerseDisplay>::iterator end() = 0;

};

}

#endif // __ISEARCH_RESULTS_H
