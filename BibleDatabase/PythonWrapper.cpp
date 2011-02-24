#include <iosfwd>
#include <vector>
#include <stdexcept>
#include <boost/python.hpp>
#include <boost/noncopyable.hpp>
#include "Verse.h"
#include "Translation.h"
#include "ISearchResults.h"
#include "SearchResultsSerial.h"
#include "VerseDisplay.h"

using namespace boost::python;
using namespace BibleDatabase;

struct Base
{
    virtual std::string get_search_string() const = 0;
    virtual int g() = 0;
};

struct ISearchResultsWrapper : ISearchResults, wrapper<ISearchResults>
{
    virtual std::string get_search_string() const
    {
        return this->get_override("get_search_string")();
    }

    virtual int num_results() const
    {
        return this->get_override("num_results")();
    }

    virtual int at(int index) const
    {
        return this->get_override("at")(index);
    }

    virtual std::string translation_at(int index) const
    {
        return this->get_override("translation_at")(index);
    }

    virtual void add_matching_verse(std::string, int) {throw std::logic_error("This member function is for the ISearchResults Python wrapper.  Do not call it.");}
    virtual std::vector<VerseDisplay>::iterator begin() {throw std::logic_error("This member function is for the ISearchResults Python wrapper.  Do not call it.");}
    virtual std::vector<VerseDisplay>::iterator end() {throw std::logic_error("This member function is for the ISearchResults Python wrapper.  Do not call it.");}
};

BOOST_PYTHON_MODULE(BibleDatabase)
{
    class_<Verse, boost::noncopyable>("Verse", init<const std::string&, int, int, const std::string&, int>())
        .add_property("book", &Verse::get_book)
        .add_property("chapter", &Verse::get_chapter)
        .add_property("verse", &Verse::get_verse)
        .add_property("text", &Verse::get_text)
        .add_property("id", &Verse::get_unique_id);

    const Verse* (Translation::*get_verse_1)(int) const = &Translation::get_verse;

    class_<Translation, boost::noncopyable>("Translation")
        .def("resume", &Translation::resume)
        .add_property("short_name", &Translation::get_short_name)
        .add_property("long_name", &Translation::get_long_name)
        .def("get_verse", get_verse_1, return_value_policy<reference_existing_object>());

    class_<ISearchResultsWrapper, boost::noncopyable>("ISearchResults")
        .def("get_search_string", pure_virtual(&ISearchResults::get_search_string))
        .def("num_results", pure_virtual(&ISearchResults::num_results))
        .def("at", pure_virtual(&ISearchResults::at))
        .def("translation_at", pure_virtual(&ISearchResults::translation_at));

    class_<SearchResultsSerial, boost::noncopyable, bases<ISearchResults> >("SearchResultsSerial", init<std::string>());
}