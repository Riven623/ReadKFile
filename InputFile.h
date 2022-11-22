#pragma once
#include "IClude.h"
#include"InputDate.h"

//写入数据函数(内联)
inline void getdigit3(ofstream& ObjectiveFile, const string inputLine, const int lineID)
{
	if (lineID < inputLine.length())
	{
		if ((' ' == inputLine[0]) && isdigit(inputLine.at(lineID)))
		{
			ObjectiveFile << inputLine << endl;
		}
	}
};

inline void getdigit2(ofstream& ObjectiveFile, const string inputLine)
{
	if (' ' == inputLine[0])
	{
		ObjectiveFile << inputLine << endl;
	}
};

//获取文件名的类
class FilenameCombine
{
public:
	FilenameCombine(string file1, string file2);

	string m_file1;
	string m_file2;
};

class FilenameCombine2
{
public:
	FilenameCombine2(string file1, string file2, string file3);

	string m_file1;
	string m_file2;
	string m_file3;
};

//获取文件名函数(内联)
inline string getFileName(string& Line)
{
	stringstream ss;
	FilenameCombine p1(Line, ".txt ");
	ss << p1.m_file1 << p1.m_file2;
	return ss.str();
}

inline string getFileName2(string& Line1, string& Line2)
{
	stringstream sss;
	FilenameCombine2 p1(Line1, Line2, ".txt ");
	sss << p1.m_file1 << p1.m_file2 << p1.m_file3;
	return sss.str();
}

//判断文件是否存在函数(内联)
inline int isFileExists(string& name)
{
	ifstream f(name.c_str());
	const int Exist = f.good();
	return Exist;
}

//读文件主函数定义类
class InputFileProject
{
public:
	InputFileProject();
	//第一次总的读取
    ifstream In;
    string line;
    ofstream SlaveNodeFile;
    ofstream EleBFile;
    ofstream EleShFile;
    ofstream SecBeamFile;
    ofstream SecShellFile;
    ofstream SecSolidFile;
    ofstream BoundaryFile;
    ofstream NodeFile;
    ofstream ElaFile;
    ofstream PlaFile;
    ofstream EleSoFile;
    ofstream MasterNodeFile;
    ofstream PartFile;
    ofstream ContactFile;
    ofstream SetFile;
    ofstream NodeVelocityFile;
    ofstream ComputingTimeFile;
    ofstream TimeIncrementFile;
    ofstream RigidWallFile;
    ofstream HourglassFile;
    ofstream BoundarySetFile;
    ofstream WallSlaveNodeFile;
    ofstream LoadNodeFile;
    ofstream DefineCurveFile;
	ofstream LoadBodyZFile;
	ofstream LoadBodyYFile;

	string LoadBodyYFileString;
	string LoadBodyZFileString;
    string DefineCurveFileString;
    string LoadNodeFileString;
    string WallSlaveNodeFileString;
    string BoundarySetFileString;
    string ElaFileString;
    string PlaFileString;
    string ComputingTimeFileString;
    string TimeIncrementFileString;
    string NodeFileString;
    string PartFileString;
    string SecSolidFileString;
    string NodeVelocityFileString;
    string MasterNodeFileString;
    string ContactFileString;
    string ContactFileString2;
	string RigidWallFileString2;


    string EleSoFileString;
    string SlaveNodeFileString;
    string SetFileString;
    string BoundaryFileString;
    string EleBFileString;
    string EleShFileString;
    string SecBeamFileString;
    string SecShellFileString;
    string SecShellFileString2;
    string RigidWallFileString;
    string HourglassFileString;

    string AdditionalDigit;

    int SetNodeId1 ;
    int SetNodeId2 ;
    int SetNodeId3 ;
    int SetNodeId4 ;
	int SetNodeId5;
	int SetNodeId6;
	int SetNodeId7;
	int SetNodeId8;
	int SetNodeId9;
	int SetNodeId10 ;

    int SegmentSetId1 ;
    int SegmentSetId2 ;
	int SegmentSetId3 ;
	int SegmentSetId4 ;
	int SegmentSetId5 ;
	int SegmentSetId6 ;

