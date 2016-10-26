// This is the main DLL file.

#include "stdafx.h"
#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "ProgressBar.h"

using namespace std;

extern "C"
{
	__declspec(dllexport) int GETSIZE(const string file_name)
	{
		/*---------------------------------------- GETSIZE -----
		|  Function 	GETSIZE()
		|
		|  Purpose:		This is a static object that will return
		|				the size of a file.
		|
		|  Parameters:
		|	file_name (IN) --	the name of file you would like to
		|						parse
		|
		|  Returns:		an integer of the size of the file
		*-------------------------------------------------------*/

		ifstream scalerfile;
		int length;
		scalerfile.open(file_name);
		if (scalerfile)
		{
			// get length of file:
			scalerfile.seekg(0, scalerfile.end);
			length = scalerfile.tellg();
			scalerfile.seekg(0, scalerfile.beg);
		}
		cout << "\nGOT THE SIZE =" << length / 350;
		return (length / 350);
	}
}