#ifndef __VERSE_DISPLAY_BEHAVIOR_H
#define __VERSE_DISPLAY_BEHAVIOR_H

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

class VerseDisplayObjectsAreEqual : public IThen
{
public:
	void ensure_that(const World& world)
	{
		CPPUNIT_ASSERT(world.GetWhen<ComparedTo>()->get_comparison_result());
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

class VerseDisplayBehavior : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(VerseDisplayBehavior);
    CPPUNIT_TEST(shouldTreatTheSameVerseDisplayObjectsAsEqual);
    CPPUNIT_TEST(shouldTreatVerseDisplayObjectsWithDifferentTranslationsAsNotEqual);
    CPPUNIT_TEST(shouldTreatVerseDisplayObjectsWithDifferentVerseIdsAsNotEqual);
    CPPUNIT_TEST(shouldTreatVerseDisplayObjectsWithDifferentContextsAsEqual);
    CPPUNIT_TEST_SUITE_END();

public:
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
};

}

#endif // __VERSE_DISPLAY_BEHAVIOR_H
