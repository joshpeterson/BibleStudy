#ifndef __SEARCH_RESULTS_SERIAL_H
#define __SEARCH_RESULTS_SERIAL_H

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include "ISearchResults.h"
#include "VerseDisplay.h"

class SearchResultsSerial : public ISearchResults, private boost::noncopyable
{
public:
    SearchResultsSerial(std::string search_string);

    // ISearchResults
    virtual void add_matching_verse(std::string translation_long_name, int unique_verse_id);
    virtual std::string get_search_string() const { return m_search_string; }
    virtual int num_results() const { return static_cast<int>(m_matching_verses.size()); }
    virtual int at(int index) const { return m_matching_verses.at(index).get_verse_id(); }
    virtual std::string translation_at(int index) const { return m_matching_verses.at(index).get_translation(); }
    virtual std::vector<int>::iterator begin() { return m_matching_verses.begin(); }
    virtual std::vector<int>::iterator end() { return m_matching_verses.end(); }

private:
    std::string m_search_string;
    std::vector<VerseDisplay> m_matching_verses;

    SearchResultsSerial() {};

};
#endif // __SEARCH_RESULTS_SERIAL_H
