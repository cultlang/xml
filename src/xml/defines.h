
#pragma once

//
// Platform Dynamic Library
//
#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define CULTLANG_XML_EXPORTED_EXPORT __attribute__ ((dllexport))
#define CULTLANG_XML_EXPORTED_IMPORT __attribute__ ((dllimport))
#else
#define CULTLANG_XML_EXPORTED_EXPORT __declspec(dllexport)
#define CULTLANG_XML_EXPORTED_IMPORT __declspec(dllimport)
#endif
#else
#if __GNUC__ >= 4
#define CULTLANG_XML_EXPORTED_EXPORT __attribute__ ((visibility ("default")))
#define CULTLANG_XML_EXPORTED_IMPORT
#else
#define CULTLANG_XML_EXPORTED_EXPORT
#define CULTLANG_XML_EXPORTED_IMPORT
#endif
#endif


//
// Engine Compile
//

#ifdef CULTLANG_XML_DLL
#define CULTLANG_XML_EXPORTED CULTLANG_XML_EXPORTED_EXPORT
#else
#define CULTLANG_XML_EXPORTED CULTLANG_XML_EXPORTED_IMPORT
#endif
