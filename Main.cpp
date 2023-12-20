#include <string>
#include <ProMenuBar.h>
#include <ProUICmd.h>
#include <ProMdl.h>
#include <ProMessage.h>
#include <ProUIMessage.h>
#include <ProArray.h>
#include "partModule.h"
#include "AllChecks.h"


using namespace std;

int DrawingCheckAction(uiCmdCmdId command, uiCmdValue* p_value, void* p_push_command_data);
uiCmdAccessState DrawingCheckAccess(uiCmdAccessMode access_mode);

wchar_t MsgFile[] = L"DrawingCheckV1.txt";

extern "C" int user_initialize()
{
	ProErr status = PRO_TK_NO_ERROR;
	uiCmdCmdId action_id;

	// Menu bar
	status = ProMenubarMenuAdd("Start", "Start_Label", NULL, PRO_B_TRUE, MsgFile);

	// Push buttons

	// Part
	status = ProCmdActionAdd("DrawingCheck", DrawingCheckAction, uiProe2ndImmediate, DrawingCheckAccess, PRO_B_TRUE, PRO_B_TRUE, &action_id);

	status = ProMenubarmenuPushbuttonAdd("Start", "DrawingCheck", "DrawingCheck_Label", "DrawingCheck_Helptext", NULL, PRO_B_TRUE, action_id, MsgFile);
	
	// Set Icon
	status = ProCmdIconSet(action_id, "beer.png");

	
	return 0;
}

extern "C" void user_terminate()
{

}

// Drawing Checks
int DrawingCheckAction(uiCmdCmdId command, uiCmdValue* p_value, void* p_push_command_data)
{
	ProErr status = PRO_TK_NO_ERROR;

	ProMdl Mdl;
	status = ProMdlCurrentGet(&Mdl);

	ProMdlType MdlType;
	status = ProMdlTypeGet(Mdl, &MdlType);

	if (MdlType == PRO_MDL_DRAWING)
	{
		Checks::DimInMM((ProDrawing)Mdl);
		Checks::MaterialCheck((ProDrawing)Mdl);
		Checks::IsSheetEmpty((ProDrawing)Mdl);


	}

	return status;
}

uiCmdAccessState DrawingCheckAccess(uiCmdAccessMode access_mode)
{

	return ACCESS_AVAILABLE;
}

