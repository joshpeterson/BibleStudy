CONFIG += qt thread exceptions stl debug_and_release

HEADERS += IDocument.h
HEADERS += IEntry.h
HEADERS += ISearchResults.h
HEADERS += IVerse.h
HEADERS += SearchResultsModel.h
HEADERS += SearchResultsSerial.h
HEADERS += Translation.h
HEADERS += TranslationBuffer.pb.h
HEADERS += UISearchWidget.h
HEADERS += Verse.h
HEADERS += UISearchResultsWidget.h
HEADERS += UIBibleStudyWidget.h

SOURCES += BibleStudy.cpp
SOURCES += SearchResultsModel.cpp
SOURCES += SearchResultsSerial.cpp
SOURCES += Translation.cpp
SOURCES += UISearchWidget.cpp
SOURCES += Verse.cpp
SOURCES += TranslationBuffer.pb.cc
SOURCES += UISearchResultsWidget.cpp
SOURCES += UIBibleStudyWidget.cpp

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