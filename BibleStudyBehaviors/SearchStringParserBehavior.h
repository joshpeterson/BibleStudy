#ifndef __SEARCH_STRING_PARSER_BEHAVIOR_H
#define __SEARCH_STRING_PARSER_BEHAVIOR_H

#include <vector>
#include <string>
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
        m_search_string_parser = boost::shared_ptr<SearchStringParser>(new SearchStringParser());
    }

    boost::shared_ptr<SearchStringParser> get_search_string_parser() const
    {
        return m_search_string_parser;
    }

private:
    boost::shared_ptr<SearchStringParser> m_search_string_parser;
};

class SearchStringHasTwoWords : public IWhen
{
public:
    void occurs(const World& world)
    {
        m_search_terms = world.GetGiven<DefaultSearchStringParser>()->get_search_string_parser()->parse("Foo bar");
    }

    const std::vector<std::string>& get_search_terms() const
    {
        return m_search_terms;
    }

private:
    std::vector<std::string> m_search_terms;
};

class TwoValidSearchTermsAreReturned : public IThen
{
public:
    void ensure_that(const World& world)
    {
        std::vector<std::string> search_terms = world.GetWhen<SearchStringHasTwoWords>()->get_search_terms();
        CPPUNIT_ASSERT_EQUAL(2, static_cast<int>(search_terms.size()));
        CPPUNIT_ASSERT_EQUAL(std::string("Foo"), search_terms[0]);
        CPPUNIT_ASSERT_EQUAL(std::string("bar"), search_terms[1]);
    }
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
