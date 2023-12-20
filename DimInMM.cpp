#include "AllChecks.h"
#include "DrawingModule.h"
#include <ProMdlUnits.h>
#include "Output.h"
#include "Utility.h"
#include <ProAsmcomppath.h>
#include <ProSolid.h>
#include <ProMessage.h>

using namespace std;

ProError SolidCompVisitMM(ProAsmcomppath* p_path, ProSolid handle, ProBoolean down, ProAppData app_data);


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
	wchar_t MsgFile[] = L"DrawingCheckV1.txt";


	ProDrawingViewsCollect(myDrawing, &views);
	ProArraySizeGet(views, &n_views);

	for (int i = 0;i < n_views;i++)
	{
		// Get Solids from all the views
		ProDrawingViewSolidGet(myDrawing, views[i], &solid);

		ProMdlType solid_type;
		ProMdlTypeGet((ProMdl)solid, &solid_type);

		if (solid_type == PRO_MDL_ASSEMBLY)
		{
			bool solidCompStatus = ProSolidDispCompVisit(solid, SolidCompVisitMM, NULL, NULL);

			if (solidCompStatus != PRO_TK_NO_ERROR)
			{
				status = PRO_TK_ABORT;
				break;
			}
			else if (solidCompStatus == PRO_TK_NO_ERROR)
			{
				status = PRO_TK_NO_ERROR;
			}
		}
		else if (solid_type == PRO_MDL_PART)
		{
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

	}

	if (status == PRO_TK_CONTINUE || status == PRO_TK_NO_ERROR)
	{
		string FinalOutput = "All parts are in MM\n";
		Output::PrintTxtFile("FinalOutPut.txt", FinalOutput);

	}
	return status;
}

ProError SolidCompVisitMM(ProAsmcomppath* p_path, ProSolid handle, ProBoolean down, ProAppData app_data)
{
	ProError status = PRO_TK_NO_ERROR;
	if (down == PRO_B_FALSE)
	{
		ProUnitsystem principalUnitSys;
		ProUnitsystemType unitType;
		ProUnititem lengthUnit;
		ProName MdlName;
		wchar_t MsgFile[] = L"DrawingCheckV1.txt";

		ProMdlType solid_type;
		ProMdlTypeGet((ProMdl)handle, &solid_type);

		ProName mdlname;
		ProMdlMdlnameGet((ProMdl)handle, mdlname);
		char cmdlname[99];
		ProWstringToString(cmdlname, mdlname);
		string smdlname = cmdlname;
		string SComps = smdlname + "\n";
		Output::PrintTxtFile("Components.txt", SComps);

		// Get unit system
		ProMdlPrincipalunitsystemGet((ProMdl)handle, &principalUnitSys);

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

			ProMdlNameGet((ProMdl)handle, MdlName);

			char cName[99];
			ProWstringToString(cName, MdlName);
			string sName = cName;

			char cLengthUnit[99];
			ProWstringToString(cLengthUnit, lengthUnit.name);
			string sLengthUnit = cLengthUnit;
			string mltMM = sName + " has length in " + sLengthUnit + "\n";
			Output::PrintTxtFile("mltLength.txt", mltMM);
			status = PRO_TK_NO_ERROR;
		}
		else if (wstring(lengthUnit.name) != L"mm")
		{
			ProMdlNameGet((ProMdl)handle, MdlName);

			char cName[99];
			ProWstringToString(cName, MdlName);
			string sName = cName;
			string mltMM = sName + " has length in " + sLengthUnit + "\n";
			Output::PrintTxtFile("mltLength.txt", mltMM);
			status = PRO_TK_ABORT;


		}

		/*if (solid_type == PRO_MDL_ASSEMBLY)
		{
			bool solidCompStatus = ProSolidDispCompVisit(handle, SolidCompVisitMM, NULL, NULL);

			if (solidCompStatus != PRO_TK_NO_ERROR)
			{
				status = PRO_TK_ABORT;
			}
			else if (solidCompStatus == PRO_TK_NO_ERROR)
			{
				status = PRO_TK_NO_ERROR;
			}
		}
		else if (solid_type == PRO_MDL_PART)
		{
			

		}*/

		
	}
	return status;
}

