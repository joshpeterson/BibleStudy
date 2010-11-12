TEMPLATE = lib
CONFIG += dll stl debug_and_release console
CONFIG -= qt
QT -= core gui

HEADERS += ISearchResults.h
HEADERS += ICommand.h
HEADERS += SearchResultsSerial.h
HEADERS += Translation.h
HEADERS += TranslationBuffer.pb.h
HEADERS += TranslationBufferNoWarnings.pb.h
HEADERS += Verse.h
HEADERS += CommandPerformSearch.h
HEADERS += VerseDisplay.h
HEADERS += VerseTreeItem.h
HEADERS += TranslationManager.h
HEADERS += TranslationIterator.h
HEADERS += BibleDatabaseExporter.h
HEADERS += TranslationLoader.h
HEADERS += SearchStringParser.h
HEADERS += CommandLoadTranslation.h

SOURCES += SearchResultsSerial.cpp
SOURCES += Translation.cpp
SOURCES += Verse.cpp
SOURCES += TranslationBuffer.pb.cc
SOURCES += CommandPerformSearch.cpp
SOURCES += VerseDisplay.cpp
SOURCES += VerseTreeItem.cpp
SOURCES += TranslationManager.cpp
SOURCES += TranslationLoader.cpp
SOURCES += SearchStringParser.cpp
SOURCES += CommandLoadTranslation.cpp

DEFINES += _EXPORTING_BIBLE_DATABASE
DESTDIR = "../Output"

win32 {  
    QMAKE_CXXFLAGS_DEBUG += /wd4996
    QMAKE_CXXFLAGS_DEBUG += /wd4251
    QMAKE_CXXFLAGS_DEBUG += /wd4100
    
    QMAKE_CXXFLAGS_RELEASE += /wd4996
    QMAKE_CXXFLAGS_RELEASE += /wd4251
    QMAKE_CXXFLAGS_RELEASE += /wd4100
    
    INCLUDEPATH += "$$(BOOST_DIR)"
    INCLUDEPATH += "$$(GOOGLE_PROTOBUF_DIR)\include"
    
# Debug mode specific settings
    build_pass:CONFIG(debug, debug|release) {
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\debug\libprotoc.lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\debug\libprotobuf.lib"
     }

# Release mode specific settings
    build_pass:CONFIG(release, debug|release){
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\release\libprotoc.lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\release\libprotobuf.lib"
    }
}

unix {
    LIBS += -l"protobuf"
    LIBS += -l"boost_system"
}

