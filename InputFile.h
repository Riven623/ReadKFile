#pragma once
#include "IClude.h"
#include"InputDate.h"


	 /**
	  * @file InputFile.h
	  * @brief 文件读取的头文件。
	  * @details 这个文件包含文件读取所需要的类和函数。
	  * @author ZhaoRui riven_zhao@njust.edu.cn
	  * @date 2023-03-09
	  */

	 /**
		  * @brief 写数据函数
		  *
		  * 将每一行数据判断后写入指定文件。
		  *
		  * @param ObjectiveFile 目标文件。
		  * @param inputLine 数据行。
		  */
inline void getdigit2(ofstream& ObjectiveFile, const string inputLine)
{
	if (' ' == inputLine[0])
	{
		ObjectiveFile << inputLine << endl;
	}
};

/**
	 * @brief 组合文件名类
	 *
	 * @details 将两部分字符串拼接。
	 *
	 */
class FilenameCombine
{
public:
	FilenameCombine(string file1, string file2);

	string m_file1;///<第一部分字符串
	string m_file2;///<第二部分字符串
};

/**
	 * @brief 组合文件名类2
	 *
	 * @details 将三部分字符串拼接。
	 *
	 */
class FilenameCombine2
{
public:
	FilenameCombine2(string file1, string file2, string file3);

	string m_file1;///<第一部分字符串
	string m_file2;///<第二部分字符串
	string m_file3;///<第三部分字符串
};

/**
	 * @brief 获取文件名函数1
	 *
	 * @param Line 文件名。
	 * @return 返回一个字符串为文件名加后缀。
	 */
inline string getFileName(string& Line)
{
	stringstream ss;
	FilenameCombine p1(Line, ".txt ");
	ss << p1.m_file1 << p1.m_file2;
	return ss.str();
}

/**
	 * @brief 获取文件名函数2
	 *
	 * @param Line1 第一个字符串。
	 * @param Line2 第二个字符串。
	 * @return 返回一个字符串为文件名加后缀。
	 */
inline string getFileName2(string& Line1, string& Line2)
{
	stringstream sss;
	FilenameCombine2 p1(Line1, Line2, ".txt ");
	sss << p1.m_file1 << p1.m_file2 << p1.m_file3;
	return sss.str();
}

/**
	 * @brief 获取文件名函数3
	 *
	 * 用于检测文件是否合规的临时文件。
	 * @param Line 文件名。
	 * @return 返回一个字符串为文件名加后缀。
	 */
inline string getFileName3(string& Line)
{
	stringstream ss;
	FilenameCombine p1(Line, "test.txt ");
	ss << p1.m_file1 << p1.m_file2;
	return ss.str();
}

/**
	 * @brief 判断文件是否存在函数
	 *
	 * @param name 文件名。
	 * @return 存在则返回整数1。
	 */
inline int isFileExists(string& name)
{
	ifstream f(name.c_str());
	const int Exist = f.good();
	return Exist;
}

/**
	 * @brief 读文件类
	 *
	 * @details 包含读取车辆模型和假人模型的函数。
	 *
	 */
class InputFileProject
{
public:
	/**
	 * @brief 读车辆模型文件函数
	 *
	 * 读车辆模型文件信息放入InputAllDate。
	 *
	 * @param fileToOpen 模型文件路径。
	 * @return 返回InputAllDate的指针。
	 */
	InputAllDate* inputFunction(const std::string& fileToOpen);
	/**
	 * @brief 读人体模型文件函数
	 *
	 * 读人体模型文件信息放入InputAllDate。
	 *
	 * @param MBfileToOpen 模型文件路径。
	 * @param IADate 存放信息目标。
	 * @return 传回一个整数。
	 */
	int inputMBFunction(const std::string& MBfileToOpen, InputAllDate*IADate);
	//	DynamicCalculation* setTimeParameters();
	streampos fp; ///<文件指针的偏移量,用以判断文件是否为空。
	///构造函数
	InputFileProject(void);
};

