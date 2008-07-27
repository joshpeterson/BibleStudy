#ifndef __IVERSE_H
#define __IVERSE_H

#include <string>
#include <vector>
#include "IEntry.h"
#include "ISearchResults.h"

class IVerse : public IEntry
{
public:
    virtual std::string get_book() const = 0;
    virtual int get_chapter() const = 0;
    virtual int get_verse() const = 0;

};

#endif // __IVERSE_H