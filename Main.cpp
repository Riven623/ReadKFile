
#pragma comment(lib,"Shlwapi.lib")
#include "InputFile.h"

using namespace std;
using namespace Eigen;


int main() 
{
	InputFileProject* pInputFile = new InputFileProject;
	InputAllDate* IAD = new InputAllDate;

	IAD= pInputFile->inputFunction("D:\\Cfile\\OriginalInputFile\\1234.k");

	//cout << IAD->InputAllContact[3].MasterContactNode[2] << endl;



	/*auto pr = (*IAD).InputAllContact[4].MasterContactNode.find(2);
	if (pr != std::end((*IAD).InputAllContact[4].MasterContactNode))
	{
	std:cout << pr->first << " is " << endl << pr->second << endl;
	}*/
}
