CONFIG += console qt thread exceptions stl debug_and_release

HEADERS += TranslationLoaderBehavior.h

SOURCES += BibleStudyBehaviors.cpp

win32 {
    INCLUDEPATH += "$$(CPPUNIT_DIR)\include"
    INCLUDEPATH += "$$(BOOST_DIR)"
    INCLUDEPATH += "$$(GOOGLE_PROTOBUF_DIR)\include"

# Debug mode specific settings
    build_pass:CONFIG(debug, debug|release) {
	LIBS += "$$(CPPUNIT_DIR)\lib\cppunitd.lib"
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\debug\libprotoc.lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\debug\libprotobuf.lib"
     }

# Release mode specific settings
    build_pass:CONFIG(release, debug|release){
	LIBS += "$$(CPPUNIT_DIR)\lib\cppunit.lib"
        LIBS += -L"$$(BOOST_DIR)\lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\release\libprotoc.lib"
        LIBS += "$$(GOOGLE_PROTOBUF_DIR)\release\libprotobuf.lib"
    }

    QMAKE_POST_LINK = '"$(TargetPath)"'
}

unix {
    LIBS+=-l"protoc"
    LIBS+=-l"protobuf"
    LIBS+=-l"cppunit"
}

