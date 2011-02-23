#include <boost/python.hpp>
#include <boost/noncopyable.hpp>
#include "Verse.h"
#include "Translation.h"
using namespace boost::python;

BOOST_PYTHON_MODULE(BibleDatabase)
{
    class_<BibleDatabase::Verse, boost::noncopyable>("Verse", init<const std::string&, int, int, const std::string&, int>())
        .def("book", &BibleDatabase::Verse::get_book)
        .def("chapter", &BibleDatabase::Verse::get_chapter)
        .def("verse", &BibleDatabase::Verse::get_verse)
        .def("text", &BibleDatabase::Verse::get_text)
        .def("id", &BibleDatabase::Verse::get_unique_id);

    class_<BibleDatabase::Translation, boost::noncopyable>("Translation");
}