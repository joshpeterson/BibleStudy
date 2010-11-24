TEMPLATE = app
CONFIG += windows qt thread exceptions stl debug_and_release

SOURCES += BibleStudy.cpp

win32 {
    INCLUDEPATH += "$$(BOOST_DIR)"

# Debug mode specific settings
    build_pass:CONFIG(debug, debug|release) {
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\debug\libprotoc.lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\debug\libprotobuf.lib"
        LIBS += -L"BibleDatabase/debug"
        LIBS += -L"BibleStudyGui/debug"
        LIBS += "BibleDatabase.lib"
        LIBS += "BibleStudyGui.lib"
     }

# Release mode specific settings
    build_pass:CONFIG(release, debug|release){
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\release\libprotoc.lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\release\libprotobuf.lib"
        LIBS += -L"BibleDatabase/release"
        LIBS += -L"BibleStudyGui/release"
        LIBS += "BibleDatabase.lib"
        LIBS += "BibleStudyGui.lib"
    }
}

unix {
    LIBS += -L"BibleDatabase"
    LIBS += -L"BibleStudyGui"
    LIBS += -l"BibleDatabase"
    LIBS += -l"BibleStudyGui"
}
