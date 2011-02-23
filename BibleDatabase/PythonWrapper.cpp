#include <boost/python.hpp>
#include <boost/noncopyable.hpp>
#include "Verse.h"
#include "Translation.h"

using namespace boost::python;
using namespace BibleDatabase;

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
}