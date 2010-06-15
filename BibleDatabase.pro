TEMPLATE = lib
CONFIG += dll stl debug_and_release
CONFIG -= qt
QT -= core gui

HEADERS += BibleDatabase/ISearchResults.h
HEADERS += BibleDatabase/ICommand.h
HEADERS += BibleDatabase/SearchResultsSerial.h
HEADERS += BibleDatabase/Translation.h
HEADERS += BibleDatabase/TranslationBuffer.pb.h
HEADERS += BibleDatabase/TranslationBufferNoWarnings.pb.h
HEADERS += BibleDatabase/Verse.h
HEADERS += BibleDatabase/CommandPerformSearch.h
HEADERS += BibleDatabase/VerseDisplay.h
HEADERS += BibleDatabase/VerseTreeItem.h
HEADERS += BibleDatabase/TranslationManager.h
HEADERS += BibleDatabase/TranslationIterator.h
HEADERS += BibleDatabase/BibleDatabaseExporter.h

SOURCES += BibleDatabase/SearchResultsSerial.cpp
SOURCES += BibleDatabase/Translation.cpp
SOURCES += BibleDatabase/Verse.cpp
SOURCES += BibleDatabase/TranslationBuffer.pb.cc
SOURCES += BibleDatabase/CommandPerformSearch.cpp
SOURCES += BibleDatabase/VerseDisplay.cpp
SOURCES += BibleDatabase/VerseTreeItem.cpp
SOURCES += BibleDatabase/TranslationManager.cpp

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
    LIBS+=-l"protoc"
    LIBS+=-l"protobuf"
}

