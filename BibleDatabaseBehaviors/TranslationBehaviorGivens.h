#ifndef __TRANSLATION_BEHAVIOR_GIVENS
#define __TRANSLATION_BEHAVIOR_GIVENS

#include <boost/filesystem.hpp>
#include "BibleDatabase/Translation.h"

using namespace BehaviorDrivenDesign;
using namespace BibleDatabase;

namespace BibleDatabaseBehaviors
{

class TestTranslation : public IGiven
{
public:
    void setup(const World& /*world*/)
    {
        m_translation = boost::shared_ptr<Translation>(new Translation());

        boost::filesystem::path translation_file = boost::filesystem::initial_path();
        translation_file /= "Translations/TT.buf";

        m_translation->resume(translation_file.file_string());
    }

    boost::shared_ptr<const Translation> get_translation() const
    {
        return m_translation;
    }

private:
    boost::shared_ptr<Translation> m_translation;
};

class WorldWithTestTranslationGiven
{
public:
    WorldWithTestTranslationGiven()
    {
        m_world.Given<TestTranslation>();
    }

    const World& get_world() const
    {
        return m_world;
    }

private:
    World m_world;
};

}

#endif // __TRANSLATION_BEHAVIOR_GIVENS