/**
	 * @brief 车辆模型信息类
	 *
	 * @details 车辆模型信息类包含读取车辆模型K文件所需要的实体。
	 *
	 */
class VehicleInformation
{
public:
	///构造函数
	VehicleInformation(void);
	ifstream In; ///< 这是第一次总的读取
	string line; ///< 这是总读取每行信息存放的string
	ofstream SlaveNodeFile; ///< 从节点文件
	ofstream EleBFile;///< 梁单元文件
	ofstream EleShFile;///< 壳单元文件
	ofstream SecBeamFile;///< 梁信息文件
	ofstream SecShellFile;///< 壳信息文件
	ofstream SecSolidFile;///< 实体信息文件
	ofstream BoundaryFile;///< 边界文件
	ofstream NodeFile;///< 节点文件
	ofstream ElaFile;///<弹性材料文件
	ofstream PlaFile;///< 塑性材料文件
	ofstream EleSoFile;///< 实体单元文件
	ofstream MasterNodeFile;///< 主节点文件
	ofstream PartFile;///< Part文件
	ofstream ContactFile;///< 接触文件
	ofstream SetFile;///< Set文件
	ofstream NodeVelocityFile;///< 节点速度文件
	ofstream ComputingTimeFile;///< 计算时间文件
	ofstream TimeIncrementFile;///< 时间增量文件
	ofstream RigidWallFile;///< 刚性墙文件
	ofstream HourglassFile;///< 沙漏文件
	ofstream BoundarySetFile;///< 边界Set文件
	ofstream WallSlaveNodeFile;///< 墙体从节点文件
	ofstream LoadNodeFile;///< 节点力文件
	ofstream DefineCurveFile;///< 曲线信息文件
	ofstream LoadBodyZFile;///< Z方向体力文件
	ofstream LoadBodyYFile;///< Y方向体力文件

	string LoadBodyYFileString;///< Y方向体力文件名
	string LoadBodyZFileString;///< Z方向体力文件名
	string DefineCurveFileString;///< 曲线信息文件名
	string LoadNodeFileString;///< 节点力文件名
	string WallSlaveNodeFileString;///< 墙体从节点文件名
	string BoundarySetFileString;///<边界Set文件名
	string ElaFileString;///< 弹性材料文件名
	string PlaFileString;///< 塑性材料文件名
	string ComputingTimeFileString;///< 计算时间文件名
	string TimeIncrementFileString;///< 时间增量文件名
	string NodeFileString;///< 节点文件名
	string PartFileString;///< Part文件名
	string SecSolidFileString;///< 实体信息文件名
	string NodeVelocityFileString;///< 节点速度文件名
	string MasterNodeFileString;///< 主面节点文件名
	string ContactFileString;///< 接触文件名
	string ContactFileString2;///< 完整接触文件名
	string RigidWallFileString2;///< 完整刚性墙文件名
	string EleSoFileString;///< 实体单元文件名
	string SlaveNodeFileString;///< 从节点文件名
	string SetFileString;///< Set文件名
	string BoundaryFileString;///< 边界文件名
	string EleBFileString;///< 梁单元文件名
	string EleShFileString;///< 壳单元文件名
	string SecBeamFileString;///< 梁信息文件名
	string SecShellFileString;///< 壳信息文件名
	string SecShellFileString2;///< 完整壳信息文件名
	string RigidWallFileString;///< 刚性墙文件名
	string HourglassFileString;///< 沙漏文件名

	string AdditionalDigit;



	//FORCE
	ifstream InForce;///< 读取力
	string LineForce;
	ofstream ForceFile;///< 力文件
	ofstream ForceSetNodeFile;///< 力Set文件
	ofstream ForceBOUNDARYFile;///< 力约束文件
	string ForceFileString;///< 力文件名
	string ForceSetNodeFileString;///< 力set文件名
	string ForceBOUNDARYFileString;///< 力约束文件名

	int PanduanForce;


	//RIGIDWALL_PLANAR_FINITE_ID
	ifstream InRigidwall; ///< 读取刚性墙信息
	string LineRigidwall;
	ofstream RigidWallFile2;///< 完整的刚性墙信息文件


