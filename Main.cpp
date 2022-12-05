
#pragma comment(lib,"Shlwapi.lib")
#include "InputFile.h"

using namespace std;
using namespace Eigen;


int main() 
{
	InputFileProject* pInputFile = new InputFileProject;
	InputAllDate* IAD = new InputAllDate;

	IAD= pInputFile->inputFunction("D:\\Cfile\\OriginalInputFile\\car1127.txt");

	//pInputFile->inputMBFunction("D:\\Cfile\\OriginalInputFile\\RenTi1205.txt", IAD);

	for (auto& it : IAD->InputAllContact[3].MasterContactNode)
	{

		cout << it.second.transpose() << endl;
	}
	

	/*for (auto& it : IAD->inputAllRigidBody[17].MeshCoor)
	{
		cout << it.first << endl;
	}*/

	delete IAD;
	delete pInputFile;


}
