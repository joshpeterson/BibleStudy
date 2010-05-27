#ifndef __TRANSLATION_LOADER_BEHAVIOR_H
#define __TRANSLATION_LOADER_BEHAVIOR_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include "BehaviorDrivenDesign.h"
#include "TranslationLoader.h"

using namespace BibleStudy;

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
        TranslationLoader* loader = new TranslationLoader(world.GetGiven<ExecutableDirectory>()->get_directory_name());
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
    }
};

}
#endif // __TRANSLATION_LOADER_BEHAVIOR_H
