CONFIG += qt thread exceptions stl debug_and_release

HEADERS += TranslationLoaderBehavior.h

SOURCES += BibleStudyBehaviors.cpp

win32 {
    INCLUDEPATH += "$$(BOOST_DIR)"
    INCLUDEPATH += "$$(GOOGLE_PROTOBUF_DIR)\include"
    INCLUDEPATH += "$$(CPPUNIT_DIR)\include"

# Debug mode specific settings
    build_pass:CONFIG(debug, debug|release) {
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\debug\libprotoc.lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\debug\libprotobuf.lib"
	LIVS += "$$(CPPUNIT_DIR)\lib"
     }

# Release mode specific settings
    build_pass:CONFIG(release, debug|release){
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\release\libprotoc.lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\release\libprotobuf.lib"
	LIBS += "$$(CPPUNIT_DIR)\lib"
    }
}

unix {
    LIBS+=-l"protoc"
    LIBS+=-l"protobuf"
}

