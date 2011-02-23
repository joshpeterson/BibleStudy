#include <boost/python.hpp>
#include <boost/noncopyable.hpp>
#include "Verse.h"
#include "Translation.h"

using namespace boost::python;
using namespace BibleDatabase;

BOOST_PYTHON_MODULE(BibleDatabase)
{
    class_<Verse, boost::noncopyable>("Verse", init<const std::string&, int, int, const std::string&, int>())
        .def("book", &Verse::get_book)
        .def("chapter", &Verse::get_chapter)
        .def("verse", &Verse::get_verse)
        .def("text", &Verse::get_text)
        .def("id", &Verse::get_unique_id);

    const Verse* (Translation::*get_verse_1)(int) const = &Translation::get_verse;

    class_<Translation, boost::noncopyable>("Translation")
        .def("resume", &Translation::resume)
        .def("short_name", &Translation::get_short_name)
        .def("long_name", &Translation::get_long_name)
        .def("get_verse", get_verse_1, return_value_policy<manage_new_object>());
}