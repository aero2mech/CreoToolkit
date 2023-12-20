#include "AllChecks.h"
#include "DrawingModule.h"
#include <ProMdlUnits.h>
#include "Output.h"
#include "Utility.h"
#include <ProAsmcomppath.h>
#include <ProSolid.h>

using namespace std;

ProError SolidCompVisit(ProAsmcomppath* p_path, ProSolid handle, ProBoolean down, ProAppData app_data);

ProError Checks::MaterialCheck(ProDrawing myDrawing)
{
	ProError status = PRO_TK_NO_ERROR;

	ProView* views;
	ProSolid solid;
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
			
			status = ProSolidDispCompVisit(solid, SolidCompVisit, NULL, NULL);
			
		}

		else if (solid_type == PRO_MDL_PART)
		{
			// Material check
			ProName* MaterialName = NULL;
			ProName wMaterialName = L"PTC_SYSTEM_MTRL_PROPS";
			int MSize = -1;
			ProArrayAlloc(0, sizeof(ProName), 1, (ProArray*)&MaterialName);
			ProPartMaterialsGet(solid, &MaterialName);
			ProArraySizeGet(MaterialName, &MSize);

			for (int j = 1;j < MSize;j++)
			{
				if (MSize <= 1)
				{
					return PRO_TK_ABORT;
				}
				else if (MaterialName[j] != L"PTC_SYSTEM_MTRL_PROPS" || MSize > 1)
				{
					char cMtrl[99];
					ProWstringToString(cMtrl, MaterialName[i]);
					string sMtrl = cMtrl;
					string Mtrl = "\n" + sMtrl;
					Output::PrintTxtFile("MaterialAssigned.txt", Mtrl);
				}
			}

		}
	}
	string FinalOutput = "All parts are assigned with Materials\n";
	Output::PrintTxtFile("FinalOutPut.txt", FinalOutput);
}

ProError SolidCompVisit(ProAsmcomppath* p_path, ProSolid handle, ProBoolean down, ProAppData app_data)
{
	ProError status = PRO_TK_NO_ERROR;
	if (down == PRO_B_FALSE)
	{

		ProName mdlname;
		ProMdlMdlnameGet((ProMdl)handle, mdlname);
		char cmdlname[99];
		ProWstringToString(cmdlname, mdlname);
		string smdlname = cmdlname;
		string ssMtrl = smdlname + "\n";
		Output::PrintTxtFile("MaterialAssigneds.txt", ssMtrl);

		// Material check
		ProName* MaterialName = NULL;
		ProName wMaterialName = L"PTC_SYSTEM_MTRL_PROPS";
		int MSize = -1;
		ProArrayAlloc(0, sizeof(ProName), 1, (ProArray*)&MaterialName);
		ProPartMaterialsGet(handle, &MaterialName);
		ProArraySizeGet(MaterialName, &MSize);

		for (int j = 1;j < MSize;j++)
		{
			if (MaterialName[j] == L"PTC_SYSTEM_MTRL_PROPS")
			{
				return PRO_TK_ABORT;
				
			}
			else if (MaterialName[j] != L"PTC_SYSTEM_MTRL_PROPS" || MSize > 1)
			{
				char cMtrl[99];
				ProWstringToString(cMtrl, MaterialName[j]);
				string sMtrl = cMtrl;
				string Mtrl = smdlname + " | " + sMtrl + "\n";
				Output::PrintTxtFile("MaterialAssigned.txt", Mtrl);
			}
		}

	}
	return status;
}

/*
ProName compName;
ProMdlNameGet(handle, compName);

char cMdlname[99];
ProWstringToString(cMdlname, compName);
string sMdlname = cMdlname;


// AsmComppath
string sAsmCompPath = "";

for (int i = 0;i < PRO_MAX_ASSEM_LEVEL;i++) // PRO_MAX_ASSEM_LEVEL = 25 - maximum
{
	sAsmCompPath = sAsmCompPath + ", " + to_string(p_path->comp_id_table[i]);

}

string compMsg = "\nComponent is: " + sMdlname +
" | " + sAsmCompPath +
" | Level: " + to_string(p_path->table_num);
Output::PrintTxtFile("Component List.txt", compMsg);
*/