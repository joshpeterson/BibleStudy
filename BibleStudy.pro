TEMPLATE = app
CONFIG += windows qt thread exceptions stl debug_and_release

SOURCES += BibleStudy.cpp

win32 {
    INCLUDEPATH += "$$(BOOST_DIR)"

# Debug mode specific settings
    build_pass:CONFIG(debug, debug|release) {
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += -L"debug"
	    LIBS += "BibleDatabase.lib"
	    LIBS += BibleStudyGui.lib"
     }

# Release mode specific settings
    build_pass:CONFIG(release, debug|release){
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += -L"release"
	    LIBS += "BibleDatabase.lib"
	    LIBS += "BibleStudyGui.lib"
    }
}
