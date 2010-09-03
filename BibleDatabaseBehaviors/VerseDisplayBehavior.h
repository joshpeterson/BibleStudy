#ifndef __VERSE_DISPLAY_BEHAVIOR_H
#define __VERSE_DISPLAY_BEHAVIOR_H

#include <string>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "BehaviorDrivenDesign.h"
#include "BibleDatabase/VerseDisplay.h"

using namespace BehaviorDrivenDesign;
using namespace BibleDatabase;

namespace BibleDatabaseBehaviors
{

class VerseDisplayObject : public IGiven
{
public:
	void setup(const World& world)
	{
		m_verse_display = boost::make_shared<VerseDisplay>("Test Translation", 101, 3);
	}

	boost::shared_ptr<VerseDisplay> get_verse_display() const
	{
		return m_verse_display;
	}

private:
	boost::shared_ptr<VerseDisplay> m_verse_display;
};

class ComparedTo : public IWhen
{
public:
	ComparedTo() : m_other_verse_display("Foo", 0, 0) {}

	ComparedTo(VerseDisplay other_verse_display) : m_other_verse_display(other_verse_display) {}

	void occurs(const World& world)
	{
		m_comparison_result = *(world.GetGiven<VerseDisplayObject>()->get_verse_display()) == m_other_verse_display;
	}

	bool get_comparison_result() const
	{
		return m_comparison_result;
	}

private:
	VerseDisplay m_other_verse_display;
	bool m_comparison_result;
};

class VerseDisplayIsSerialized : public IWhen
{
public:
	void occurs(const World& world)
	{
		world.GetGiven<VerseDisplayObject>()->get_verse_display()->serialize(m_serialized_verse);
	}

	std::string get_serialized_verse_display() const
	{
		return m_serialized_verse.str();
	}

private:
	std::stringstream m_serialized_verse;
};

class VerseDisplayObjectsAreEqual : public IThen
{
public:
	void ensure_that(const World& world)
	{
		CPPUNIT_ASSERT(world.GetWhen<ComparedTo>()->get_comparison_result());
	}
};

class VerseDisplayHasCorrectProperties : public IThen
{
public:
	void ensure_that(const World& world)
	{
		CPPUNIT_ASSERT_EQUAL(std::string("Test Translation"), world.GetGiven<VerseDisplayObject>()->get_verse_display()->get_translation());
		CPPUNIT_ASSERT_EQUAL(101, world.GetGiven<VerseDisplayObject>()->get_verse_display()->get_verse_id());
		CPPUNIT_ASSERT_EQUAL(3, world.GetGiven<VerseDisplayObject>()->get_verse_display()->get_num_verses_context());
	}
};

class VerseDisplayObjectsAreNotEqual : public IThen
{
public:
	void ensure_that(const World& world)
	{
		CPPUNIT_ASSERT(!world.GetWhen<ComparedTo>()->get_comparison_result());
	}
};

class VerseSerializationIsCorrect : public IThen
{
public:
	void ensure_that(const World& world)
	{
		CPPUNIT_ASSERT_EQUAL(std::string("Test Translation:101:3"), world.GetWhen<VerseDisplayIsSerialized>()->get_serialized_verse_display());
	}
};

class VerseDisplayBehavior : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(VerseDisplayBehavior);
    CPPUNIT_TEST(shouldSetPropertiesCorrectly);
    CPPUNIT_TEST(shouldTreatTheSameVerseDisplayObjectsAsEqual);
    CPPUNIT_TEST(shouldTreatVerseDisplayObjectsWithDifferentTranslationsAsNotEqual);
    CPPUNIT_TEST(shouldTreatVerseDisplayObjectsWithDifferentVerseIdsAsNotEqual);
    CPPUNIT_TEST(shouldTreatVerseDisplayObjectsWithDifferentContextsAsEqual);
    CPPUNIT_TEST(shouldSerializeVerseDisplayObject);
    CPPUNIT_TEST_SUITE_END();

public:
	void shouldSetPropertiesCorrectly()
	{
		World world;

        world.Given<VerseDisplayObject>();
		world.Then<VerseDisplayHasCorrectProperties>();
	}

    void shouldTreatTheSameVerseDisplayObjectsAsEqual()
    {
        World world;

        world.Given<VerseDisplayObject>();
		world.When<ComparedTo>(*(world.GetGiven<VerseDisplayObject>()->get_verse_display()));
        world.Then<VerseDisplayObjectsAreEqual>();
    }

	void shouldTreatVerseDisplayObjectsWithDifferentTranslationsAsNotEqual()
    {
        World world;

		VerseDisplay verse_display("Test Translation 2", 101, 3);

        world.Given<VerseDisplayObject>();
		world.When<ComparedTo>(verse_display);
        world.Then<VerseDisplayObjectsAreNotEqual>();
    }

	void shouldTreatVerseDisplayObjectsWithDifferentVerseIdsAsNotEqual()
    {
        World world;

		VerseDisplay verse_display("Test Translation", 100, 3);

        world.Given<VerseDisplayObject>();
		world.When<ComparedTo>(verse_display);
        world.Then<VerseDisplayObjectsAreNotEqual>();
    }

	void shouldTreatVerseDisplayObjectsWithDifferentContextsAsEqual()
    {
        World world;

		VerseDisplay verse_display("Test Translation", 101, 2);

        world.Given<VerseDisplayObject>();
		world.When<ComparedTo>(verse_display);
        world.Then<VerseDisplayObjectsAreEqual>();
    }

	void shouldSerializeVerseDisplayObject()
    {
        World world;

        world.Given<VerseDisplayObject>();
		world.When<VerseDisplayIsSerialized>();
        world.Then<VerseSerializationIsCorrect>();
    }
};

}

#endif // __VERSE_DISPLAY_BEHAVIOR_H
