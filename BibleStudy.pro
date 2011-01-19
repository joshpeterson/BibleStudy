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
    LIBS += -L"Output/lib"
    LIBS += -l"BibleDatabase"
    LIBS += -l"BibleStudyGui"

    TARGET = "bin/BibleStudy"
    target.path = /usr/bin
    INSTALLS += target

    libraries.path = /usr/lib
    libraries.files = $$DESTDIR/lib/lib*.so*
    INSTALLS += libraries

    translations.path = /usr/share/BibleStudy/Translations
    translations.files = $$DESTDIR/share/BibleStudy/Translations/*.buf
    INSTALLS += translations

    icons.path = /usr/share/BibleStudy/icons
    icons.files = $$DESTDIR/share/BibleStudy/icons/*
    INSTALLS += icons
}
