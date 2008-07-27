#include <fstream>
#include <iostream>
#include "IEntry.h"
#include "IVerse.h"
#include "Translation.h"
#include "SearchResultsSerial.h"

int main(int argc, char* argv[])
{
    //std::ifstream raw_text;

    //raw_text.open("c:\\Documents and Settings\\Josh\\Desktop\\DR.txt");

	Translation test;

    //test.Import("Douay-Rheims", "DR", "c:\\Documents and Settings\\Josh\\Desktop\\DR.txt");

    //test.Save("c:\\Documents and Settings\\Josh\\Desktop\\DR.buf");

    test.Resume("c:\\Documents and Settings\\Josh\\Desktop\\DR.buf");

    IEntry::ISearchResultsPtr query(new SearchResultsSerial("bread of life"));
    IEntry::ISearchResultsCol results;
    results.push_back(query);

    test.search(results);

    for (IEntry::ISearchResultsCol::const_iterator it = results.begin();
         it != results.end();
         ++it)
    {
        std::cout << "Results for query: " << (*it)->get_search_string() << std::endl;
        for (std::vector<int>::iterator jit = (*it)->begin();
             jit != (*it)->end();
             ++jit)
        {
            test.get_entry(*jit)->display(std::cout);
        }
    }
}

