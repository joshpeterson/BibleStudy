CONFIG += qt thread exceptions stl debug_and_release

HEADERS += IDocument.h
HEADERS += IEntry.h
HEADERS += ISearchResults.h
HEADERS += IVerse.h
HEADERS += ICommand.h
HEADERS += SearchResultsModel.h
HEADERS += SearchResultsSerial.h
HEADERS += Translation.h
HEADERS += TranslationBuffer.pb.h
HEADERS += TranslationBufferNoWarnings.pb.h
HEADERS += UISearchWidget.h
HEADERS += Verse.h
HEADERS += UISearchResultsWidget.h
HEADERS += UIBibleStudyWidget.h
HEADERS += CommandPerformSearch.h
HEADERS += UITextViewWidget.h
HEADERS += UIStarredVersesWidget.h
HEADERS += StarredVersesModel.h
HEADERS += VerseDisplay.h
HEADERS += BrowseVersesModel.h
HEADERS += UIBrowseVersesWidget.h
HEADERS += VerseTreeItem.h
#HEADERS += BrowseVersesDelegate.h

SOURCES += BibleStudy.cpp
SOURCES += SearchResultsModel.cpp
SOURCES += SearchResultsSerial.cpp
SOURCES += Translation.cpp
SOURCES += UISearchWidget.cpp
SOURCES += Verse.cpp
SOURCES += TranslationBuffer.pb.cc
SOURCES += UISearchResultsWidget.cpp
SOURCES += UIBibleStudyWidget.cpp
SOURCES += CommandPerformSearch.cpp
SOURCES += UITextViewWidget.cpp
SOURCES += UIStarredVersesWidget.cpp
SOURCES += StarredVersesModel.cpp
SOURCES += VerseDisplay.cpp
SOURCES += BrowseVersesModel.cpp
SOURCES += UIBrowseVersesWidget.cpp
SOURCES += VerseTreeItem.cpp
#SOURCES += BrowseVersesDelegate.cpp

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
