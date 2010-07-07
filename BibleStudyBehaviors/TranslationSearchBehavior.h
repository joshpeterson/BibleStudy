#ifndef __TRANSLATION_SEARCH_BEHAVIOR_H
#define __TRANSLATION_SEARCH_BEHAVIOR_H

#include <boost/shared_ptr.hpp>
#include "BehaviorDrivenDesign.h"
#include "TranslationBehaviorGivens.h"
#include "BibleDatabase/Translation.h"
#include "BibleDatabase/ISearchResults.h"
#include "BibleDatabase/SearchResultsSerial.h"

using namespace BehaviorDrivenDesign;
using namespace BibleDatabase;

namespace BibleStudyBehaviors
{

class SearchForTwoWords : public IWhen
{
public:
    void occurs(const World& world)
    {
        m_query = boost::shared_ptr<ISearchResults>(new SearchResultsSerial("God lights"));
        boost::shared_ptr<const Translation> translation = world.GetGiven<TestTranslation>()->get_translation();        
        translation->search(m_query);
    }

    boost::shared_ptr<ISearchResults> get_search_results() const
    {
        return m_query;
    }

private:
    boost::shared_ptr<ISearchResults> m_query;
};

class CorrectResultsAreReturned : public IThen
{
public:
    void ensure_that(const World& world)
    {
        boost::shared_ptr<ISearchResults> results = world.GetWhen<SearchForTwoWords>()->get_search_results();
        CPPUNIT_ASSERT_EQUAL(2, results->num_results());
        CPPUNIT_ASSERT_EQUAL(13, results->at(0));
        CPPUNIT_ASSERT_EQUAL(15, results->at(1));
    }
};

class TranslationSearchBehavior : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TranslationSearchBehavior);
    CPPUNIT_TEST(shouldTreatSpacesInSearchStringAsAndOperators);
    CPPUNIT_TEST_SUITE_END();

public:
    void shouldTreatSpacesInSearchStringAsAndOperators()
    {
        World world(get_world_with_test_translation_given());

        world.When<SearchForTwoWords>();
        world.Then<CorrectResultsAreReturned>();
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
