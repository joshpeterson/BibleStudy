#ifndef __TRANSLATION_BUFFER_NO_WARNINGS_PB_H
#define __TRANSLATION_BUFFER_NO_WARNINGS_PB_H

#ifdef _WINDOWS
#pragma warning(push)
#pragma warning(disable : 4018)
#pragma warning(disable : 4146)
#pragma warning(disable : 4244)
#pragma warning(disable : 4251)
#pragma warning(disable : 4267)
#pragma warning(disable : 4305)
#pragma warning(disable : 4355)
#pragma warning(disable : 4800)
#pragma warning(disable : 4996)
#include "TranslationBuffer.pb.h"
#pragma warning(pop)
#else
#include "TranslationBuffer.pb.h"
#endif

#endif //__TRANSLATION_BUFFER_NO_WARNINGS_PB_H
