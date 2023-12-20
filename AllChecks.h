#pragma once
#include <iostream>
#include <ProToolkit.h>
#include <ProMdl.h>
#include <ProDrawing.h>
#include "DrawingCheck.h"

using namespace std;

class Checks
{
public:
	static ProError DimInMM(ProDrawing myDrawing);
	static ProError MaterialCheck(ProDrawing myDrawing);
	static ProError IsSheetEmpty(ProDrawing myDrawing);
	static bool Sheet_has_views(int sheet);
	static int GetViewSheetNumber(ProDrawing myDrawing, ProView myView);


private:

};