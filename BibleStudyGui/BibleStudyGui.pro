TEMPLATE = lib
CONFIG += dll stl debug_and_release qt

HEADERS += SearchResultsModel.h
HEADERS += UISearchWidget.h
HEADERS += UISearchResultsWidget.h
HEADERS += UIBibleStudyWidget.h
HEADERS += UITextViewWidget.h
HEADERS += UIStarredVersesWidget.h
HEADERS += StarredVersesModel.h
HEADERS += BrowseVersesModel.h
HEADERS += UIBrowseVersesWidget.h
HEADERS += QtConnectHelper.h
HEADERS += BackgroundWorker.h
HEADERS += Version.h

SOURCES += SearchResultsModel.cpp
SOURCES += UISearchWidget.cpp
SOURCES += UISearchResultsWidget.cpp
SOURCES += UIBibleStudyWidget.cpp
SOURCES += UITextViewWidget.cpp
SOURCES += UIStarredVersesWidget.cpp
SOURCES += StarredVersesModel.cpp
SOURCES += BrowseVersesModel.cpp
SOURCES += UIBrowseVersesWidget.cpp
SOURCES += BackgroundWorker.cpp

DEFINES += _EXPORTING_BIBLE_STUDY_GUI

win32 {
    INCLUDEPATH += "$$(BOOST_DIR)"

    QMAKE_LFLAGS += /IMPLIB:$(IntDir)$(TargetName).lib

# Debug mode specific settings
    build_pass:CONFIG(debug, debug|release) {
        DESTDIR = "../Output/debug"
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += "../BibleDatabase/debug/BibleDatabase.lib"
     }

# Release mode specific settings
    build_pass:CONFIG(release, debug|release){
        DESTDIR = "../Output/release"
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += "../BibleDatabase/release/BibleDatabase.lib"
    }
}

unix {
    DESTDIR = "../Output/lib"
    LIBS += -L"../Output/lib"
    LIBS += -l"BibleDatabase"
}
