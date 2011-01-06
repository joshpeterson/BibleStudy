TEMPLATE = app
CONFIG += windows qt thread exceptions stl debug_and_release

SOURCES += BibleStudy.cpp


win32 {
    RC_FILE=BibleStudy.rc
    INCLUDEPATH += "$$(BOOST_DIR)"

# Debug mode specific settings
    build_pass:CONFIG(debug, debug|release) {
        DESTDIR = "Output/debug"
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += "BibleDatabase/debug/BibleDatabase.lib"
        LIBS += "BibleStudyGui/debug/BibleStudyGui.lib"
     }

# Release mode specific settings
    build_pass:CONFIG(release, debug|release){
        DESTDIR = "Output/release"
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += "BibleDatabase/release/BibleDatabase.lib"
        LIBS += "BibleStudyGui/release/BibleStudyGui.lib"
    }
}

unix {
    DESTDIR = "Output"
    LIBS += -L"Output"
    LIBS += -l"BibleDatabase"
    LIBS += -l"BibleStudyGui"
}
