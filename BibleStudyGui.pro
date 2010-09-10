TEMPLATE = lib
CONFIG += dll stl debug_and_release qt

HEADERS += BibleStudyGui/SearchResultsModel.h
HEADERS += BibleStudyGui/UISearchWidget.h
HEADERS += BibleStudyGui/UISearchResultsWidget.h
HEADERS += BibleStudyGui/UIBibleStudyWidget.h
HEADERS += BibleStudyGui/UITextViewWidget.h
HEADERS += BibleStudyGui/UIStarredVersesWidget.h
HEADERS += BibleStudyGui/StarredVersesModel.h
HEADERS += BibleStudyGui/BrowseVersesModel.h
HEADERS += BibleStudyGui/UIBrowseVersesWidget.h
HEADERS += BibleStudyGui/QtConnectHelper.h
HEADERS += BibleStudyGui/BackgroundWorker.h
HEADERS += BibleStudyGui/ProjectFileWriter.h
HEADERS += BibleStudyGui/QMutexLocker.h
HEADERS += BibleStudyGui/SearchPersistenceState.h
HEADERS += BibleStudyGui/StarredVersesPersistenceState.h
HEADERS += BibleStudyGui/ISerializable.h

SOURCES += BibleStudyGui/SearchResultsModel.cpp
SOURCES += BibleStudyGui/UISearchWidget.cpp
SOURCES += BibleStudyGui/UISearchResultsWidget.cpp
SOURCES += BibleStudyGui/UIBibleStudyWidget.cpp
SOURCES += BibleStudyGui/UITextViewWidget.cpp
SOURCES += BibleStudyGui/UIStarredVersesWidget.cpp
SOURCES += BibleStudyGui/StarredVersesModel.cpp
SOURCES += BibleStudyGui/BrowseVersesModel.cpp
SOURCES += BibleStudyGui/UIBrowseVersesWidget.cpp
SOURCES += BibleStudyGui/BackgroundWorker.cpp
SOURCES += BibleStudyGui/ProjectFileWriter.cpp
SOURCES += BibleStudyGui/SearchPersistenceState.cpp
SOURCES += BibleStudyGui/StarredVersesPersistenceState.cpp

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
