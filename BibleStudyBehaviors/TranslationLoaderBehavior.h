#ifndef __TRANSLATION_LOADER_BEHAVIOR_H
#define __TRANSLATION_LOADER_BEHAVIOR_H

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
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
        m_directory_name = boost::filesystem::initial_path().directory_string();
    }

    std::string get_directory_name() const
    {
        return m_directory_name;
    }

private:
    std::string m_directory_name;
};

class NonExistentExecutableDirectory : public ExecutableDirectory
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

class TranslationLoaderIsCreatedWithNonExistentExecutableDirectory : public IWhen
{
public:
    void occurs(const World& world)
    {
        m_loader = boost::shared_ptr<TranslationLoader>(new TranslationLoader(world.GetGiven<NonExistentExecutableDirectory>()->get_directory_name()));
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

class TranslationCanBeCreatedFromDisk : public IThen
{
public:
    void ensure_that(const World& world)
    {
        std::string translation_file("Translations/TT.buf");
        boost::shared_ptr<const Translation> translation = world.GetWhen<TranslationLoaderIsCreated>()->get_loader()->create_translation(translation_file);
        CPPUNIT_ASSERT(translation != NULL);
    }
};

class TranslationCannotBeCreated : public IThen
{
public:
    void ensure_that(const World& world)
    {
        std::string translation_file("Translations/TT.buf");
        boost::shared_ptr<const Translation> translation = world.GetWhen<TranslationLoaderIsCreatedWithNonExistentExecutableDirectory>()->get_loader()->create_translation(translation_file);
        CPPUNIT_ASSERT(translation == NULL);
    }
};

class TranslationCannotBeCreatedWithNonExistentTranslationFile : public IThen
{
public:
    void ensure_that(const World& world)
    {
        std::string translation_file("Translations/foo.buf");
        boost::shared_ptr<const Translation> translation = world.GetWhen<TranslationLoaderIsCreated>()->get_loader()->create_translation(translation_file);
        CPPUNIT_ASSERT(translation == NULL);
    }
};

class TranslationLoaderBehavior : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TranslationLoaderBehavior);
    CPPUNIT_TEST(shouldStoreExecutableDirectoryOnCreation);
    CPPUNIT_TEST(shouldCreateTranslationFromDiskWhenRequested);
    CPPUNIT_TEST(shouldNotCreateTranslationIfExecutableDirectoryDoesNotExist);
    CPPUNIT_TEST(shouldNotCreateTranslationIfTranslationFileDoesNotExist);
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

    void shouldCreateTranslationFromDiskWhenRequested()
    {
        World world;

        world.Given<ExecutableDirectory>();
        world.When<TranslationLoaderIsCreated>();
        world.Then<TranslationCanBeCreatedFromDisk>();
    }

    void shouldNotCreateTranslationIfExecutableDirectoryDoesNotExist()
    {
        World world;

        world.Given<NonExistentExecutableDirectory>();
        world.When<TranslationLoaderIsCreatedWithNonExistentExecutableDirectory>();
        world.Then<TranslationCannotBeCreated>();
    }

    void shouldNotCreateTranslationIfTranslationFileDoesNotExist()
    {
        World world;

        world.Given<ExecutableDirectory>();
        world.When<TranslationLoaderIsCreated>();
        world.Then<TranslationCannotBeCreatedWithNonExistentTranslationFile>();
    }
};

}
#endif // __TRANSLATION_LOADER_BEHAVIOR_H
