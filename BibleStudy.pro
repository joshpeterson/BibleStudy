TEMPLATE = app
CONFIG += windows qt thread exceptions stl debug_and_release

SOURCES += BibleStudy.cpp


win32 {
    INCLUDEPATH += "$$(BOOST_DIR)"

# Debug mode specific settings
    build_pass:CONFIG(debug, debug|release) {
        DESTDIR = "Output/debug"
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += -L"Output/debug"
        LIBS += "BibleDatabase.lib"
        LIBS += "BibleStudyGui.lib"
     }

# Release mode specific settings
    build_pass:CONFIG(release, debug|release){
        DESTDIR = "Output/release"
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += -L"Output/release"
        LIBS += "BibleDatabase.lib"
        LIBS += "BibleStudyGui.lib"
    }
}

unix {
    DESTDIR = "Output"
    LIBS += -L"Output"
    LIBS += -l"BibleDatabase"
    LIBS += -l"BibleStudyGui"
}