    InputAllDate* inputFunction(const std::string& fileToOpen);

	//RIGIDWALL_PLANAR_FINITE_ID
	ifstream InRigidwall;
	string LineRigidwall;
	ofstream RigidWallFile2;


	//SecShell
	ifstream InSecShell;
	string LineSecShell;
	ofstream SecShellFile2;

	//Contact
	ifstream InContact;
	string LineContact;
	ofstream ContactFile2;

    //SegmentSet
	ifstream InSegmentSet;
    string LineSegmentSet;
	ofstream SegmentSetFile1;
	ofstream SegmentSetFile2;
	ofstream SegmentSetFile3;
	ofstream SegmentSetFile4;
	ofstream SegmentSetFile5;
	ofstream SegmentSetFile6;

	string SetSegment;
	string SegmentSetFile1String;
	string SegmentSetFile2String;
	string SegmentSetFile3String;
	string SegmentSetFile4String;
	string SegmentSetFile5String;
	string SegmentSetFile6String;

    //SetNode
	string Setnodelist;
	ifstream InSetNode;
	string LineSetNode;

	ofstream SetNodeFile1;
	ofstream SetNodeFile2;
	ofstream SetNodeFile3;
	ofstream SetNodeFile4;
	ofstream SetNodeFile5;
	ofstream SetNodeFile6;
	ofstream SetNodeFile7;
	ofstream SetNodeFile8;
	ofstream SetNodeFile9;
	ofstream SetNodeFile10;

	string SetNodeFile1String;
	string SetNodeFile2String;
	string SetNodeFile3String;
	string SetNodeFile4String;
	string SetNodeFile5String;
	string SetNodeFile6String;
	string SetNodeFile7String;
	string SetNodeFile8String;
	string SetNodeFile9String;
	string SetNodeFile10String;

    int PanduanSetNode ;
	int PanduanSegmentSetNode ;


};

//汇总Part, Section，Velocity，SetNode，SetSegmentNode 信息
class Part
{
public:
	Part();
	int Pid;
	int SectionID;
	int Mid;
};
class sectionbeam
{
public:
	sectionbeam();
	int secidbeam;
	double TS;
	double TT;
};
class sectionshell
{
public:
	sectionshell();
	int secidshell;
	double T1;
	double T2;
	double T3;
	double T4;
};
class Velocity
{
public:
	Velocity();
	int SetType;     // 1: part set ID
					 // 2: part ID
					 // 3: node set ID
	int SetNodeid;
	double XVelocity;
	double YVelocity;
	double ZVelocity;
};
class SetNode
{
public:
	SetNode();
	int SetType ;
	int SetId ; //set 集号
	Matrix<int, Dynamic, Dynamic> SetNodeID;  //set 集节点号
};
class SetSegmentNode
{
public:
	SetSegmentNode();
	int SetType ;
	int SetSegmentId; //SetSegment集号
	Matrix<int, Dynamic, Dynamic> SetSegmentNodeID;  //SetSegment集节点号
};
class LoadBodyZ
{
public:
	LoadBodyZ();
	int LoadBodyZCurveID;
	double LoadCurveScaleFactor;
};
class LoadBodyY
{
public:
	LoadBodyY();
	int LoadBodyYCurveID;
	double LoadCurveScaleFactor;
};
class LoadBodyX
{
public:
	LoadBodyX();
	int LoadBodyXCurveID;
	double LoadCurveScaleFactor;
};
class lsmap   //所有临时信息汇总的类
{
public:
	map<int, Part > AllPart;
	map<int, sectionbeam>AllSectionbeam;
	map<int, sectionshell>AllSectionshell;
	map<int, Velocity > AllVelocity;
	map<int, SetNode > AllSetNode;
	map<int, SetSegmentNode > AllSetSegment;
	map<int, LoadBodyZ > AllLoadBodyZ;
	map<int, LoadBodyX > AllLoadBodyX;
	map<int, LoadBodyY > AllLoadBodyY;
};
