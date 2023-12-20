#include "AllChecks.h"
#include "DrawingModule.h"
#include <ProMdlUnits.h>
#include "Output.h"
#include "Utility.h"
#include <ProAsmcomppath.h>
#include <ProSolid.h>
#include <ProMessage.h>

using namespace std;


ProError Checks::DimInMM(ProDrawing myDrawing)
{
	ProError status = PRO_TK_NO_ERROR;

	ProView* views;
	ProSolid solid;
	ProUnitsystem principalUnitSys;
	ProUnitsystemType unitType;
	ProUnititem lengthUnit;
	ProName MdlName;
	int n_views;


	ProDrawingViewsCollect(myDrawing, &views);
	ProArraySizeGet(views, &n_views);
	wchar_t MsgFile[] = L"DrawingCheckV1.txt";

	for (int i = 0;i < n_views;i++)
	{
		// Get Solids from all the views
		ProDrawingViewSolidGet(myDrawing, views[i], &solid);

		ProMdlType solid_type;
		ProMdlTypeGet((ProMdl)solid, &solid_type);

		// Get unit system
		ProMdlPrincipalunitsystemGet((ProMdl)solid, &principalUnitSys);

		// Get Unit Type
		ProUnitsystemTypeGet(&principalUnitSys, &unitType);

		status = ProUnitsystemUnitGet(&principalUnitSys, PRO_UNITTYPE_LENGTH, &lengthUnit);


		char cLengthUnit[99];
		ProWstringToString(cLengthUnit, lengthUnit.name);
		string sLengthUnit = cLengthUnit;
		ProMessageDisplay(MsgFile, (char*)sLengthUnit.c_str());

		//
		if (wstring(lengthUnit.name) == L"mm")
		{

			ProMdlNameGet((ProMdl)solid, MdlName);

			char cName[99];
			ProWstringToString(cName, MdlName);
			string sName = cName;

			char cLengthUnit[99];
			ProWstringToString(cLengthUnit, lengthUnit.name);
			string sLengthUnit = cLengthUnit;
			string mltMM = sName + " has length in " + sLengthUnit + "\n";
			Output::PrintTxtFile("mltLength.txt", mltMM);
		}
		else if (wstring(lengthUnit.name) != L"mm")
		{
			return PRO_TK_ABORT;

			break;

		}
		
	}

	string FinalOutput = "All parts are in MM unit system\n";
	Output::PrintTxtFile("FinalOutPut.txt", FinalOutput);

}

