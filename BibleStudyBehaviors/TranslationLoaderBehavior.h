#ifndef __TRANSLATION_LOADER_BEHAVIOR_H
#define __TRANSLATION_LOADER_BEHAVIOR_H

#include <string>
#include <boost/shared_ptr.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include "BehaviorDrivenDesign.h"
#include "BibleDatabase/TranslationLoader.h"

using namespace BehaviorDrivenDesign;
using namespace BibleDatabase;

namespace BibleStudyBehaviors
{

class ExecutableDirectory : public IGiven
{
public:
    void setup(const World& /*world*/)
    {
        m_directory_name = "Foo";
    }

    std::string get_directory_name() const
    {
        return m_directory_name;
    }

private:
    std::string m_directory_name;
};

class TranslationLoaderIsCreated : public IWhen
{
public:
    void occurs(const World& world)
    {
        m_loader = boost::shared_ptr<TranslationLoader>(new TranslationLoader(world.GetGiven<ExecutableDirectory>()->get_directory_name()));
    }

    boost::shared_ptr<const TranslationLoader> get_loader() const
    {
        return m_loader;
    }

private:
    boost::shared_ptr<TranslationLoader> m_loader;
};

class ExecutableDirectoryIsSet : public IThen
{
public:
    void ensure_that(const World& world)
    {
        CPPUNIT_ASSERT_EQUAL(world.GetGiven<ExecutableDirectory>()->get_directory_name(), world.GetWhen<TranslationLoaderIsCreated>()->get_loader()->get_executable_directory());
    }
};

class TranslationLoaderBehavior : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TranslationLoaderBehavior);
    CPPUNIT_TEST(shouldStoreExecutableDirectoryOnCreation);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
    }

    void tearDown()
    {
    }

    void shouldStoreExecutableDirectoryOnCreation()
    {
        World world;

        world.Given<ExecutableDirectory>();
        world.When<TranslationLoaderIsCreated>();
        world.Then<ExecutableDirectoryIsSet>();
    }
};

}
#endif // __TRANSLATION_LOADER_BEHAVIOR_H
