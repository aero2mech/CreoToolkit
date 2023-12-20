#include "AllChecks.h"
#include "DrawingModule.h"
#include <ProMdlUnits.h>
#include "Output.h"
#include "Utility.h"
#include <ProAsmcomppath.h>
#include <ProSolid.h>

using namespace std;

ProError SolidCompVisitUnit(ProAsmcomppath* p_path, ProSolid handle, ProBoolean down, ProAppData app_data);

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

	for (int i = 0;i < n_views;i++)
	{
		// Get Solids from all the views
		ProDrawingViewSolidGet(myDrawing, views[i], &solid);

		ProMdlType solid_type;
		ProMdlTypeGet((ProMdl)solid, &solid_type);

		if (solid_type == PRO_MDL_ASSEMBLY)
		{
			ProSolidDispCompVisit(solid, SolidCompVisitUnit, NULL, NULL);

		}
		else if (solid_type == PRO_MDL_PART)
		{
			// Get unit system
			ProMdlPrincipalunitsystemGet((ProMdl)solid, &principalUnitSys);

			// Get Unit Type
			ProUnitsystemTypeGet(&principalUnitSys, &unitType);

			ProUnitsystemUnitGet(&principalUnitSys, PRO_UNITTYPE_LENGTH, &lengthUnit);


			//
			if (unitType == PRO_UNITLENGTH_MM)
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
			else {
				return PRO_TK_ABORT;
			}

		}

		
	}

	string FinalOutput = "All parts are in MM unit system\n";
	Output::PrintTxtFile("FinalOutPut.txt", FinalOutput);

}

ProError SolidCompVisitUnit(ProAsmcomppath* p_path, ProSolid handle, ProBoolean down, ProAppData app_data)
{
	ProError status = PRO_TK_NO_ERROR;

	ProUnitsystem principalUnitSys;
	ProUnitsystemType unitType;
	ProUnititem lengthUnit;
	ProName MdlName;

	if (down == PRO_B_FALSE)
	{

		// Get unit system
		ProMdlPrincipalunitsystemGet((ProMdl)handle, &principalUnitSys);

		// Get Unit Type
		ProUnitsystemTypeGet(&principalUnitSys, &unitType);

		ProUnitsystemUnitGet(&principalUnitSys, PRO_UNITTYPE_LENGTH, &lengthUnit);


		//
		if (unitType == PRO_UNITLENGTH_MM)
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

		}
		else {
			return PRO_TK_ABORT;
		}

	}
	return status;
}


/*if (unitType != PRO_UNITSYSTEM_MLT)
		{
			return PRO_TK_ABORT;

			ProMdlNameGet((ProMdl)solid, MdlName);

			char cName[99];
			ProWstringToString(cName, MdlName);
			string sName = cName;


			string noMLT = sName + " is not MLT unit system\n";

			Output::PrintTxtFile("NoMLT.txt", noMLT);
		}
		else if (unitType == PRO_UNITSYSTEM_MLT)
		{
			ProUnitsystemUnitGet(&principalUnitSys, PRO_UNITTYPE_LENGTH, &lengthUnit);

			ProMdlNameGet((ProMdl)solid, MdlName);

			char cName[99];
			ProWstringToString(cName, MdlName);
			string sName = cName;

			char cLengthUnit[99];
			ProWstringToString(cLengthUnit, lengthUnit.name);
			string sLengthUnit = cLengthUnit;
			string mltMM = sName + " has length in " + sLengthUnit + "\n";
			Output::PrintTxtFile("mltLength.txt", mltMM);

			if (lengthUnit.name == L"mm")
			{
				return PRO_TK_NO_ERROR;
			}
			else 
			{
				return PRO_TK_ABORT;
				/*string MM = "Some Parts are not in MM unit system!!\n";
				Output::PrintTxtFile("mltMM.txt", MM);
			}

		}*/