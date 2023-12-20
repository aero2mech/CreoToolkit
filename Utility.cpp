#include "Utility.h"
#include <ProUtil.h>

using namespace std;

string Utility::WstringToString(wchar_t Name)
{
	char cName[99];
	ProWstringToString(cName, &Name);
	string sName = cName;
	return sName;

}