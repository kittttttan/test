#ifndef DLL_H_
#define DLL_H_

#if defined (__GNUC__)
#define EXPORT  __declspec(__dllexport__)
#define IMPORT  __declspec(__dllimport__)
#endif
#if defined (_MSC_VER) || defined (__BORLANDC__)
#define EXPORT  __declspec(dllexport)
#define IMPORT  __declspec(dllimport)
#endif
#ifdef __WATCOMC__
#define EXPORT  __export
#define IMPORT  __import
#endif
#ifdef __IBMC__
#define EXPORT  _Export
#define IMPORT  _Import
#endif

#ifdef DLL_EXPORT
#define DECLSPEC EXPORT
#else
#define DECLSPEC IMPORT
#endif

typedef unsigned char BYTE;

#ifdef __cplusplus
extern "C" {
#endif

DECLSPEC void CColorImage(void* buffer, int width, int height,
  BYTE b, BYTE g, BYTE r);
DECLSPEC void CCalcMandel(void* buf, int width, int height, int limit, double scale);

#ifdef __cplusplus
}
#endif

#endif