	//SecShell
	ifstream InSecShell;///< 读取壳信息
	string LineSecShell;
	ofstream SecShellFile2;///< 完整的壳信息文件

	//Contact
	ifstream InContact;///< 读取接触信息
	string LineContact;
	ofstream ContactFile2;///< 完整的接触文件

	//SegmentSet
	ifstream InSegmentSet;///< 读取SegmentSet信息
	string LineSegmentSet;
	ofstream SegmentSetFile1;///< 完整的SegmentSet信息文件
	ofstream SegmentSetFile2;

	string SetSegment;
	string SegmentSetFile1String;
	string SegmentSetFile2String;

	//SetNode
	string Setnodelist;
	ifstream InSetNode;///< 读取SetNode信息
	string LineSetNode;

	ofstream SetNodeFile1;///< 完整的SetNode信息文件
	ofstream SetNodeFile2;

	string SetNodeFile1String;
	string SetNodeFile2String;

	//文件合法
	string TestPart;///< 判断part文件合法的文件名
	string TestNode;///< 判断节点文件合法的文件名
	string TestEla;///< 判断弹性材料文件合法的文件名
	string TestPla;///< 判断塑性材料文件合法的文件名
	string TestSecShell;///< 判断壳信息文件合法的文件名
	string TestNodeVelocity;///< 判断节点速度文件合法的文件名
	string TestRigidWall;///< 判断刚性墙文件合法的文件名
	string TestEleSh;///< 判断壳单元文件合法的文件名
	string TestEleSo;///< 判断实体单元文件合法的文件名
	string TestSecBeam;///< 判断梁信息文件合法的文件名
	string TestContact;///< 判断接触文件合法的文件名

	ofstream testfile;
};

 /**
	 * @brief 人体模型信息类
	 *
	 * @details 包含读取人体模型文件所需要的实体。
	 *
	 */
class DummyInformation
{
public:
	///构造函数
	DummyInformation(void);
	//人体模型
	ifstream InMB; ///< 这是第一次总的读取
	string LineMB;///< 每一次读取的数据
	string Multibody;

	ofstream RigidBodyFile;///< 刚体文件
	ofstream ColumHingeFile;///< 柱铰文件
	ofstream BallJointFile;///< 球铰文件
	ofstream MBNodeFile;///< 假人节点文件
	ofstream MBContactFile;///< 假人接触文件

	string MBContactFileString;///< 假人接触文件名
	string MBNodeFileString;///< 假人节点文件名
	string RigidBodyFileString;///< 假人刚体文件名
	string ColumHingeFileString;///< 假人柱铰文件名
	string BallJointFileString;///< 假人球铰文件名

	ifstream MBInContact;
	string MBLineContact;
	ofstream MBContactFile2;///< 完整的假人接触文件
	string MBContactFileString2;

	string MBLineSegmentSet;

	ofstream ConnectNodeFile;///< 完整的假人接触节点文件
	string ConnectNodeFileString;

	ifstream InSegmentSet;
	string LineSegmentSet;
	ofstream SegmentSetFile1;///< 完整的假人SegmentSet文件
	ofstream SegmentSetFile2;

	string SetSegment;
	string SegmentSetFile1String;
	string SegmentSetFile2String;

	string Setnodelist;
	ifstream InSetNode;
	string LineSetNode;

	ofstream SetNodeFile1;///< 完整的假人SetNode文件
	ofstream SetNodeFile2;

	string SetNodeFile1String;
	string SetNodeFile2String;
};

