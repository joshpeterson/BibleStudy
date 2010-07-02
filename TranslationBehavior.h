#ifndef __TRANSLATION_BEHAVIOR_H
#define __TRANSLATION_BEHAVIOR_H

#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include "BehaviorDrivenDesign.h"
#include "BibleDatabase/Translation.h"
#include "BibleDatabase/Verse.h"

using namespace BehaviorDrivenDesign;
using namespace BibleDatabase;

namespace BibleStudyBehaviors
{

class TestTranslation : public IGiven
{
public:
    void setup(const World& /*world*/)
    {
        m_translation = boost::shared_ptr<Translation>(new Translation());

        boost::filesystem::path translation_file = boost::filesystem::initial_path();
        translation_file /= "Translations/TT.buf";

        m_translation->Resume(translation_file.file_string());
    }

    boost::shared_ptr<const Translation> get_translation() const
    {
        return m_translation;
    }

private:
    boost::shared_ptr<Translation> m_translation;
};

class VerseIsObtainedWithNoContext : public IWhen
{
public:
    VerseIsObtainedWithNoContext() {}

    VerseIsObtainedWithNoContext(int verse_id) : m_verse_id(verse_id) {}

    void occurs(const World& world)
    {
        boost::shared_ptr<const Translation> translation = world.GetGiven<TestTranslation>()->get_translation();        
        m_verses = translation->get_verse(m_verse_id, 0);
    }

    std::vector<boost::shared_ptr<const Verse> > get_verses() const
    {
        return m_verses;
    }

private:
    int m_verse_id;
    std::vector<boost::shared_ptr<const Verse> > m_verses;
};

class VerseIsObtainedWithContext : public IWhen
{
public:
    VerseIsObtainedWithContext() {}

    VerseIsObtainedWithContext(int verse_id) : m_verse_id(verse_id) {}

    void occurs(const World& world)
    {
        boost::shared_ptr<const Translation> translation = world.GetGiven<TestTranslation>()->get_translation();        
        m_verses = translation->get_verse(m_verse_id, 1);
    }

    std::vector<boost::shared_ptr<const Verse> > get_verses() const
    {
        return m_verses;
    }

private:
    int m_verse_id;
    std::vector<boost::shared_ptr<const Verse> > m_verses;
};

class VerseIsCorrectWithNoContext : public IThen
{
public:
    VerseIsCorrectWithNoContext(int verse_id) : m_verse_id(verse_id) {}

    void ensure_that(const World& world)
    {
        CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(world.GetWhen<VerseIsObtainedWithNoContext>()->get_verses().size()));
        CPPUNIT_ASSERT_EQUAL(m_verse_id, world.GetWhen<VerseIsObtainedWithNoContext>()->get_verses()[0]->get_unique_id());
    }

private:
    int m_verse_id;
};

class VerseIsCorrectWithNoContextWithContext : public IThen
{
public:
    VerseIsCorrectWithNoContextWithContext() {}
    VerseIsCorrectWithNoContextWithContext(int verse_id) : m_verse_id(verse_id) {}

    void ensure_that(const World& world)
    {
        int expected_number_verses = 0;
        int expected_first_verse_id = 0;
        int expected_last_verse_id = 0;

        if (m_verse_id == 0)
        {
            expected_number_verses = 2;
            expected_first_verse_id = 0;
            expected_last_verse_id = 1;
        }
        else if (m_verse_id == 2740)
        {
            expected_number_verses = 2;
            expected_first_verse_id = 2739;
            expected_last_verse_id = 2740;
        }
        else
        {
            expected_number_verses = 3;
            expected_first_verse_id = m_verse_id - 1;
            expected_last_verse_id = m_verse_id + 1;
        }

        CPPUNIT_ASSERT_EQUAL(expected_number_verses, static_cast<int>(world.GetWhen<VerseIsObtainedWithContext>()->get_verses().size()));
        CPPUNIT_ASSERT_EQUAL(expected_first_verse_id, world.GetWhen<VerseIsObtainedWithContext>()->get_verses()[0]->get_unique_id());
        CPPUNIT_ASSERT_EQUAL(expected_last_verse_id, world.GetWhen<VerseIsObtainedWithContext>()->get_verses()[expected_number_verses-1]->get_unique_id());
    }

private:
    int m_verse_id;
};

class TranslationBehavior : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TranslationBehavior);
    CPPUNIT_TEST(shouldGetSingleFirstVerseCorrectly);
    CPPUNIT_TEST(shouldGetSingleMiddleVerseCorrectly);
    CPPUNIT_TEST(shouldGetSingleSecondToLastVerseCorrectly);
    CPPUNIT_TEST(shouldGetSingleLastVerseCorrectly);
    CPPUNIT_TEST(shouldGetFirstVerseWithContextCorrectly);
    CPPUNIT_TEST(shouldGetMiddleVerseWithContextCorrectly);
    CPPUNIT_TEST(shouldGetLastVerseWithContextCorrectly);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
        m_world.Given<TestTranslation>();
    }

    void tearDown()
    {
    }

    void shouldGetSingleFirstVerseCorrectly()
    {
        World world(m_world);

        world.When<VerseIsObtainedWithNoContext, int>(0);
        world.Then<VerseIsCorrectWithNoContext>(0);
    }

    void shouldGetSingleMiddleVerseCorrectly()
    {
        World world(m_world);

        world.When<VerseIsObtainedWithNoContext, int>(1024);
        world.Then<VerseIsCorrectWithNoContext>(1024);
    }

    void shouldGetSingleSecondToLastVerseCorrectly()
    {
        World world(m_world);

        world.When<VerseIsObtainedWithNoContext, int>(2739);
        world.Then<VerseIsCorrectWithNoContext>(2739);
    }

    void shouldGetSingleLastVerseCorrectly()
    {
        World world(m_world);

        world.When<VerseIsObtainedWithNoContext, int>(2740);
        world.Then<VerseIsCorrectWithNoContext>(2740);
    }

    void shouldGetFirstVerseWithContextCorrectly()
    {
        World world(m_world);

        world.When<VerseIsObtainedWithContext, int>(0);
        world.Then<VerseIsCorrectWithNoContextWithContext>(0);
    }

    void shouldGetMiddleVerseWithContextCorrectly()
    {
        World world(m_world);

        world.When<VerseIsObtainedWithContext, int>(816);
        world.Then<VerseIsCorrectWithNoContextWithContext>(816);
    }

    void shouldGetLastVerseWithContextCorrectly()
    {
        World world(m_world);

        world.When<VerseIsObtainedWithContext, int>(2740);
        world.Then<VerseIsCorrectWithNoContextWithContext>(2740);
    }

private:
    World m_world;
};

}

#endif // __TRANSLATION_BEHAVIOR_H
