TEMPLATE = app
CONFIG += console exceptions stl debug_and_release
CONFIG -= qt
QT -= core gui

HEADERS += BehaviorDrivenDesign.h
HEADERS += BehaviorDrivenDesignTest.h
HEADERS += TranslationLoaderBehavior.h
HEADERS += TranslationBehaviorGivens.h
HEADERS += TranslationFirstAndLastVerseBehavior.h
HEADERS += TranslationSearchBehavior.h
HEADERS += SearchStringParserBehavior.h

SOURCES += BibleDatabaseBehaviors.cpp
DESTDIR = "../Output"

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
        LIBS += -L"../Output"
        LIBS += "BibleDatabase.lib"
     }

# Release mode specific settings
    build_pass:CONFIG(release, debug|release){
        LIBS += "$$(CPPUNIT_DIR)\lib\cppunit.lib"
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += -L"../Output"
        LIBS += "BibleDatabase.lib"
    }

    QMAKE_POST_LINK = '"$(TargetPath)"'
}

unix {
    LIBS += -L"../Output"
    LIBS += -l"cppunit"
    LIBS += -l"boost_filesystem"
    LIBS += -l"BibleDatabase"
}

