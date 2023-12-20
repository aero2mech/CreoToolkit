#include "DrawingCheck.h"
#include <ProDrawing.h>

using namespace std;

bool DrawingSheet::sheet_has_views(int sheet)
{

}

Error IDrawing::GetAllDrawingView(VecIView AllDrawingViews)
{
	ProError status = PRO_TK_NO_ERROR;
	status = ProDrawingViewVisit(mDrawing, ViewVisit, NULL,(void*)&AllDrawingViews);
	return (Error)status;
}

ProError ViewVisit(ProDrawing xdrawing, ProView xview, ProError status, ProAppData xdata)
{
	VecIView* lView = (VecIView*)xdata;
	lView->push_back(new View(xview));

	return status;
}

int View::GetViewSheetNumber(IDrawing* xDrawing)
{

}