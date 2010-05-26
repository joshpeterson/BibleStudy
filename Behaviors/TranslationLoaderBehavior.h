#ifndef __TRANSLATION_LOADER_BEHAVIOR_H
#define __TRANSLATION_LOADER_BEHAVIOR_H

#include <cppunit/extensions/HelperMacros.h>
#include "BehaviorDrivenDesign.h"

namespace BibleStudyBehaviors
{

class TranslationLoaderBehavior : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TranslationLoaderBehavior);
    CPPUNIT_TEST(shouldPass);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
    }

    void tearDown()
    {
    }

    void shouldPass()
    {
	    CPPUNIT_ASSERT(1 == 1);
    }
};

}
#endif // __TRANSLATION_LOADER_BEHAVIOR_H
