TEMPLATE = app
CONFIG += console qt thread exceptions stl debug_and_release

HEADERS += BibleStudyBehaviors/BehaviorDrivenDesign.h
HEADERS += BibleStudyBehaviors/BehaviorDrivenDesignTest.h
HEADERS += BibleStudyBehaviors/TranslationLoaderBehavior.h
HEADERS += BibleStudyBehaviors/TranslationBehaviorGivens.h
HEADERS += BibleStudyBehaviors/TranslationFirstAndLastVerseBehavior.h
HEADERS += BibleStudyBehaviors/TranslationSearchBehavior.h
HEADERS += BibleStudyBehaviors/SearchStringParserBehavior.h

SOURCES += BibleStudyBehaviors/BibleStudyBehaviors.cpp

win32 {
    QMAKE_CXXFLAGS_DEBUG += /wd4100
    
    QMAKE_CXXFLAGS_RELEASE += /wd4100
    
    INCLUDEPATH += "$$(CPPUNIT_DIR)\include"
    INCLUDEPATH += "$$(BOOST_DIR)"
    INCLUDEPATH += "$$(GOOGLE_PROTOBUF_DIR)\include"

# Debug mode specific settings
    build_pass:CONFIG(debug, debug|release) {
	    LIBS += "$$(CPPUNIT_DIR)\lib\cppunitd.lib"
	    LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += -L"debug"
	    LIBS += "BibleDatabase.lib"
     }

# Release mode specific settings
    build_pass:CONFIG(release, debug|release){
	    LIBS += "$$(CPPUNIT_DIR)\lib\cppunit.lib"
	    LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += -L"release"
	    LIBS += "BibleDatabase.lib"
    }

    QMAKE_POST_LINK = '"$(TargetPath)"'
}

unix {
    LIBS+=-l"cppunit"
}

