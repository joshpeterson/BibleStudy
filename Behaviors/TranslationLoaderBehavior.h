#include <cppunit/extensions/HelperMacros.h>

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

