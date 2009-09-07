#include "SearchResultsSerial.h"

SearchResultsSerial::SearchResultsSerial(std::string search_string) :
    m_search_string(search_string)
{
}

void SearchResultsSerial::add_matching_verse(std::string translation_long_name, int unique_verse_id)
{
    m_matching_verses.push_back(VerseDisplay(translation_long_name, unique_verse_id, 0));
}

