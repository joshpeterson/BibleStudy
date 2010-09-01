#ifndef __SEARCH_STRING_PARSER_BEHAVIOR_H
#define __SEARCH_STRING_PARSER_BEHAVIOR_H

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include "BehaviorDrivenDesign.h"
#include "BibleDatabase/SearchStringParser.h"

using namespace BehaviorDrivenDesign;
using namespace BibleDatabase;

namespace BibleDatabaseBehaviors
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

class SearchStringIs : public IWhen
{
public:
    SearchStringIs() {}

    SearchStringIs(std::string search_string) : m_search_string(search_string) {}

    void occurs(const World& world)
    {
        m_search_terms = world.GetGiven<DefaultSearchStringParser>()->get_search_string_parser()->parse(m_search_string);
    }

    const std::vector<std::string>& get_search_terms() const
    {
        return m_search_terms;
    }

private:
    std::string m_search_string;
    std::vector<std::string> m_search_terms;
};

class ValidSearchTermsAreReturned : public IThen
{
public:
    ValidSearchTermsAreReturned() {}

    ValidSearchTermsAreReturned(std::vector<std::string> expected_search_terms) : m_expected_search_terms(expected_search_terms) {}

    void ensure_that(const World& world)
    {
        std::vector<std::string> actual_search_terms = world.GetWhen<SearchStringIs>()->get_search_terms();

        CPPUNIT_ASSERT_EQUAL(m_expected_search_terms.size(), actual_search_terms.size());

        std::vector<std::string>::const_iterator expected_term = m_expected_search_terms.begin();
        std::vector<std::string>::const_iterator actual_term = actual_search_terms.begin();

        for (; expected_term != m_expected_search_terms.end(); ++expected_term, ++actual_term)
        {
            CPPUNIT_ASSERT_EQUAL(*expected_term, *actual_term);
        }
    }

private:
    std::vector<std::string> m_expected_search_terms;
};

class SearchStringParserBehavior : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SearchStringParserBehavior);
    CPPUNIT_TEST(shouldTreatSpacesInSearchStringAsAndOperators);
    CPPUNIT_TEST(shouldTreatQuotedStringsInSearchStringAsOneTerm);
    CPPUNIT_TEST(shouldParseStringWithQuotedAndUnquotedStrings);
    CPPUNIT_TEST(shouldParseStringWithConsecutiveQuotedStrings);
    CPPUNIT_TEST(shouldRemoveLeadingAndTrailingWhitespace);
    CPPUNIT_TEST_SUITE_END();

public:
    void shouldTreatSpacesInSearchStringAsAndOperators()
    {
        World world;

        std::vector<std::string> expected_search_terms;
        expected_search_terms.push_back("Foo");
        expected_search_terms.push_back("bar");
        expected_search_terms.push_back("yes");
        expected_search_terms.push_back("no");

        world.Given<DefaultSearchStringParser>();
        world.When<SearchStringIs>("Foo bar yes no");
        world.Then<ValidSearchTermsAreReturned>(expected_search_terms);
    }

    void shouldTreatQuotedStringsInSearchStringAsOneTerm()
    {
        World world;

        std::vector<std::string> expected_search_terms;
        expected_search_terms.push_back("Foo bar");

        world.Given<DefaultSearchStringParser>();
        world.When<SearchStringIs>("\"Foo bar\"");
        world.Then<ValidSearchTermsAreReturned>(expected_search_terms);
    }

    void shouldParseStringWithQuotedAndUnquotedStrings()
    {
        World world;

        std::vector<std::string> expected_search_terms;
        expected_search_terms.push_back("test");
        expected_search_terms.push_back("Foo bar");
        expected_search_terms.push_back("yes");

        world.Given<DefaultSearchStringParser>();
        world.When<SearchStringIs>("test \"Foo bar\" yes");
        world.Then<ValidSearchTermsAreReturned>(expected_search_terms);
    }

    void shouldParseStringWithConsecutiveQuotedStrings()
    {
        World world;

        std::vector<std::string> expected_search_terms;
        expected_search_terms.push_back("Foo bar");
        expected_search_terms.push_back("yes no");

        world.Given<DefaultSearchStringParser>();
        world.When<SearchStringIs>("\"Foo bar\"\"yes no\"");
        world.Then<ValidSearchTermsAreReturned>(expected_search_terms);
    }

    void shouldRemoveLeadingAndTrailingWhitespace()
    {
        World world;

        std::vector<std::string> expected_search_terms;
        expected_search_terms.push_back("Foo bar");

        world.Given<DefaultSearchStringParser>();
        world.When<SearchStringIs>("   \"Foo bar\"     ");
        world.Then<ValidSearchTermsAreReturned>(expected_search_terms);
    }
};

}

#endif  // __SEARCH_STRING_PARSER_BEHAVIOR_H
