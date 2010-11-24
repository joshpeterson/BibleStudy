TEMPLATE = lib
CONFIG += staticlib stl debug_and_release qt

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

win32 {
    INCLUDEPATH += "$$(BOOST_DIR)"
}

unix {
    LIBS += -L"../BibleDatabase"
    LIBS += -l"BibleDatabase"
}
