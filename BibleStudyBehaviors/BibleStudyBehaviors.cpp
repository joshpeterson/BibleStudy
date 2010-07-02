#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "BehaviorDrivenDesignTest.h"
#include "TranslationLoaderBehavior.h"
#include "TranslationBehavior.h"

using namespace BibleStudyBehaviors;
using namespace BibleDatabase;

CPPUNIT_TEST_SUITE_REGISTRATION(BehaviorDrivenDesignTest);
CPPUNIT_TEST_SUITE_REGISTRATION(TranslationLoaderBehavior);
CPPUNIT_TEST_SUITE_REGISTRATION(TranslationBehavior);

int main()
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

    runner.addTest(registry.makeTest());
    bool testStatus = runner.run("", false);

    return testStatus ? 0 : 1;
}

