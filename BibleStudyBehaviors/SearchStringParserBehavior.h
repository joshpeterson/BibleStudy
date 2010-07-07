#ifndef __SEARCH_STRING_PARSER_BEHAVIOR_H
#define __SEARCH_STRING_PARSER_BEHAVIOR_H

#include <boost/shared_ptr.hpp>
#include "BehaviorDrivenDesign.h"
#include "BibleDatabase/SearchStringParser.h"

using namespace BehaviorDrivenDesign;
using namespace BibleDatabase;

namespace BibleStudyBehaviors
{

class DefaultSearchStringParser : public IGiven
{
public:
    void setup(const World&)
    {
        m_search_string_parser = boost::shared_ptr<SearchStringParserBehavior>(new SearchStringParser());
    }

    boost::shared_ptr<SearchStringParser> get_search_string_parser() const
    {
        return m_search_string_parser;
    }

private:
    boost::shared_ptr<SearchStringParser> m_search_string_parser;
};

class SearchStringParserBehavior : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SearchStringParserBehavior);
    CPPUNIT_TEST(shouldTreatSpacesInSearchStringAsAndOperators);
    CPPUNIT_TEST_SUITE_END();

public:
    void shouldTreatSpacesInSearchStringAsAndOperators()
    {
        World world;

        world.Given<DefaultSearchStringParser>();
        world.When<SearchStringHasTwoWords>();
        world.Then<TwoValidSearchTermsAreReturned>();
    }
};

}

#endif  // __SEARCH_STRING_PARSER_BEHAVIOR_H
