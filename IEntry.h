#ifndef __IENTRY_H
#define __IENTRY_H

#include <string>
#include <vector>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include "ISearchResults.h"

class IEntry
{
public:
    typedef boost::shared_ptr<ISearchResults> ISearchResultsPtr;
    typedef std::vector<ISearchResultsPtr> ISearchResultsCol;

    virtual void match(ISearchResultsCol& search_strings) const = 0;

    virtual int get_unqiue_id() const = 0;
    virtual std::string get_text() const = 0;
    virtual void display(std::ostream& out) const = 0;

};

#endif // __IENTRY_H

