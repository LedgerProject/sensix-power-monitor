#pragma once

#include <hedley/hedley.h>

#if defined(_MSC_VER)
#define EXPORT_SYMBOL __declspec(dllexport)
#define IMPORT_SYMBOL __declspec(dllimport)
#elif defined(__GNUC__) || defined(__clang__)
#define EXPORT_SYMBOL __attribute__((visibility("default")))
#define IMPORT_SYMBOL
#else
#define EXPORT_SYMBOL
#define IMPORT_SYMBOL
#pragma warning Unknown dynamic link import / export semantics.
#endif

#ifndef ELSEN_NO_IMPORT_EXPORT_SEMANTICS
#ifdef ELSEN_LIB
#define ELSEN_API EXPORT_SYMBOL
#else
#define ELSEN_API IMPORT_SYMBOL
#endif
#else
#define ELSEN_API
#endif

#define ELSEN_TO_STRING_IMP(x) #x
#define ELSEN_TO_STRING(x) ELSEN_TO_STRING_IMP(x)

#define ELSEN_FIRST_ARG_(N, ...) N
#define ELSEN_FIRST_ARG(args) ELSEN_FIRST_ARG_ args

#define ELSEN_DISABLE_COPY(klass)           \
    explicit klass(const klass &) = delete; \
    klass &operator=(const klass &) = delete

#define ELSEN_DISABLE_MOVE(klass)      \
    explicit klass(klass &&) = delete; \
    klass &operator=(klass &&) = delete

#define ELSEN_UNUSED(var) static_cast<void>(var)

#ifdef __clang__
#define ELSEN_DIAGNOSTIC_IGNORE_OLD_STYLE_CAST \
    HEDLEY_PRAGMA(clang diagnostic ignored "-Wold-style-cast")
#define ELSEN_DIAGNOSTIC_IGNORE_USELESS_CAST \
    HEDLEY_PRAGMA(clang diagnostic ignored "-Wuseless-cast")
#define ELSEN_DIAGNOSTIC_IGNORE_KEYWORD_MACRO \
    HEDLEY_PRAGMA(clang diagnostic ignored "-Wkeyword-macro")
#elif __GNUG__
#define ELSEN_DIAGNOSTIC_IGNORE_OLD_STYLE_CAST \
    HEDLEY_PRAGMA(GCC diagnostic ignored "-Wold-style-cast")
#define ELSEN_DIAGNOSTIC_IGNORE_USELESS_CAST HEDLEY_PRAGMA(GCC diagnostic ignored "-Wuseless-cast")
#define ELSEN_DIAGNOSTIC_IGNORE_KEYWORD_MACRO \
    HEDLEY_PRAGMA(GCC diagnostic ignored "-Wkeyword-macro")
#else
#define ELSEN_DIAGNOSTIC_IGNORE_OLD_STYLE_CAST
#define ELSEN_DIAGNOSTIC_IGNORE_USELESS_CAST
#define ELSEN_DIAGNOSTIC_IGNORE_KEYWORD_MACRO
#endif
