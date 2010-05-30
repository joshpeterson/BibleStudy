#ifndef __SEARCH_RESULTS_SERIAL_H
#define __SEARCH_RESULTS_SERIAL_H

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include "ISearchResults.h"
#include "VerseDisplay.h"
#include "BibleDatabaseExporter.h"

namespace BibleStudy
{

//! This class implements the ISearchResults interface using a serial linear search.
/*!
    See the document for ISearchResults for details about the individual members of this class.
*/
class SearchResultsSerial : public ISearchResults, private boost::noncopyable
{
public:
    //! Create a new instance of the SearchResultsSerial class.
    BIBLE_DATABASE_EXPORT SearchResultsSerial(std::string search_string);

    // ISearchResults
    BIBLE_DATABASE_EXPORT virtual void add_matching_verse(std::string translation_long_name, int unique_verse_id);
    BIBLE_DATABASE_EXPORT virtual std::string get_search_string() const { return m_search_string; }
    BIBLE_DATABASE_EXPORT virtual int num_results() const { return static_cast<int>(m_matching_verses.size()); }
    BIBLE_DATABASE_EXPORT virtual int at(int index) const { return m_matching_verses.at(index).get_verse_id(); }
    BIBLE_DATABASE_EXPORT virtual std::string translation_at(int index) const { return m_matching_verses.at(index).get_translation(); }
    BIBLE_DATABASE_EXPORT virtual std::vector<VerseDisplay>::iterator begin() { return m_matching_verses.begin(); }
    BIBLE_DATABASE_EXPORT virtual std::vector<VerseDisplay>::iterator end() { return m_matching_verses.end(); }

private:
    std::string m_search_string;
    std::vector<VerseDisplay> m_matching_verses;

    SearchResultsSerial() {};

};

}

#endif // __SEARCH_RESULTS_SERIAL_H
