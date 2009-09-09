#ifndef __ISEARCH_RESULTS_H
#define __ISEARCH_RESULTS_H

#include <vector>
#include "VerseDisplay.h"

class ISearchResults
{
public:
    virtual void add_matching_verse(std::string translation_long_name, int unique_verse_id) = 0;
    virtual std::string get_search_string() const = 0;
    virtual int num_results() const = 0;
    virtual int at(int index) const = 0;
    virtual std::string translation_at(int index) const = 0;
    virtual std::vector<VerseDisplay>::iterator begin() = 0;
    virtual std::vector<VerseDisplay>::iterator end() = 0;

};

#endif // __ISEARCH_RESULTS_H
