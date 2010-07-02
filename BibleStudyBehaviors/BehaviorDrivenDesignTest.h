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

class TestGivenWithOneArgumentConstructor : public IGiven
{
public:
    TestGivenWithOneArgumentConstructor() {}

    TestGivenWithOneArgumentConstructor(int argument) : m_argument(argument)
    {
    }

    void setup(const World&)
    {
    }

    int get_argument() const
    {
        return m_argument;
    }

private:
    int m_argument;
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

class TestWhenWithOneArgumentConstructor : public IWhen
{
public:
    TestWhenWithOneArgumentConstructor() {}

    TestWhenWithOneArgumentConstructor(int argument) : m_argument(argument)
    {
    }

    void occurs(const World&)
    {
    }

    int get_argument() const
    {
        return m_argument;
    }

private:
    int m_argument;
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

class TestThenWithOneArgumentConstructor : public IThen
{
public:
    TestThenWithOneArgumentConstructor() {}

    TestThenWithOneArgumentConstructor(int argument) : m_argument(argument)
    {
    }

    void ensure_that(const World&)
    {
    }

    int get_argument() const
    {
        return m_argument;
    }

private:
    int m_argument;
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
    CPPUNIT_TEST(testWorldCopyConstructor);
    CPPUNIT_TEST(testGivenWithOneArgumentConstructor);
    CPPUNIT_TEST(testWhenWithOneArgumentConstructor);
    CPPUNIT_TEST(testThenWithOneArgumentConstructor);
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
	    CPPUNIT_ASSERT_EQUAL(true, testGiven->get_setup_called());
    }

    void testWhenOccursCalled()
    {
        World world;

        world.When<TestWhen>();

        const TestWhen* testWhen = world.GetWhen<TestWhen>();
	    CPPUNIT_ASSERT_EQUAL(true, testWhen->get_occurs_called());
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

    void testWorldCopyConstructor()
    {
        World world;

        world.Given<TestGiven>();
        world.When<TestWhen>();

        World worldCopy(world);
        CPPUNIT_ASSERT(worldCopy.GetGiven<TestGiven>() != NULL);
        CPPUNIT_ASSERT(worldCopy.GetWhen<TestWhen>() != NULL);
    }

    void testGivenWithOneArgumentConstructor()
    {
        World world;

        world.Given<TestGivenWithOneArgumentConstructor, int>(42);
        CPPUNIT_ASSERT_EQUAL(42, world.GetGiven<TestGivenWithOneArgumentConstructor>()->get_argument());
    }

    void testWhenWithOneArgumentConstructor()
    {
        World world;

        world.When<TestWhenWithOneArgumentConstructor, int>(42);
        CPPUNIT_ASSERT_EQUAL(42, world.GetWhen<TestWhenWithOneArgumentConstructor>()->get_argument());
    }

    void testThenWithOneArgumentConstructor()
    {
        World world;

        world.Then<TestThenWithOneArgumentConstructor, int>(42);
    }
};

}
#endif // __BEHAVOIR_DRIVEN_DEISGN_TEST_H
