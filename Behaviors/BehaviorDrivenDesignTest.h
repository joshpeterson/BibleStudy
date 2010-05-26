#ifndef __BEHAVOIR_DRIVEN_DEISGN_TEST_H
#define __BEHAVOIR_DRIVEN_DEISGN_TEST_H

#include <stdexcept>
#include <cppunit/extensions/HelperMacros.h>
#include "BehaviorDrivenDesign.h"

using namespace BehaviorDrivenDesign;

namespace BibleStudyBehaviors
{

class TestGiven : public IGiven
{
public:
    TestGiven() : m_setup_called(false)
    {
    }

    void setup(const World&)
    {
        m_setup_called = true;
    }

    bool get_setup_called() const
    {
        return m_setup_called;
    }

private:
    bool m_setup_called;
};

class EmptyTestGiven : public IGiven
{
    void setup(const World&)
    {
    }
};

class TestWhen : public IWhen
{
public:
    TestWhen() : m_occurs_called(false)
    {
    }

    void occurs(const World&)
    {
        m_occurs_called = true;
    }

    bool get_occurs_called() const
    {
        return m_occurs_called;
    }

private:
    bool m_occurs_called;
};

class EmptyTestWhen : public IWhen
{
    void occurs(const World&)
    {
    }
};

class TestThen : public IThen
{
public:
    TestThen() : m_ensure_that_called(false)
    {
    }

    void ensure_that(const World&)
    {
        m_ensure_that_called = true;
    }

    bool get_ensure_that_called() const
    {
        return m_ensure_that_called;
    }

private:
    bool m_ensure_that_called;
};

class BehaviorDrivenDesignTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(BehaviorDrivenDesignTest);
    CPPUNIT_TEST(testGivenSetupCalled);
    CPPUNIT_TEST(testWhenOccursCalled);
    CPPUNIT_TEST(testThenEnsureThatCalled);
    CPPUNIT_TEST_EXCEPTION(testGivenThrowsLogicErrorWhenTwoGivensOfTheSameTypeAreDefined, std::logic_error);
    CPPUNIT_TEST_EXCEPTION(testGivenThrowsLogicErrorWhenInvalidGivenRequested, std::logic_error);
    CPPUNIT_TEST_EXCEPTION(testWhenThrowsLogicErrorWhenTwoGivensOfTheSameTypeAreDefined, std::logic_error);
    CPPUNIT_TEST_EXCEPTION(testWhenThrowsLogicErrorWhenInvalidGivenRequested, std::logic_error);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
    }

    void tearDown()
    {
    }

    void testGivenSetupCalled()
    {
        World world;

        world.Given<TestGiven>();

        const TestGiven* testGiven = world.GetGiven<TestGiven>();
	    CPPUNIT_ASSERT(testGiven->get_setup_called() == true);
    }

    void testWhenOccursCalled()
    {
        World world;

        world.When<TestWhen>();

        const TestWhen* testWhen = world.GetWhen<TestWhen>();
	    CPPUNIT_ASSERT(testWhen->get_occurs_called() == true);
    }

    void testThenEnsureThatCalled()
    {
        World world;

        world.Then<TestThen>();

        // If we don't get any exceptions, we'll assume this test passed.
    }

    void testGivenThrowsLogicErrorWhenTwoGivensOfTheSameTypeAreDefined()
    {
        World world;

        world.Given<TestGiven>().Given<TestGiven>();
    }

    void testGivenThrowsLogicErrorWhenInvalidGivenRequested()
    {
        World world;

        world.Given<TestGiven>();
        world.GetGiven<EmptyTestGiven>();
    }

    void testWhenThrowsLogicErrorWhenTwoGivensOfTheSameTypeAreDefined()
    {
        World world;

        world.When<TestWhen>().When<TestWhen>();
    }

    void testWhenThrowsLogicErrorWhenInvalidGivenRequested()
    {
        World world;

        world.When<TestWhen>();
        world.GetWhen<EmptyTestWhen>();
    }
};

}
#endif // __BEHAVOIR_DRIVEN_DEISGN_TEST_H
