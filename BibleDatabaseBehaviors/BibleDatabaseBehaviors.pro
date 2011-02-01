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

win32 {
    QMAKE_CXXFLAGS_DEBUG += /wd4100
    
    QMAKE_CXXFLAGS_RELEASE += /wd4100
    
    INCLUDEPATH += "$$(CPPUNIT_DIR)\include"
    INCLUDEPATH += "$$(BOOST_DIR)"
    INCLUDEPATH += "$$(GOOGLE_PROTOBUF_DIR)\include"

# Debug mode specific settings
    build_pass:CONFIG(debug, debug|release) {
        DESTDIR = "../Output/debug"
        LIBS += "$$(CPPUNIT_DIR)\lib\cppunitd.lib"
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += "../BibleDatabase/debug/BibleDatabase.lib"
     }

# Release mode specific settings
    build_pass:CONFIG(release, debug|release){
        DESTDIR = "../Output/release"
        LIBS += "$$(CPPUNIT_DIR)\lib\cppunit.lib"
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += "../BibleDatabase/release/BibleDatabase.lib"
    }
}

unix {
    DEFINES = LINUX
    DESTDIR = "../Output/bin"
    LIBS += -L"../Output/lib"
    LIBS += -l"cppunit"
    LIBS += -l"boost_filesystem"
    LIBS += -l"BibleDatabase"
}

