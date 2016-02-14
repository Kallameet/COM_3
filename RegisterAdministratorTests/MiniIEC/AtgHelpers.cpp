#include "AtgHelpers.h"

std::wstring CreateWString(wchar_t* val)
{
	return std::wstring(val);
}

std::string CreateString(std::wstring val)
{
	return std::string(val.begin(), val.end());
}