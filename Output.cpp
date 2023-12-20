#include "Output.h"


void Output::PrintTxtFile(string sFilename, string sMessage)
{
	FILE* outputFile = NULL;
	string sFilePath = "F:\\creo customization\\Self Practice\\DrawingCheckV1\\PrintTxtfile\\" + sFilename;
	outputFile = fopen((char*)sFilePath.c_str(), "a");
	fprintf(outputFile, (char*)sMessage.c_str());
	fclose(outputFile);


}