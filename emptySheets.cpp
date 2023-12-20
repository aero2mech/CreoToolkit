#include "AllChecks.h"
#include "DrawingModule.h"
#include "DrawingCheck.h"
#include <ProMdlUnits.h>
#include "Output.h"
#include <ProDtlentity.h>
#include <ProDtlnote.h>
#include <ProDtlsymdef.h>
#include <ProDtlsyminst.h>
#include <ProDtlgroup.h>
#include <vector>
#include <ProMessage.h>

//
#include "AllChecks.h"
#include "DrawingModule.h"
#include <ProMdlUnits.h>
#include "Output.h"
#include "Utility.h"
#include <ProAsmcomppath.h>
#include <ProSolid.h>
// 


using namespace std;

ProError ViewVisit(ProDrawing xDrawing, ProView xView, ProError status, ProAppData appData);

ProError Checks::IsSheetEmpty(ProDrawing myDrawing)
{
	ProError err = PRO_TK_NO_ERROR;
	//ProDrawing mpDrawing;
	int sheet, n_sheet;
	ProDrawingSheetsCount(myDrawing, &n_sheet);

	for (sheet = 1; sheet <= n_sheet; sheet++)
	{
		if (Sheet_has_views(sheet))
		{
			continue;
		}
	}
	if (err == PRO_TK_CONTINUE || err == PRO_TK_NO_ERROR)
	{
		string FinalOutput = "Drawing doesn't have empty sheets\n";
		Output::PrintTxtFile("FinalOutPut.txt", FinalOutput);

	}

	string sheetname = "Total number of sheets are: " + to_string(n_sheet);
	ProMessageDisplay(L"DrawingCheckV1.txt", (char*)sheetname.c_str());
	return PRO_TK_NO_ERROR;
}

bool Checks::Sheet_has_views(int sheet)
{
	ProError err = PRO_TK_NO_ERROR;
	ProMdl Mdl;
	err = ProMdlCurrentGet(&Mdl);

	bool res = false;
	vector <ProView> allViews;
	err = ProDrawingViewVisit((ProDrawing)Mdl, ViewVisit, NULL, &allViews);
	for (vector<ProView>::iterator itr = allViews.begin(); itr != allViews.end(); itr++)
	{


		if (GetViewSheetNumber((ProDrawing)Mdl, *itr) == sheet)
		{
			res = true;
			err = PRO_TK_CONTINUE;
		}
	}
	
	return err;

}

ProError ViewVisit(ProDrawing xDrawing, ProView xView, ProError status, ProAppData appData)
{
	ProError err = PRO_TK_NO_ERROR;
	vector <ProView>* allViews = (vector<ProView>*) appData;
	allViews->push_back(xView);

	return err;
}

int Checks::GetViewSheetNumber(ProDrawing myDrawing, ProView myView)
{
	ProError err = PRO_TK_NO_ERROR;
	ProMdl Mdl;
	err = ProMdlCurrentGet(&Mdl);
	int sheetNum = -1;
	err = ProDrawingViewSheetGet((ProDrawing)Mdl, myView, &sheetNum);

		

	return sheetNum;

}

