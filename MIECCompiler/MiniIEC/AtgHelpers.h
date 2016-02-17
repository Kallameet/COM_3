#ifndef ATGHELPERS_H
#define ATGHELPERS_H

#include <string>
#include "BaseType.h"
#include "Symbol.h"

/**
* <summary> Converts a wchar_t* to a wstring. </summary>
*
* <param name="val"> Value that will be converted. </param>
*
* <returns> Returns the converted wstring. </returns>
*/
std::wstring CreateWString(wchar_t* val);

/**
* <summary> Converts a wstring to a string. </summary>
*
* <param name="val"> Value that will be converted. </param>
*
* <returns> Returns the converted string. </returns>
*/
std::string CreateString(std::wstring val);

#endif
