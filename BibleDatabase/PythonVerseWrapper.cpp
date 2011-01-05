#include <boost/python.hpp>
#include <boost/noncopyable.hpp>
#include "Verse.h"
using namespace boost::python;

BOOST_PYTHON_MODULE(BibleDatabase)
{
    class_<BibleDatabase::Verse, boost::noncopyable>("Verse", init<const std::string&, int, int, const std::string&, int>())
        .def("case_sensitive_match", &BibleDatabase::Verse::case_sensitive_match);
}