///K文件Part类
class KFilePart
{
public:
	///构造函数
	KFilePart(void);
	int Pid;
	int SectionID;
	int Mid;
};
///K文件梁信息类
class sectionbeam
{
public:
	///构造函数
	sectionbeam(void);
	int secidbeam;
	double TS;
	double TT;
};
///K文件壳信息类
class sectionshell
{
public:
	///构造函数
	sectionshell(void);
	int secidshell;
	double T1;
	double T2;
	double T3;
	double T4;
};
///K文件速度类
class Velocity
{
public:
	///构造函数
	Velocity(void);
	int SetType;     // 1: part set ID
					 // 2: part ID
					 // 3: node set ID
	int SetNodeid;
	double XVelocity;
	double YVelocity;
	double ZVelocity;
};
///K文件SetNode类
class SetNode
{
public:
	///构造函数
	SetNode(void);
	int SetType ;
	int SetId ; ///<set 集号
	Matrix<int, Dynamic, Dynamic> SetNodeID;  ///<set 集节点号
};
///K文件SetSegmentNode类
class SetSegmentNode
{
public:
	///构造函数
	SetSegmentNode(void);
	int SetType ;
	int SetSegmentId; ///<SetSegment集号
	Matrix<int, Dynamic, Dynamic> SetSegmentNodeID;  ///<SetSegment集节点号
};
///K文件Z体力类
class LoadBodyZ
{
public:
	///构造函数
	LoadBodyZ(void);
	int LoadBodyZCurveID;
	double LoadCurveScaleFactor;
};
///K文件Y体力类
class LoadBodyY
{
public:
	///构造函数
	LoadBodyY(void);
	int LoadBodyYCurveID;
	double LoadCurveScaleFactor;
};
///K文件X体力类
class LoadBodyX
{
public:
	///构造函数
	LoadBodyX(void);
	int LoadBodyXCurveID;
	double LoadCurveScaleFactor;
};

/**
	* @brief 汇总临时信息类
	*
	* @details 汇总读文件时Part, Section，Velocity，SetNode，SetSegmentNode 等等临时信息。
	*
	*/
class lsmap   
{
public:
	map<int, KFilePart > AllPart;///<所有Part信息
	map<int, sectionbeam>AllSectionbeam;///<所有梁信息
	map<int, sectionshell>AllSectionshell;///<所有壳信息
	map<int, Velocity > AllVelocity;///<所有速度信息
	map<int, SetNode > AllSetNode;///<所有SetNode信息
	map<int, SetSegmentNode > AllSetSegment;///<所有SetSegment信息
	map<int, LoadBodyZ > AllLoadBodyZ;///<所有Z体力信息
	map<int, LoadBodyX > AllLoadBodyX;///<所有X体力信息
	map<int, LoadBodyY > AllLoadBodyY;///<所有Y体力信息
	lsmap(void);
};


//汇总人体模型辅助信息

///假人节点类
class MBNode
{
public:
	///构造函数
	MBNode(void);
	int NodeID;///<节点编号
	Matrix<double, 1, 3> NodeCoordinates;///<坐标（x,y,z）的值
};
///假人SetNode类
class MBSetNode
{
public:
	///构造函数
	MBSetNode(void);
	int SetType;
	int SetId; ///<set 集号
	Matrix<int, Dynamic, Dynamic> SetNodeID;  ///<set 集节点号
};
///假人SetSegmentNode类
class MBSetSegmentNode
{
public:
	///构造函数
	MBSetSegmentNode(void);
	int SetType;
	int SetSegmentId; ///<SetSegment集号
	Matrix<int, Dynamic, Dynamic> SetSegmentNodeID;  ///<SetSegment集节点号
};

/**
	* @brief 汇总假人临时信息类
	*
	* @details 汇总读文件时假人的临时信息。
	*
	*/
class MBlsmap   
{
public:
	map<int, MBNode > AllMBNode;///<所有假人节点信息
	map<int, MBSetNode>AllMBSetNode;///<所有假人SetNode信息
	map<int, MBSetSegmentNode>AllMBSetSegmentNode;///<所有假人SetSegmentNode信息
	MBlsmap(void);
};

/**
 * @brief 删除中间文件函数
 *
 * 将计算过程中产生的中间文件删除。
 *
 * @param filename 文件名。
 */
inline void DeleteProcessFile(string& filename)
{
	if (filename.empty() == false)
	{
		char* c = new char[1000];
		strcpy(c, filename.c_str());
		(void)remove(c);
		delete c;
		c = nullptr;
	}
}

