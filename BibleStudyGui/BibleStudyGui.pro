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
DESTDIR = "../Output"

win32 {
    INCLUDEPATH += "$$(BOOST_DIR)"

# Debug mode specific settings
    build_pass:CONFIG(debug, debug|release) {
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += -L"../Output"
        LIBS += "BibleDatabase.lib"
        QMAKE_POST_LINK = 'del /f ..\Output\Qt*4.dll;copy "$$(QT_DIR)\bin\QtGuid4.dll" ..\Output;copy "$$(QT_DIR)\bin\QtCored4.dll" ..\Output'
     }

# Release mode specific settings
    build_pass:CONFIG(release, debug|release){
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += -L"../Output"
        LIBS += "BibleDatabase.lib"
        QMAKE_POST_LINK = 'del /f ..\Output\Qt*4.dll;copy "$$(QT_DIR)\bin\QtGui4.dll" ..\Output;copy "$$(QT_DIR)\bin\QtCore4.dll" ..\Output'
    }
}

unix {
    LIBS += -L"../Output"
    LIBS += -l"BibleDatabase"
}
