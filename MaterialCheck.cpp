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
			bool solidCompStatus = ProSolidDispCompVisit(solid, SolidCompVisit, NULL, NULL);

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

			// Material check
			ProName* MaterialName = NULL;
			ProName wMaterialName = L"PTC_SYSTEM_MTRL_PROPS";
			int MSize = -1;
			ProArrayAlloc(0, sizeof(ProName), 1, (ProArray*)&MaterialName);
			ProPartMaterialsGet(solid, &MaterialName);
			ProArraySizeGet(MaterialName, &MSize);

			for (int j = 1;j < MSize;j++)
			{
				char cMtrl[99];
				ProWstringToString(cMtrl, MaterialName[j]);
				string sMtrl = cMtrl;
				string Mtrl = "\n" + sMtrl;
				Output::PrintTxtFile("MaterialAssigned.txt", Mtrl);
			}
			if (/*MSize <= 1 or */wstring(MaterialName[1]) == L"")
			{
				string smmm = "No Material assigned\n";
				Output::PrintTxtFile("MaterialAssign.txt", smmm);
				status = PRO_TK_ABORT;
				//break;

			}
			else if (/*MSize > 1 or */wstring(MaterialName[1]) != L"")
			{
				char csmm[99];
				ProWstringToString(csmm, MaterialName[1]);
				string ssmm = csmm;
				string smm = "Material assigned " + ssmm + "\n";
				Output::PrintTxtFile("MaterialAssign.txt", smm);
				status = PRO_TK_CONTINUE;
			}
		}

	}
	if (status == PRO_TK_CONTINUE || status == PRO_TK_NO_ERROR)
	{
		string FinalOutput = "All parts are assigned with Materials\n";
		Output::PrintTxtFile("FinalOutPut.txt", FinalOutput);

	}
	return status;
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
		string SComps = smdlname + "\n";
		Output::PrintTxtFile("Components.txt", SComps);

		

		// Material check
		ProName* MaterialName = NULL;
		ProName wMaterialName = L"PTC_SYSTEM_MTRL_PROPS";
		int MSize = -1;
		ProArrayAlloc(0, sizeof(ProName), 1, (ProArray*)&MaterialName);
		ProPartMaterialsGet(handle, &MaterialName);
		ProArraySizeGet(MaterialName, &MSize);

		for (int j = 0;j < MSize;j++)
		{

			char cMtrl[99];
			ProWstringToString(cMtrl, MaterialName[j]);
			string sMtrl = cMtrl;
			string Mtrl = smdlname + " | " + sMtrl + "\n";
			Output::PrintTxtFile("MaterialAssigned.txt", Mtrl);

			if (wstring(MaterialName[1]) == L"" ||
				wstring(MaterialName[1]) == wMaterialName)
			{
				char csmm[99];
				ProWstringToString(csmm, MaterialName[1]);
				string ssmm = csmm;
				string smm = "No Material assigned\n";
				Output::PrintTxtFile("MaterialAssign.txt", smm);
				status = PRO_TK_ABORT;
			}
			else if (wstring(MaterialName[1]) != L"" || wstring(MaterialName[1]) != wMaterialName)
			{
				char csmm[99];
				ProWstringToString(csmm, MaterialName[1]);
				string ssmm = csmm;
				string smm = "Material assigned " + ssmm + "\n";
				Output::PrintTxtFile("MaterialAssign.txt", smm);
				status = PRO_TK_NO_ERROR;
			}

		}
	}
	return status;
}

