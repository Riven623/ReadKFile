
#pragma comment(lib,"Shlwapi.lib")
#include "InputFile.h"

using namespace std;
using namespace Eigen;


int main() 
{
	 //hdfReadAnimation("wujiechucar11.h5",157781,51);
	//hdfReadCurve("smallshell144su.h5", 4368, 1001);

	InputFileProject* pInputFile = new InputFileProject;
	InputAllDate* IAD = new InputAllDate;

	IAD= pInputFile->inputFunction("car1127.txt");

	pInputFile->inputMBFunction("BigRenTi.txt", IAD);
 
	//for (auto& it : IAD->InputAllContact[3].MasterContactNode)
	//{

	//	cout << it.second.transpose() << endl;
	//}


	/*for (auto& it : IAD->inputAllRigidBody[17].MeshCoor)
	{
		cout << it.first << endl;
	}*/


	delete IAD;
	delete pInputFile;
	IAD = nullptr;
	pInputFile = nullptr;

	return 0;
	
}



