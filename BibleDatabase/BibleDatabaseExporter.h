#ifndef __BIBLE_DATABASE_EXPORTER_H
#define __BIBLE_DATABASE_EXPORTER_H

#ifdef WIN32
    #ifdef _EXPORTING_BIBLE_DATABASE
        #define BIBLE_DATABASE_EXPORT __declspec(dllexport)
    #else // _EXPORTING_BIBLE_DATABASE
        #define BIBLE_DATABASE_EXPORT __declspec(dllimport)
    #endif // _EXPORTING_BIBLE_DATABASE
#endif // WIN32

#endif // __BIBLE_DATABASE_EXPORTER_H