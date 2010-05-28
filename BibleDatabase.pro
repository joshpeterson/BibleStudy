TEMPLATE = lib
CONFIG += dll stl debug_and_release
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

SOURCES += SearchResultsSerial.cpp
SOURCES += Translation.cpp
SOURCES += Verse.cpp
SOURCES += TranslationBuffer.pb.cc
SOURCES += CommandPerformSearch.cpp
SOURCES += VerseDisplay.cpp
SOURCES += VerseTreeItem.cpp
SOURCES += TranslationManager.cpp

win32 {
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

