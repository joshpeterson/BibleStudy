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

# Debug mode specific settings
    build_pass:CONFIG(debug, debug|release) {
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += -L"debug"
	    LIBS += "BibleDatabase.lib"
     }

# Release mode specific settings
    build_pass:CONFIG(release, debug|release){
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += -L"release"
	    LIBS += "BibleDatabase.lib"
    }
}

unix {
    DESTDIR = "../Output"
    LIBS += -l"BibleDatabase"
    LIBS += -L"../Output"
}
