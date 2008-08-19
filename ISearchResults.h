#ifndef __ISEARCH_RESULTS_H
#define __ISEARCH_RESULTS_H

#include <vector>

class ISearchResults
{
public:
    virtual void add_matching_verse(int unique_verse_id) = 0;
    virtual std::string get_search_string() const = 0;
    virtual int num_results() const = 0;
    virtual int at(int index) const = 0;
    virtual std::vector<int>::iterator begin() = 0;
    virtual std::vector<int>::iterator end() = 0;

};

#endif // __ISEARCH_RESULTS_H
