#ifndef __TRANSLATION_SEARCH_BEHAVIOR_H
#define __TRANSLATION_SEARCH_BEHAVIOR_H

#include <boost/shared_ptr.hpp>
#include "BehaviorDrivenDesign.h"
#include "TranslationBehaviorGivens.h"
#include "../BibleDatabase/Translation.h"
#include "../BibleDatabase/ISearchResults.h"
#include "../BibleDatabase/SearchResultsSerial.h"

using namespace BehaviorDrivenDesign;
using namespace BibleDatabase;

namespace BibleDatabaseBehaviors
{

class SearchIs : public IWhen
{
public:
    SearchIs() {}

    SearchIs(std::string search_string, int search_option) : m_search_string(search_string), m_search_option(search_option) {}

    void occurs(const World& world)
    {
        m_query = boost::shared_ptr<ISearchResults>(new SearchResultsSerial(m_search_string));
        boost::shared_ptr<const Translation> translation = world.GetGiven<TestTranslation>()->get_translation();        
        translation->search(m_query, m_search_option);
    }

    boost::shared_ptr<ISearchResults> get_search_results() const
    {
        return m_query;
    }

private:
    boost::shared_ptr<ISearchResults> m_query;
    std::string m_search_string;
    int m_search_option;
};


class CorrectResultsAreReturned : public IThen
{
public:
    CorrectResultsAreReturned() {}

    CorrectResultsAreReturned(std::vector<int> expected_results) : m_expected_results(expected_results) {}

    void ensure_that(const World& world)
    {
        boost::shared_ptr<ISearchResults> actual_results = world.GetWhen<SearchIs>()->get_search_results();

        int number_of_expected_results = static_cast<int>(m_expected_results.size());

        CPPUNIT_ASSERT_EQUAL(number_of_expected_results, actual_results->num_results());

        for (int idx = 0; idx < number_of_expected_results; ++idx)
        {
            CPPUNIT_ASSERT_EQUAL(m_expected_results[idx], actual_results->at(idx));
        }
    }

private:
    std::vector<int> m_expected_results;
};

class CorrectNumberOfResultsAreReturned : public IThen
{
public:
    CorrectNumberOfResultsAreReturned() {}

    CorrectNumberOfResultsAreReturned(int expected_number_of_results) : m_expected_number_of_results(expected_number_of_results) {}

    void ensure_that(const World& world)
    {
        boost::shared_ptr<ISearchResults> actual_results = world.GetWhen<SearchIs>()->get_search_results();

        CPPUNIT_ASSERT_EQUAL(m_expected_number_of_results, actual_results->num_results());
    }

private:
    int m_expected_number_of_results;
};

class TranslationSearchBehavior : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TranslationSearchBehavior);
    CPPUNIT_TEST(shouldTreatSpacesInSearchStringAsAndOperators);
    CPPUNIT_TEST(shouldUseCaseSensitiveSearchWhenRequested);
    CPPUNIT_TEST(shouldUseCaseInsensitiveSearchWhenRequested);
    CPPUNIT_TEST(shouldUseCaseSensitiveSearchAndMatchWholeWordsWhenRequested);
    CPPUNIT_TEST(shouldUseCaseInsensitiveSearchAndMatchWholeWordsWhenRequested);
    CPPUNIT_TEST_SUITE_END();

public:
    void shouldTreatSpacesInSearchStringAsAndOperators()
    {
        World world(get_world_with_test_translation_given());

        std::vector<int> expected_results;
        expected_results.push_back(13);
        expected_results.push_back(15);

        world.When<SearchIs>("God lights", CaseSensitive);
        world.Then<CorrectResultsAreReturned>(expected_results);
    }

    void shouldUseCaseSensitiveSearchWhenRequested()
    {
        World world(get_world_with_test_translation_given());

        world.When<SearchIs>("God", CaseSensitive);
        world.Then<CorrectNumberOfResultsAreReturned>(285);
    }

    void shouldUseCaseInsensitiveSearchWhenRequested()
    {
        World world(get_world_with_test_translation_given());

        world.When<SearchIs>("god", CaseInsensitive);
        world.Then<CorrectNumberOfResultsAreReturned>(310);
    }

    void shouldUseCaseSensitiveSearchAndMatchWholeWordsWhenRequested()
    {
        World world(get_world_with_test_translation_given());

        world.When<SearchIs>("god", CaseSensitive|MatchWholeWord);
        world.Then<CorrectNumberOfResultsAreReturned>(2);
    }

    void shouldUseCaseInsensitiveSearchAndMatchWholeWordsWhenRequested()
    {
        World world(get_world_with_test_translation_given());

        world.When<SearchIs>("god", CaseInsensitive|MatchWholeWord);
        world.Then<CorrectNumberOfResultsAreReturned>(286);
    }

private:
    const World& get_world_with_test_translation_given()
    {
        static WorldWithTestTranslationGiven world_with_test_translation;
        return world_with_test_translation.get_world();
    }
};

}

#endif // __TRANSLATION_SEARCH_BEHAVIOR_H
