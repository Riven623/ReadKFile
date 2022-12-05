#pragma once
#include "IClude.h"
#include"InputDate.h"


//void txt_to_vectordouble(vector<vector<double>>& res, const std::string pathname)
//{
//	ifstream infile;
//	infile.open(pathname);   //将文件流对象与文件连接起来 
//	//assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 
//	vector<double> suanz;
//	string s;
//	while (getline(infile, s)) {
//		istringstream is(s); //将读出的一行转成数据流进行操作
//		double d;
//		while (!is.eof()) {
//			is >> d;
//			suanz.push_back(d);
//		}
//		res.push_back(suanz);
//		suanz.clear();
//		s.clear();
//	}
//	infile.close();             //关闭文件输入流 
//};

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
	int SetNodeId10;
	int SetNodeId11;
	int SetNodeId12;
	int SetNodeId13;
	int SetNodeId14;
	int SetNodeId15;
	int SetNodeId16;
	int SetNodeId17;
	int SetNodeId18;
	int SetNodeId19;
	int SetNodeId20;
	int SetNodeId21;
	int SetNodeId22;
	int SetNodeId23;
	int SetNodeId24;
	int SetNodeId25;
	int SetNodeId26;
	int SetNodeId27;
	int SetNodeId28;
	int SetNodeId29;
	int SetNodeId30;

    int SegmentSetId1 ;
    int SegmentSetId2 ;
	int SegmentSetId3 ;
	int SegmentSetId4 ;
	int SegmentSetId5 ;
	int SegmentSetId6 ;

    
	
	
	
	
	InputAllDate* inputFunction(const std::string& fileToOpen);

	int inputMBFunction(const std::string& MBfileToOpen, InputAllDate*IADate);

	

	//FORCE
	ifstream InForce;
	string LineForce;
	ofstream ForceFile;
	ofstream ForceSetNodeFile;
	ofstream ForceBOUNDARYFile;
	string ForceFileString;
	string ForceSetNodeFileString;
	string ForceBOUNDARYFileString;

	int PanduanForce;


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
	ofstream SetNodeFile11;
	ofstream SetNodeFile12;
	ofstream SetNodeFile13;
	ofstream SetNodeFile14;
	ofstream SetNodeFile15;
	ofstream SetNodeFile16;
	ofstream SetNodeFile17;
	ofstream SetNodeFile18;
	ofstream SetNodeFile19;
	ofstream SetNodeFile20;
	ofstream SetNodeFile21;
	ofstream SetNodeFile22;
	ofstream SetNodeFile23;
	ofstream SetNodeFile24;
	ofstream SetNodeFile25;
	ofstream SetNodeFile26;
	ofstream SetNodeFile27;
	ofstream SetNodeFile28;
	ofstream SetNodeFile29;
	ofstream SetNodeFile30;
	ofstream SetNodeFile31;


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
	string SetNodeFile11String;
	string SetNodeFile12String;
	string SetNodeFile13String;
	string SetNodeFile14String;
	string SetNodeFile15String;
	string SetNodeFile16String;
	string SetNodeFile17String;
	string SetNodeFile18String;
	string SetNodeFile19String;
	string SetNodeFile20String;
	string SetNodeFile21String;
	string SetNodeFile22String;
	string SetNodeFile23String;
	string SetNodeFile24String;
	string SetNodeFile25String;
	string SetNodeFile26String;
	string SetNodeFile27String;
	string SetNodeFile28String;
	string SetNodeFile29String;
	string SetNodeFile30String;

    int PanduanSetNode ;
	int PanduanSegmentSetNode ;
	int PanduanSecondpart;

	//人体模型
	ifstream InMB;
	string LineMB;
	string Multibody = "MB";

	ofstream RigidBodyFile;
	ofstream ColumHingeFile;
	ofstream BallJointFile;
	ofstream MBNodeFile;
	ofstream MBContactFile;

	string MBContactFileString;
	string MBNodeFileString;
	string RigidBodyFileString;
	string ColumHingeFileString;
	string BallJointFileString;

	//MBContact
	ifstream MBInContact;
	string MBLineContact;
	ofstream MBContactFile2;
	string MBContactFileString2;

	string MBLineSegmentSet;

	//ConnectNode
	ofstream ConnectNodeFile;
	string ConnectNodeFileString;
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

//汇总人体模型辅助信息
class MBNode
{
public:
	MBNode();
	int NodeID;//节点编号
	Matrix<double, 1, 3> NodeCoordinates;//坐标（x,y,z）的值
};
class MBSetNode
{
public:
	MBSetNode();
	int SetType;
	int SetId; //set 集号
	Matrix<int, Dynamic, Dynamic> SetNodeID;  //set 集节点号
};
class MBSetSegmentNode
{
public:
	MBSetSegmentNode();
	int SetType;
	int SetSegmentId; //SetSegment集号
	Matrix<int, Dynamic, Dynamic> SetSegmentNodeID;  //SetSegment集节点号
};

class MBlsmap   //所有临时信息汇总的类
{
public:
	map<int, MBNode > AllMBNode;
	map<int, MBSetNode>AllMBSetNode;
	map<int, MBSetSegmentNode>AllMBSetSegmentNode;
};
