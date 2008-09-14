#ifndef __IDocument_H
#define __IDocument_H

#include <string>
#include "IEntry.h"

class IDocument
{
public:
    virtual std::string get_long_name() const = 0;
    virtual std::string get_short_name() const = 0;
    virtual void search(IEntry::ISearchResultsCol& results) const = 0;
    virtual const IEntry* get_entry(int unique_id) const = 0;
    virtual int num_entries() const = 0;
    virtual bool Save(const std::string& filename) = 0;
    virtual bool Resume(const std::string& filename) = 0;

};

#endif // __IDocument_H

