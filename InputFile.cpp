#include "InputFile.h"
#include"csv_MatrixXd_IO.h"
using namespace Eigen;
using namespace std;

//读人体模型文件函数
int InputFileProject::inputMBFunction(const std::string& MBfileToOpen, InputAllDate* IADate)
{

	 InMB.open(MBfileToOpen);
	while (getline(InMB, LineMB))
	{
		//刚体
		if (LineMB == "*RigidBody")
		{
			ColumHingeFile.close();
			MBNodeFile.close();
			BallJointFile.close();
			MBContactFile.close();
			LineMB.erase(0, 1);
			RigidBodyFileString = getFileName(LineMB);
			RigidBodyFile.open(getFileName(LineMB));
		}
		if (RigidBodyFile.is_open())
		{
			getdigit2(RigidBodyFile, LineMB);
		};
		//柱铰
		if (LineMB == "*ColumHinge")
		{
			RigidBodyFile.close();
			BallJointFile.close();
			MBNodeFile.close();
			MBContactFile.close();
			LineMB.erase(0, 1);
			ColumHingeFileString = getFileName(LineMB);
			ColumHingeFile.open(getFileName(LineMB));
		}
		if (ColumHingeFile.is_open())
		{
			getdigit2(ColumHingeFile, LineMB);
		};
		//球铰
		if (LineMB == "*BallJoint")
		{
			ColumHingeFile.close();
			RigidBodyFile.close();
			MBNodeFile.close();
			MBContactFile.close();
			LineMB.erase(0, 1);
			BallJointFileString = getFileName(LineMB);
			BallJointFile.open(getFileName(LineMB));
		}
		if (BallJointFile.is_open())
		{
			getdigit2(BallJointFile, LineMB);
		};

		//NODE
		if (LineMB == "*NODE")
		{
			ColumHingeFile.close();
			RigidBodyFile.close();
			BallJointFile.close();
			MBContactFile.close();
			LineMB.erase(0, 1);
			MBNodeFileString = getFileName2(Multibody,LineMB);
			MBNodeFile.open(MBNodeFileString);
		}
		if (MBNodeFile.is_open())
		{
			getdigit2(MBNodeFile, LineMB);
		};

		//接触
		if (LineMB == "*CONTACT_NODES_TO_SURFACE_ID")
		{
			ColumHingeFile.close();
			RigidBodyFile.close();
			BallJointFile.close();
			MBNodeFile.close();
			LineMB.erase(0, 1);
			MBContactFileString = "MBContact.txt";
			MBContactFileString2 = "MBContactTemp.txt";
			MBContactFile.open(MBContactFileString2);
			MBContactFile.clear();
			MBContactFile << endl;
		}
		if (MBContactFile.is_open())
		{
			if (' ' == LineMB[0])
			{
				MBContactFile << LineMB << " ";
			}
		}

		if (LineMB == "*SET_NODE_LIST")
		{
			ColumHingeFile.close();
			RigidBodyFile.close();
			BallJointFile.close();
			MBNodeFile.close();
			MBContactFile.close();
		}
		if (LineMB == "*SET_SEGMENT")
		{
			ColumHingeFile.close();
			RigidBodyFile.close();
			BallJointFile.close();
			MBNodeFile.close();
			MBContactFile.close();
		}
		if (LineMB == "*END")
		{
			ColumHingeFile.close();
			RigidBodyFile.close();
			BallJointFile.close();
			MBNodeFile.close();
			MBContactFile.close();
		}
		if ("*ConnectNode" == LineMB )
		{
			LineMB = LineMB.erase(0, 1);
			ConnectNodeFileString = getFileName(LineMB);
			ConnectNodeFile.open(ConnectNodeFileString);
		}
		if (ConnectNodeFile.is_open())
		{
			getdigit2(ConnectNodeFile, LineMB);
		}
		if (LineMB == "*END2")
		{
			ConnectNodeFile.close();
		}
	}
	InMB.close();

	//Contact 文件
	MBInContact.open(MBContactFileString2);
	MBContactFile2.open(MBContactFileString);
	while (getline(MBInContact, MBLineContact))
	{
		if (MBContactFile2.is_open())
		{
			if (' ' == MBLineContact[0])
			{
				MBContactFile2 << MBLineContact << endl;
			}
		}
	}
	MBContactFile2.close();
	MBInContact.close();

	//SegmentSet 文件
	InSegmentSet.open(MBfileToOpen);
	while (getline(InSegmentSet, MBLineSegmentSet))
	{
		//主面节点
		if ("*SET_SEGMENT" == MBLineSegmentSet)
		{
			SetSegment = ("MB")+ (MBLineSegmentSet.erase(0, 1));
			PanduanSegmentSetNode = 1;

		}
		if ((1 == PanduanSegmentSetNode) && ("         1                                        MECH      " == MBLineSegmentSet))
		{
			MBLineSegmentSet = MBLineSegmentSet.erase(0, 9);
			MBLineSegmentSet = MBLineSegmentSet.erase(1, 50);
			SegmentSetId1 = MBLineSegmentSet.at(0) - '0';
			SegmentSetFile1String = getFileName2(SetSegment, MBLineSegmentSet);
			SegmentSetFile1.open(SegmentSetFile1String);
		}
		if (SegmentSetFile1.is_open())
		{
			getdigit3(SegmentSetFile1, MBLineSegmentSet, 19);
		}
		if ((1 == PanduanSegmentSetNode) && ("         2                                        MECH      " == MBLineSegmentSet))
		{
			SegmentSetFile1.close();
			MBLineSegmentSet = MBLineSegmentSet.erase(0, 9);
			MBLineSegmentSet = MBLineSegmentSet.erase(1, 50);
			SegmentSetId2 = MBLineSegmentSet.at(0) - '0';
			SegmentSetFile2String = getFileName2(SetSegment, MBLineSegmentSet);
			SegmentSetFile2.open(SegmentSetFile2String);
		}
		if (SegmentSetFile2.is_open())
		{
			getdigit3(SegmentSetFile2, MBLineSegmentSet, 19);
		}
		if ((1 == PanduanSegmentSetNode) && ("         3                                        MECH      " == MBLineSegmentSet))
		{
			SegmentSetFile1.close();
			SegmentSetFile2.close();

			MBLineSegmentSet = MBLineSegmentSet.erase(0, 9);
			MBLineSegmentSet = MBLineSegmentSet.erase(1, 50);
			SegmentSetId3 = MBLineSegmentSet.at(0) - '0';
			SegmentSetFile3String = getFileName2(SetSegment, MBLineSegmentSet);
			SegmentSetFile3.open(SegmentSetFile3String);
		}
		if (SegmentSetFile3.is_open())
		{
			getdigit3(SegmentSetFile3, MBLineSegmentSet, 19);
		}
		if ((1 == PanduanSegmentSetNode) && ("         4                                        MECH      " == MBLineSegmentSet))
		{
			SegmentSetFile1.close();
			SegmentSetFile3.close();
			SegmentSetFile2.close();
			MBLineSegmentSet = MBLineSegmentSet.erase(0, 9);
			MBLineSegmentSet = MBLineSegmentSet.erase(1, 50);
			SegmentSetId4 = MBLineSegmentSet.at(0) - '0';
			SegmentSetFile4String = getFileName2(SetSegment, MBLineSegmentSet);
			SegmentSetFile4.open(SegmentSetFile4String);
		}
		if (SegmentSetFile4.is_open())
		{
			getdigit3(SegmentSetFile4, MBLineSegmentSet, 19);
		}
		if ((1 == PanduanSegmentSetNode) && ("         5                                        MECH      " == MBLineSegmentSet))
		{
			SegmentSetFile1.close();
			SegmentSetFile3.close();
			SegmentSetFile2.close();
			SegmentSetFile4.close();
			MBLineSegmentSet = MBLineSegmentSet.erase(0, 9);
			MBLineSegmentSet = MBLineSegmentSet.erase(1, 50);
			SegmentSetId5 = MBLineSegmentSet.at(0) - '0';
			SegmentSetFile5String = getFileName2(SetSegment, MBLineSegmentSet);
			SegmentSetFile5.open(SegmentSetFile5String);
		}
		if (SegmentSetFile5.is_open())
		{
			getdigit3(SegmentSetFile5, MBLineSegmentSet, 19);
		}
		if ((1 == PanduanSegmentSetNode) && ("         6                                        MECH      " == MBLineSegmentSet))
		{
			SegmentSetFile1.close();
			SegmentSetFile3.close();
			SegmentSetFile2.close();
			SegmentSetFile4.close();
			SegmentSetFile5.close();
			MBLineSegmentSet = MBLineSegmentSet.erase(0, 9);
			MBLineSegmentSet = MBLineSegmentSet.erase(1, 50);
			SegmentSetId6 = MBLineSegmentSet.at(0) - '0';
			SegmentSetFile6String = getFileName2(SetSegment, MBLineSegmentSet);
			SegmentSetFile6.open(SegmentSetFile6String);
		}
		if (SegmentSetFile6.is_open())
		{
			getdigit3(SegmentSetFile6, MBLineSegmentSet, 19);
		}
		if ("*END" == MBLineSegmentSet)
		{
			SegmentSetFile1.close();
			SegmentSetFile2.close();
			SegmentSetFile3.close();
			SegmentSetFile4.close();
			SegmentSetFile6.close();
			SegmentSetFile5.close();
			
			//MBLineSegmentSet = nullptr;
			PanduanSegmentSetNode = 0;
		}
	}
	InSegmentSet.close();

	//SetNode
	InSetNode.open(MBfileToOpen);
	while (getline(InSetNode, LineSetNode))
	{
		if ("*SET_NODE_LIST" == LineSetNode)
		{
			Setnodelist = ("MB")+(LineSetNode.erase(0, 1));
			PanduanSetNode = 1;
		}
		if ((1 == PanduanSetNode) && ("         1                                        MECH      " == LineSetNode))
		{
			SetNodeFile2.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile10.close();
			SetNodeFile11.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 9);
			LineSetNode = LineSetNode.erase(1, 50);
			SetNodeId1 = LineSetNode.at(0) - '0';
			SetNodeFile1String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile1.open(SetNodeFile1String);
			continue;
		}
		if (SetNodeFile1.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile1 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("         2                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile10.close();
			SetNodeFile11.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 9);
			LineSetNode = LineSetNode.erase(1, 50);
			SetNodeId2 = LineSetNode.at(0) - '0';
			SetNodeFile2String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile2.open(SetNodeFile2String);
			continue;
		}
		if (SetNodeFile2.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile2 << LineSetNode << " ";
			}
		}

		if ((1 == PanduanSetNode) && ("         3                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile2.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile10.close();
			SetNodeFile11.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 9);
			LineSetNode = LineSetNode.erase(1, 50);
			SetNodeId3 = LineSetNode.at(0) - '0';
			SetNodeFile3String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile3.open(SetNodeFile3String);
			continue;
		}
		if (SetNodeFile3.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile3 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("         4                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile2.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile10.close();
			SetNodeFile11.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 9);
			LineSetNode = LineSetNode.erase(1, 50);
			SetNodeId4 = LineSetNode.at(0) - '0';
			SetNodeFile4String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile4.open(SetNodeFile4String);
			continue;
		}
		if (SetNodeFile4.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile4 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("         5                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile2.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile10.close();
			SetNodeFile11.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 9);
			LineSetNode = LineSetNode.erase(1, 50);
			SetNodeId5 = LineSetNode.at(0) - '0';
			SetNodeFile5String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile5.open(SetNodeFile5String);
			continue;
		}
		if (SetNodeFile5.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile5 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("         6                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile2.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile10.close();
			SetNodeFile11.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 9);
			LineSetNode = LineSetNode.erase(1, 50);
			SetNodeId6 = LineSetNode.at(0) - '0';
			SetNodeFile6String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile6.open(SetNodeFile6String);
			continue;
		}
		if (SetNodeFile6.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (LineSetNode[0] == ' ')
			{
				SetNodeFile6 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("         7                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile2.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile10.close();
			SetNodeFile11.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 9);
			LineSetNode = LineSetNode.erase(1, 50);
			SetNodeId7 = LineSetNode.at(0) - '0';
			SetNodeFile7String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile7.open(SetNodeFile7String);
			continue;
		}
		if (SetNodeFile7.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (LineSetNode[0] == ' ')
			{
				SetNodeFile7 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("         8                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile2.close();
			SetNodeFile9.close();
			SetNodeFile10.close();
			SetNodeFile11.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 9);
			LineSetNode = LineSetNode.erase(1, 50);
			SetNodeId8 = LineSetNode.at(0) - '0';
			SetNodeFile8String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile8.open(SetNodeFile8String);
			continue;
		}
		if (SetNodeFile8.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile8 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("         9                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile11.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 9);
			LineSetNode = LineSetNode.erase(1, 50);
			SetNodeId9 = LineSetNode.at(0) - '0';
			SetNodeFile9String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile9.open(SetNodeFile9String);
			continue;
		}
		if (SetNodeFile9.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile9 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        10                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile11.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId10 = 10;
			SetNodeFile10String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile10.open(SetNodeFile10String);
			continue;
		}
		if (SetNodeFile10.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile10 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        11                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId11 = 11;
			SetNodeFile11String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile11.open(SetNodeFile11String);
			continue;
		}
		if (SetNodeFile11.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile11 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        12                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile11.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);

			SetNodeId12 = 12;
			SetNodeFile12String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile12.open(SetNodeFile12String);
			continue;
		}
		if (SetNodeFile12.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile12 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        13                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile11.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId13 = 13;
			SetNodeFile13String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile13.open(SetNodeFile13String);
			continue;
		}
		if (SetNodeFile13.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile13 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        14                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile11.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId14 = 14;
			SetNodeFile14String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile14.open(SetNodeFile14String);
			continue;
		}
		if (SetNodeFile14.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile14 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        15                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile11.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId15 = 15;
			SetNodeFile15String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile15.open(SetNodeFile15String);
			continue;
		}
		if (SetNodeFile15.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile15 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        16                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile11.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId16 = 16;
			SetNodeFile16String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile16.open(SetNodeFile16String);
			continue;
		}
		if (SetNodeFile16.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile16 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        17                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile11.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId17 = 17;
			SetNodeFile17String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile17.open(SetNodeFile17String);
			continue;
		}
		if (SetNodeFile17.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile17 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        18                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile11.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId18 = 18;
			SetNodeFile18String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile18.open(SetNodeFile18String);
			continue;
		}
		if (SetNodeFile18.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile18 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        19                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile11.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId19 = 19;
			SetNodeFile19String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile19.open(SetNodeFile19String);
			continue;
		}
		if (SetNodeFile19.is_open() && (LineSetNode.find("MECH")== string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile19 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        20                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile11.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId20 = 20;
			SetNodeFile20String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile20.open(SetNodeFile20String);
			continue;
		}
		if (SetNodeFile20.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile20 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        21                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile11.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId21 = 21;
			SetNodeFile21String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile21.open(SetNodeFile21String);
			continue;
		}
		if (SetNodeFile21.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile21 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        22                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile11.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId22 = 22;
			SetNodeFile22String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile22.open(SetNodeFile22String);
			continue;
		}
		if (SetNodeFile22.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile22 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        23                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile11.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId23 = 23;
			SetNodeFile23String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile23.open(SetNodeFile23String);
			continue;
		}
		if (SetNodeFile23.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile23 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        24                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile11.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId24 = 24;
			SetNodeFile24String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile24.open(SetNodeFile24String);
			continue;
		}
		if (SetNodeFile24.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile24 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        25                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile11.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId25 = 25;
			SetNodeFile25String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile25.open(SetNodeFile25String);
			continue;
		}
		if (SetNodeFile25.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile25 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        26                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile11.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId26 = 26;
			SetNodeFile26String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile26.open(SetNodeFile26String);
			continue;
		}
		if (SetNodeFile26.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile26 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        27                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile11.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId27 = 27;
			SetNodeFile27String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile27.open(SetNodeFile27String);
			continue;
		}
		if (SetNodeFile27.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile27 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        28                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile11.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId28 = 28;
			SetNodeFile28String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile28.open(SetNodeFile28String);
			continue;
		}
		if (SetNodeFile28.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile28 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        29                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile11.close();
			SetNodeFile30.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId29 = 29;
			SetNodeFile29String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile29.open(SetNodeFile29String);
			continue;
		}
		if (SetNodeFile29.is_open() && (LineSetNode.find("MECH") == string::npos))
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile29 << LineSetNode << " ";
			}
		}
		if ((1 == PanduanSetNode) && ("        30                                        MECH      " == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile2.close();
			SetNodeFile10.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile11.close();
			LineSetNode = LineSetNode.erase(0, 8);
			LineSetNode = LineSetNode.erase(2, 50);
			SetNodeId30 = 30;
			SetNodeFile30String = getFileName2(Setnodelist, LineSetNode);
			SetNodeFile30.open(SetNodeFile30String);
			continue;
		}
		if (SetNodeFile30.is_open())
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile30 << LineSetNode << " ";
			}
		}

		if (("*END" == LineSetNode) || ("*DEFINE_CURVE" == LineSetNode) || ("*BOUNDARY_SPC_NODE" == LineSetNode) || ("*SET_PART_LIST" == LineSetNode) || ("*CONTACT_NODES_TO_SURFACE_ID" == LineSetNode))
		{
			SetNodeFile1.close();
			SetNodeFile3.close();
			SetNodeFile4.close();
			SetNodeFile5.close();
			SetNodeFile6.close();
			SetNodeFile7.close();
			SetNodeFile8.close();
			SetNodeFile9.close();
			SetNodeFile10.close();
			SetNodeFile11.close();
			SetNodeFile12.close();
			SetNodeFile13.close();
			SetNodeFile14.close();
			SetNodeFile15.close();
			SetNodeFile16.close();
			SetNodeFile17.close();
			SetNodeFile18.close();
			SetNodeFile19.close();
			SetNodeFile20.close();
			SetNodeFile21.close();
			SetNodeFile22.close();
			SetNodeFile23.close();
			SetNodeFile24.close();
			SetNodeFile25.close();
			SetNodeFile26.close();
			SetNodeFile27.close();
			SetNodeFile28.close();
			SetNodeFile29.close();
			SetNodeFile30.close();
			SetNodeFile2.close();
			//LineSetNode = nullptr;
			PanduanSetNode = 0;
		}
	}
	InSetNode.close();


	///分割结束
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	MBlsmap* mbls = new MBlsmap;

	//NODE
	if (1 == isFileExists(MBNodeFileString))
	{
		Matrix<int, Dynamic, Dynamic>MBNode1 = LinearMSTMMSolver::openDataInt(MBNodeFileString);
		Matrix<double, Dynamic, Dynamic>MBNode2 = LinearMSTMMSolver::openData(MBNodeFileString);
		MBNode* pMBNode = new MBNode;
		for (int i = 0; i < MBNode1.rows(); i++)
		{
			pMBNode->NodeID = MBNode1(i,0);
			pMBNode->NodeCoordinates = MBNode2.row(i).rightCols(3);
			(void)mbls->AllMBNode.insert(make_pair(pMBNode->NodeID, (*pMBNode)));
		};
		delete pMBNode;
		pMBNode = nullptr;
	};

	MBSetNode* pMBSetNode = new MBSetNode;
	//SET集信息
	if (1 == isFileExists(SetNodeFile1String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode1 = LinearMSTMMSolver::openDataInt(SetNodeFile1String);
		pMBSetNode->SetId = SetNodeId1;
		pMBSetNode->SetNodeID = SetNode1;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile2String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode2 = LinearMSTMMSolver::openDataInt(SetNodeFile2String);
		pMBSetNode->SetId = SetNodeId2;
		pMBSetNode->SetNodeID = SetNode2;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile3String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode3 = LinearMSTMMSolver::openDataInt(SetNodeFile3String);
		pMBSetNode->SetId = SetNodeId3;
		pMBSetNode->SetNodeID = SetNode3;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile4String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode4 = LinearMSTMMSolver::openDataInt(SetNodeFile4String);
		pMBSetNode->SetId = SetNodeId4;
		pMBSetNode->SetNodeID = SetNode4;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile5String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode5 = LinearMSTMMSolver::openDataInt(SetNodeFile5String);
		pMBSetNode->SetId = SetNodeId5;
		pMBSetNode->SetNodeID = SetNode5;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile6String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode6 = LinearMSTMMSolver::openDataInt(SetNodeFile6String);
		pMBSetNode->SetId = SetNodeId6;
		pMBSetNode->SetNodeID = SetNode6;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile7String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode7 = LinearMSTMMSolver::openDataInt(SetNodeFile7String);
		pMBSetNode->SetId = SetNodeId7;
		pMBSetNode->SetNodeID = SetNode7;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile8String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode8 = LinearMSTMMSolver::openDataInt(SetNodeFile8String);
		pMBSetNode->SetId = SetNodeId8;
		pMBSetNode->SetNodeID = SetNode8;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile9String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode9 = LinearMSTMMSolver::openDataInt(SetNodeFile9String);
		pMBSetNode->SetId = SetNodeId9;
		pMBSetNode->SetNodeID = SetNode9;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile10String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode10 = LinearMSTMMSolver::openDataInt(SetNodeFile10String);
		pMBSetNode->SetId = SetNodeId10;
		pMBSetNode->SetNodeID = SetNode10;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile11String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode11 = LinearMSTMMSolver::openDataInt(SetNodeFile11String);
		pMBSetNode->SetId = SetNodeId11;
		pMBSetNode->SetNodeID = SetNode11;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile12String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode12 = LinearMSTMMSolver::openDataInt(SetNodeFile12String);
		pMBSetNode->SetId = SetNodeId12;
		pMBSetNode->SetNodeID = SetNode12;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile13String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode13= LinearMSTMMSolver::openDataInt(SetNodeFile13String);
		pMBSetNode->SetId = SetNodeId13;
		pMBSetNode->SetNodeID = SetNode13;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile14String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode14 = LinearMSTMMSolver::openDataInt(SetNodeFile14String);
		pMBSetNode->SetId = SetNodeId14;
		pMBSetNode->SetNodeID = SetNode14;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile15String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode15= LinearMSTMMSolver::openDataInt(SetNodeFile15String);
		pMBSetNode->SetId = SetNodeId15;
		pMBSetNode->SetNodeID = SetNode15;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile16String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode16 = LinearMSTMMSolver::openDataInt(SetNodeFile16String);
		pMBSetNode->SetId = SetNodeId16;
		pMBSetNode->SetNodeID = SetNode16;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile17String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode17 = LinearMSTMMSolver::openDataInt(SetNodeFile17String);
		pMBSetNode->SetId = SetNodeId17;
		pMBSetNode->SetNodeID = SetNode17;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile18String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode18 = LinearMSTMMSolver::openDataInt(SetNodeFile18String);
		pMBSetNode->SetId = SetNodeId18;
		pMBSetNode->SetNodeID = SetNode18;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile19String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode19 = LinearMSTMMSolver::openDataInt(SetNodeFile19String);
		pMBSetNode->SetId = SetNodeId19;
		pMBSetNode->SetNodeID = SetNode19;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile20String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode20 = LinearMSTMMSolver::openDataInt(SetNodeFile20String);
		pMBSetNode->SetId = SetNodeId20;
		pMBSetNode->SetNodeID = SetNode20;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile21String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode21 = LinearMSTMMSolver::openDataInt(SetNodeFile21String);
		pMBSetNode->SetId = SetNodeId21;
		pMBSetNode->SetNodeID = SetNode21;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile22String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode22 = LinearMSTMMSolver::openDataInt(SetNodeFile22String);
		pMBSetNode->SetId = SetNodeId22;
		pMBSetNode->SetNodeID = SetNode22;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile23String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode23 = LinearMSTMMSolver::openDataInt(SetNodeFile23String);
		pMBSetNode->SetId = SetNodeId23;
		pMBSetNode->SetNodeID = SetNode23;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile24String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode24 = LinearMSTMMSolver::openDataInt(SetNodeFile24String);
		pMBSetNode->SetId = SetNodeId24;
		pMBSetNode->SetNodeID = SetNode24;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile25String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode25= LinearMSTMMSolver::openDataInt(SetNodeFile25String);
		pMBSetNode->SetId = SetNodeId25;
		pMBSetNode->SetNodeID = SetNode25;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile26String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode26 = LinearMSTMMSolver::openDataInt(SetNodeFile26String);
		pMBSetNode->SetId = SetNodeId26;
		pMBSetNode->SetNodeID = SetNode26;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile27String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode27 = LinearMSTMMSolver::openDataInt(SetNodeFile27String);
		pMBSetNode->SetId = SetNodeId27;
		pMBSetNode->SetNodeID = SetNode27;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile28String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode28 = LinearMSTMMSolver::openDataInt(SetNodeFile28String);
		pMBSetNode->SetId = SetNodeId28;
		pMBSetNode->SetNodeID = SetNode28;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile29String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode29 = LinearMSTMMSolver::openDataInt(SetNodeFile29String);
		pMBSetNode->SetId = SetNodeId29;
		pMBSetNode->SetNodeID = SetNode29;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	if (1 == isFileExists(SetNodeFile30String))
	{
		Matrix<int, Dynamic, Dynamic>SetNode30 = LinearMSTMMSolver::openDataInt(SetNodeFile30String);
		pMBSetNode->SetId = SetNodeId30;
		pMBSetNode->SetNodeID = SetNode30;
		(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
	};
	delete pMBSetNode;
	pMBSetNode = nullptr;
	
	MBSetSegmentNode* pMBSetSegmentNode = new MBSetSegmentNode;
	//SegmentSet信息
	if (1 == isFileExists(SegmentSetFile1String))
	{
		Matrix<int, Dynamic, Dynamic>SegmentSet1 = LinearMSTMMSolver::openDataInt(SegmentSetFile1String);
		pMBSetSegmentNode->SetSegmentId = SegmentSetId1;
		pMBSetSegmentNode->SetSegmentNodeID = SegmentSet1;
		(void)mbls->AllMBSetSegmentNode.insert(make_pair(pMBSetSegmentNode->SetSegmentId, (*pMBSetSegmentNode)));
	};
	if (1 == isFileExists(SegmentSetFile2String))
	{
		Matrix<int, Dynamic, Dynamic>SegmentSet2 = LinearMSTMMSolver::openDataInt(SegmentSetFile2String);
		pMBSetSegmentNode->SetSegmentId = SegmentSetId2;
		pMBSetSegmentNode->SetSegmentNodeID = SegmentSet2;
		(void)mbls->AllMBSetSegmentNode.insert(make_pair(pMBSetSegmentNode->SetSegmentId, (*pMBSetSegmentNode)));
	};
	if (1 == isFileExists(SegmentSetFile3String))
	{
		Matrix<int, Dynamic, Dynamic>SegmentSet3 = LinearMSTMMSolver::openDataInt(SegmentSetFile3String);
		pMBSetSegmentNode->SetSegmentId = SegmentSetId3;
		pMBSetSegmentNode->SetSegmentNodeID = SegmentSet3;
		(void)mbls->AllMBSetSegmentNode.insert(make_pair(pMBSetSegmentNode->SetSegmentId, (*pMBSetSegmentNode)));
	};
	if (1 == isFileExists(SegmentSetFile4String))
	{
		Matrix<int, Dynamic, Dynamic>SegmentSet4 = LinearMSTMMSolver::openDataInt(SegmentSetFile4String);
		pMBSetSegmentNode->SetSegmentId = SegmentSetId4;
		pMBSetSegmentNode->SetSegmentNodeID = SegmentSet4;
		(void)mbls->AllMBSetSegmentNode.insert(make_pair(pMBSetSegmentNode->SetSegmentId, (*pMBSetSegmentNode)));
	};
	if (1 == isFileExists(SegmentSetFile5String))
	{
		Matrix<int, Dynamic, Dynamic>SegmentSet5 = LinearMSTMMSolver::openDataInt(SegmentSetFile5String);
		pMBSetSegmentNode->SetSegmentId = SegmentSetId5;
		pMBSetSegmentNode->SetSegmentNodeID = SegmentSet5;
		(void)mbls->AllMBSetSegmentNode.insert(make_pair(pMBSetSegmentNode->SetSegmentId, (*pMBSetSegmentNode)));
	};
	if (1 == isFileExists(SegmentSetFile6String))
	{
		Matrix<int, Dynamic, Dynamic>SegmentSet6 = LinearMSTMMSolver::openDataInt(SegmentSetFile6String);
		pMBSetSegmentNode->SetSegmentId = SegmentSetId6;
		pMBSetSegmentNode->SetSegmentNodeID = SegmentSet6;
		(void)mbls->AllMBSetSegmentNode.insert(make_pair(pMBSetSegmentNode->SetSegmentId, (*pMBSetSegmentNode)));
	};
	delete pMBSetSegmentNode;
	pMBSetSegmentNode = nullptr;

	///////////////////////////////////////////////////////////////////////////////////////////////////
	
	// 刚体信息
	if (isFileExists(RigidBodyFileString) == 1)
	{
		Matrix<int, Dynamic, Dynamic>RigidBodyImformation1 = LinearMSTMMSolver::openDataInt(RigidBodyFileString);
		Matrix<double, Dynamic, Dynamic>RigidBodyImformation2 = LinearMSTMMSolver::openData(RigidBodyFileString);
		for (int i = 0; i < RigidBodyImformation1.rows(); i++)
		{
			inputRigidBody* InRigidBody = new inputRigidBody;
			(*InRigidBody).RigidBodyID = RigidBodyImformation1(i, 0);
			(*InRigidBody).RI1(0, 0) = RigidBodyImformation2(i, 1);
			(*InRigidBody).RI1(1, 0) = RigidBodyImformation2(i, 2);
			(*InRigidBody).RI1(2, 0) = RigidBodyImformation2(i, 3);
			(*InRigidBody).RI2(0, 0) = RigidBodyImformation2(i, 4);
			(*InRigidBody).RI2(1, 0) = RigidBodyImformation2(i, 5);
			(*InRigidBody).RI2(2, 0) = RigidBodyImformation2(i, 6);
			(*InRigidBody).RI3(0, 0) = RigidBodyImformation2(i, 7);
			(*InRigidBody).RI3(1, 0) = RigidBodyImformation2(i, 8);
			(*InRigidBody).RI3(2, 0) = RigidBodyImformation2(i, 9);
			(*InRigidBody).RO(0, 0) = RigidBodyImformation2(i, 10);
			(*InRigidBody).RO(1, 0) = RigidBodyImformation2(i, 11);
			(*InRigidBody).RO(2, 0) = RigidBodyImformation2(i, 12);
			(*InRigidBody).RC(0, 0) = RigidBodyImformation2(i, 13);
			(*InRigidBody).RC(1, 0) = RigidBodyImformation2(i, 14);
			(*InRigidBody).RC(2, 0) = RigidBodyImformation2(i, 15);
			(*InRigidBody).J.setZero(3, 3);
			(*InRigidBody).J(0, 0) = RigidBodyImformation2(i, 16);
			(*InRigidBody).J(1, 1) = RigidBodyImformation2(i, 17);
			(*InRigidBody).J(2, 2) = RigidBodyImformation2(i, 18);
			(*InRigidBody).OuO(0, 0) = RigidBodyImformation2(i, 19);
			(*InRigidBody).OuO(1, 0) = RigidBodyImformation2(i, 20);
			(*InRigidBody).OuO(2, 0) = RigidBodyImformation2(i, 21);
			(*InRigidBody).VO(0, 0) = RigidBodyImformation2(i, 22);
			(*InRigidBody).VO(1, 0) = RigidBodyImformation2(i, 23);
			(*InRigidBody).VO(2, 0) = RigidBodyImformation2(i, 24);
			(*InRigidBody).M = RigidBodyImformation2(i, 25);
			(*InRigidBody).OuLa1 = RigidBodyImformation2(i, 26);
			(*InRigidBody).OuLa2 = RigidBodyImformation2(i, 27);
			(*InRigidBody).OuLa3 = RigidBodyImformation2(i, 28);
			(*InRigidBody).OuLa4 = RigidBodyImformation2(i, 29);
			(*InRigidBody).Fc(0, 0) = RigidBodyImformation2(i, 30);
			(*InRigidBody).Fc(1, 0) = RigidBodyImformation2(i, 31);
			(*InRigidBody).Fc(2, 0) = RigidBodyImformation2(i, 32);
			(*InRigidBody).Mc(0, 0) = RigidBodyImformation2(i, 33);
			(*InRigidBody).Mc(1, 0) = RigidBodyImformation2(i, 34);
			(*InRigidBody).Mc(2, 0) = RigidBodyImformation2(i, 35);
			(*InRigidBody).ZbO(0, 0) = RigidBodyImformation2(i, 36);
			(*InRigidBody).ZbO(1, 0) = RigidBodyImformation2(i, 37);
			(*InRigidBody).ZbO(2, 0) = RigidBodyImformation2(i, 38);
			(*InRigidBody).ZbO(3, 0) = RigidBodyImformation2(i, 39);
			(*InRigidBody).ZbO(4, 0) = RigidBodyImformation2(i, 40);
			(*InRigidBody).ZbO(5, 0) = RigidBodyImformation2(i, 41);
			InRigidBody->RigidBodySetID = RigidBodyImformation1(i, 42);
			for (int j=0;j< mbls->AllMBSetNode[InRigidBody->RigidBodySetID].SetNodeID.cols();j++)
			{
				
				InRigidBody->MeshCoor.insert(make_pair(mbls->AllMBSetNode[InRigidBody->RigidBodySetID].SetNodeID(0,j), mbls->AllMBNode[mbls->AllMBSetNode[InRigidBody->RigidBodySetID].SetNodeID(0, j)].NodeCoordinates));
			}
			(*IADate).inputAllRigidBody.insert(make_pair((*InRigidBody).RigidBodyID, (*InRigidBody)));
			delete InRigidBody;
		}
	};

	// 柱铰信息
	if (isFileExists(ColumHingeFileString) == 1)
	{
		Matrix<int, Dynamic, Dynamic>ColumHingeImformation1 = LinearMSTMMSolver::openDataInt(ColumHingeFileString);
		Matrix<double, Dynamic, Dynamic>ColumHingeImformation2 = LinearMSTMMSolver::openData(ColumHingeFileString);
		inputColumnHinge* InColumnHinge = new inputColumnHinge;
		for (int i = 0; i < ColumHingeImformation1.rows(); i++)
		{
			InColumnHinge->ColumnHingeID = ColumHingeImformation1(i, 0);
			(*InColumnHinge).SeiTa0(0, 0) = ColumHingeImformation2(i, 1);
			(*InColumnHinge).SeiTa0(1, 0) = ColumHingeImformation2(i, 2);
			(*InColumnHinge).SeiTa0(2, 0) = ColumHingeImformation2(i, 3);
			(*InColumnHinge).WR(0, 0) = ColumHingeImformation2(i, 4);
			(*InColumnHinge).WR(1, 0) = ColumHingeImformation2(i, 5);
			(*InColumnHinge).WR(2, 0) = ColumHingeImformation2(i, 6);
			(*InColumnHinge).K(0, 0) = ColumHingeImformation2(i, 7);
			(*InColumnHinge).K(0, 1) = ColumHingeImformation2(i, 8);
			(*InColumnHinge).K(0, 2) = ColumHingeImformation2(i, 9);
			(*InColumnHinge).C(0, 0) = ColumHingeImformation2(i, 10);
			(*InColumnHinge).C(0, 1) = ColumHingeImformation2(i, 11);
			(*InColumnHinge).C(0, 2) = ColumHingeImformation2(i, 12);
			(*IADate).inputAllColumnHinge.insert(make_pair((*InColumnHinge).ColumnHingeID, (*InColumnHinge)));
		}
		delete InColumnHinge;
	};

	// 球铰信息
	if (isFileExists(BallJointFileString) == 1)
	{
		Matrix<int, Dynamic, Dynamic>BallJointImformation1 = LinearMSTMMSolver::openDataInt(BallJointFileString);
		Matrix<double, Dynamic, Dynamic>BallJointImformation2 = LinearMSTMMSolver::openData(BallJointFileString);
		inputBallJoint* InBallJoint = new inputBallJoint;
		for (int i = 0; i < BallJointImformation1.rows(); i++)
		{
			(*InBallJoint).BallJointID = BallJointImformation1(i, 0);
			(*InBallJoint).SeiTa0(0, 0) = BallJointImformation2(i, 10);
			(*InBallJoint).SeiTa0(1, 0) = BallJointImformation2(i, 11);
			(*InBallJoint).SeiTa0(2, 0) = BallJointImformation2(i, 12);
			(*InBallJoint).WR(0, 0) = BallJointImformation2(i, 13);
			(*InBallJoint).WR(1, 0) = BallJointImformation2(i, 14);
			(*InBallJoint).WR(2, 0) = BallJointImformation2(i, 15);
			(*InBallJoint).K.setZero(3, 3);
			(*InBallJoint).K(0, 0) = BallJointImformation2(i, 1);
			(*InBallJoint).K(1, 1) = BallJointImformation2(i, 2);
			(*InBallJoint).K(2, 2) = BallJointImformation2(i, 3);
			(*InBallJoint).C.setZero(3, 3);
			(*InBallJoint).C(0, 0) = BallJointImformation2(i, 4);
			(*InBallJoint).C(1, 1) = BallJointImformation2(i, 5);
			(*InBallJoint).C(2, 2) = BallJointImformation2(i, 6);
			(*InBallJoint).Md(0, 0) = BallJointImformation2(i, 7);
			(*InBallJoint).Md(1, 0) = BallJointImformation2(i, 8);
			(*InBallJoint).Md(2, 0) = BallJointImformation2(i, 9);
			(*IADate).inputAllBallJoint.insert(make_pair((*InBallJoint).BallJointID, (*InBallJoint)));
		}
		delete InBallJoint;
	};

	//Contact
	if (1 == isFileExists(MBContactFileString))
	{
		//Contact 关键字信息
		Matrix<double, Dynamic, Dynamic>MBContactImformation = LinearMSTMMSolver::openData(MBContactFileString);
		Matrix<int, Dynamic, Dynamic>MBContactImformation2 = LinearMSTMMSolver::openDataInt(MBContactFileString);
		//cout << ContactImformation;
		for (int i = 0; i < MBContactImformation.rows(); i++)
		{
			InputFEMtoMBContact* MBInCta = new InputFEMtoMBContact;
			MBInCta->ContactNumber = MBContactImformation2(i, 0);
			MBInCta->ContactType = 1;
			if ((0 == MBContactImformation(i, 5)) && (0 == MBContactImformation(i, 6)))
			{
				MBInCta->FrictionJudgment = 1;
			}
			else
			{
				MBInCta->FrictionJudgment = 0;
			};
			//节点集号
			MBInCta->SlaveNodeSetId = MBContactImformation2(i, 1);
			MBInCta->MasterNodeSetId = MBContactImformation2(i, 2);
			//摩擦系数
			MBInCta->StaticFrictionCoefficient = MBContactImformation(i, 5);
			MBInCta->DynamicFrictionCoefficient = MBContactImformation(i, 6);
			//主从面节点号
			for (int j = 0; j < mbls->AllMBSetSegmentNode[MBInCta->MasterNodeSetId].SetSegmentNodeID.rows(); j++)
			{
				(void)MBInCta->MasterContactNode.insert(make_pair((j + 1), mbls->AllMBSetSegmentNode[MBInCta->MasterNodeSetId].SetSegmentNodeID.row(j).adjoint()));
			};
			for (int k = 0; k < mbls->AllMBSetNode[MBInCta->SlaveNodeSetId].SetNodeID.rows(); k++)
			{
				(void)MBInCta->SlaveContactNode.insert(make_pair((k + 1), mbls->AllMBSetNode[MBInCta->SlaveNodeSetId].SetNodeID.row(k).adjoint()));
			};
			(void)IADate->InputAllFEMtoMBContact.insert(make_pair(MBInCta->ContactNumber, (*MBInCta)));
			delete MBInCta;
			MBInCta = nullptr;

		}

	}

	//ConnectNodeFileString
	if (isFileExists(ConnectNodeFileString) == 1)
	{
		Matrix<int, Dynamic, Dynamic>ConnectNodeImformation = LinearMSTMMSolver::openDataInt(ConnectNodeFileString);
		IADate->ConnectNode = ConnectNodeImformation(0, 0);

	}

	delete mbls;
	mbls = nullptr;
	return 1;
};

//读文件主函数
InputAllDate* InputFileProject::inputFunction(const std::string& fileToOpen)
{

    In.open(fileToOpen);
    while (getline(In, line))
    {
        //*LOAD_BODY_PARTS
        if ("*LOAD_BODY_PARTS" ==line )
        {
            LoadBodyZFile.close();
            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            ComputingTimeFile.close();
            LoadNodeFile.close();
            LoadBodyYFile.close();
        }

        //*SET_PART_LIST
        if ( "*SET_PART_LIST"==line )
        {
            LoadBodyZFile.close();
            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            ComputingTimeFile.close();
            LoadNodeFile.close();
            LoadBodyYFile.close();
        }

        //*LOAD_BODY_Y
        if ( "*LOAD_BODY_Y"== line)
        {
            LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            ComputingTimeFile.close();
            LoadNodeFile.close();
			line = line.erase(0, 1);
            LoadBodyYFileString = getFileName(line);
            LoadBodyYFile.open(LoadBodyYFileString);
        }
        if (LoadBodyYFile.is_open())
        {
            getdigit2(LoadBodyYFile, line);
        };

        //*LOAD_BODY_Z
		if ( "*LOAD_BODY_Z"==line )
		{
			LoadBodyYFile.close();

			WallSlaveNodeFile.close();
			BoundarySetFile.close();
			HourglassFile.close();
			RigidWallFile.close();
			TimeIncrementFile.close();
			NodeVelocityFile.close();
			PlaFile.close();
			PartFile.close();
			SecSolidFile.close();
			MasterNodeFile.close();
			ContactFile.close();
			EleSoFile.close();
			SlaveNodeFile.close();
			BoundaryFile.close();
			EleBFile.close();
			EleShFile.close();
			SecBeamFile.close();
			SecShellFile.close();
			SetFile.close();
			ComputingTimeFile.close();
			LoadNodeFile.close();
			line=line.erase(0, 1);
            LoadBodyZFileString = getFileName(line);
            LoadBodyZFile.open(LoadBodyZFileString);
		}
		if (LoadBodyZFile.is_open())
		{
			getdigit2(LoadBodyZFile, line);
		};

        //*DEFINE_CURVE
        if ( "*DEFINE_CURVE"==line )
		{
			LoadBodyYFile.close();

            LoadBodyZFile.close();
            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            ComputingTimeFile.close();
            LoadNodeFile.close();
			line = line.erase(0, 1);
            DefineCurveFileString = getFileName(line);
            DefineCurveFile.open(DefineCurveFileString);
        }
        if (DefineCurveFile.is_open())
        {
            getdigit2(DefineCurveFile, line);
        };

        //*LOAD_NODE_SET
        if ( "*LOAD_NODE_SET"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            ComputingTimeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            LoadNodeFileString = getFileName(line);
            LoadNodeFile.open(LoadNodeFileString);
        }
        if (LoadNodeFile.is_open())
        {
            getdigit2(LoadNodeFile, line);
        };

        //计算时长
        if ( "*CONTROL_TERMINATION"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            ComputingTimeFileString = getFileName(line);
            ComputingTimeFile.open(ComputingTimeFileString);
        }
        if (ComputingTimeFile.is_open())
        {
            getdigit2(ComputingTimeFile, line);
        };

        //步长
        if (  "*CONTROL_TIMESTEP"== line)
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            NodeVelocityFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            TimeIncrementFileString = getFileName(line);
            TimeIncrementFile.open(getFileName(line));
        }
        if (TimeIncrementFile.is_open())
        {
            getdigit2(TimeIncrementFile, line);
        };

		if ( "*DATABASE_BINARY_D3PLOT"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

			WallSlaveNodeFile.close();
			BoundarySetFile.close();
			HourglassFile.close();
			RigidWallFile.close();
			ComputingTimeFile.close();
			TimeIncrementFile.close();
			NodeVelocityFile.close();
			PlaFile.close();
			PartFile.close();
			SecSolidFile.close();
			MasterNodeFile.close();
			ContactFile.close();
			EleSoFile.close();
			SlaveNodeFile.close();
			BoundaryFile.close();
			EleBFile.close();
			EleShFile.close();
			SecBeamFile.close();
			SecShellFile.close();
			SetFile.close();
			LoadNodeFile.close();
			DefineCurveFile.close();
		};

        if ( "*DATABASE_GLSTAT"== line)
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
        };

        if ( "*CONTROL_IMPLICIT_EIGENVALUE"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
        };

        //节点
        if ( "*NODE"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            NodeFileString = getFileName(line);
            NodeFile.open(NodeFileString);
            NodeFile.clear();
            // continue;
        }
        if (NodeFile.is_open())
        {
            getdigit2(NodeFile, line);
        }

        //材料部分最终输出文件见最下方，InputElaFile，InputPlaFile。
        if ( "*MAT_ELASTIC"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
            line=line.erase(0, 1);
            ElaFileString = getFileName(line);
            ElaFile.open(getFileName(line));
            ElaFile.clear();
            //continue;
        }
        if (ElaFile.is_open())
        {
            if (  (' '==line[0] )&& (isdigit(line[9])))
            {
                line = line.insert(10, " ");
				line = line.insert(21, " ");
                ElaFile << line << endl;
            }
        }

        if ( "*MAT_PLASTIC_KINEMATIC"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            ElaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            PlaFileString = getFileName(line);
            PlaFile.open(getFileName(line));
            PlaFile.clear();
            //continue;
        }
        if (PlaFile.is_open())
        {
            if ( (' '==line[0] ) && (isdigit(line[9])))
            {
                line = line.insert(10, " ");
                PlaFile << line << endl;
            }
        }

        //Part
        if ( "*PART"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            ElaFile.close();
            PlaFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            PartFileString = getFileName(line);
            PartFile.open(getFileName(line));
            //continue;
        }
        if (PartFile.is_open())
        {
            if (' ' ==line[0] )
            {
				line = line.erase(49, 2);
                PartFile << line << endl;
            }
        };

        //沙漏
        if ( "*HOURGLASS"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            SecSolidFile.close();
            BoundarySetFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            ElaFile.close();
            PlaFile.close();
            PartFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            HourglassFileString = getFileName(line);
            HourglassFile.open(getFileName(line));
            //continue;
        }
        if (HourglassFile.is_open())
        {
            getdigit2(HourglassFile, line);
        }

        //初始速度*INITIAL_VELOCITY_GENERATION
        if ( "*INITIAL_VELOCITY_GENERATION"== line)
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeFile.close();
            ElaFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            NodeVelocityFileString = getFileName(line);
            NodeVelocityFile.open(getFileName(line));
        }
        if (NodeVelocityFile.is_open())
        {
            if (  ' '==line[0])
            {
                NodeVelocityFile << line << " ";
            }
        }

        //*BOUNDARY_SPC_SET
        if ( "*BOUNDARY_SPC_SET"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            ElaFile.close();
            PlaFile.close();
            PartFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            BoundarySetFileString = getFileName(line);
            BoundarySetFile.open(getFileName(line));
            //continue;
        }
        if (BoundarySetFile.is_open())
        {
            getdigit2(BoundarySetFile, line);
        }

        if ( "*SET_SEGMENT"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

			WallSlaveNodeFile.close();
			BoundarySetFile.close();
			HourglassFile.close();
			RigidWallFile.close();
			ComputingTimeFile.close();
			TimeIncrementFile.close();
			NodeVelocityFile.close();
			NodeFile.close();
			ElaFile.close();
			PlaFile.close();
			PartFile.close();
			SecSolidFile.close();
			MasterNodeFile.close();
			ContactFile.close();
			EleSoFile.close();
			SlaveNodeFile.close();
			BoundaryFile.close();
			EleBFile.close();
			EleShFile.close();
			SecBeamFile.close();
			SecShellFile.close();
			SetFile.close();
			LoadNodeFile.close();
			DefineCurveFile.close();
        }

        //接触
        if ( "*CONTACT_AUTOMATIC_NODES_TO_SURFACE_ID"==line  ||  "*CONTACT_NODES_TO_SURFACE_ID"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            ElaFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            ContactFileString = "Contact.txt";
            ContactFileString2 = "ContactTemp.txt";
            ContactFile.open(ContactFileString2);
            ContactFile.clear();
            ContactFile << endl;
            //  continue;
        }
        if (ContactFile.is_open())
        {
            if ( ' ' ==line[0])
            {
                ContactFile << line << " ";
            }
        }

        //实体单元   
        if ( "*ELEMENT_SOLID"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            ElaFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            EleSoFileString = getFileName(line);
            EleSoFile.open(getFileName(line));
			EleSoFile.clear();
            // continue;
        }
        if (EleSoFile.is_open())
        {
            getdigit2(EleSoFile, line);
        }

        //从面节点
        if ( "*SET_NODE_LIST"== line)
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            BoundarySetFile.close();
            HourglassFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            ElaFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            RigidWallFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
        }

        //边界条件
        if (  "*BOUNDARY_SPC_NODE"==line)
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            ElaFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            BoundaryFileString = getFileName(line);
            BoundaryFile.open(getFileName(line));
            // continue;
        }
        if (BoundaryFile.is_open())
        {
            getdigit2(BoundaryFile, line);
        }

        //刚性墙
        if ( "*RIGIDWALL_PLANAR_FINITE_ID"== line)
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();
            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            ElaFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            RigidWallFileString2 = getFileName2(line, AdditionalDigit);
            RigidWallFileString = getFileName(line);
            RigidWallFile.open(RigidWallFileString2);
            RigidWallFile.clear();
            RigidWallFile << endl;
        }
        if (RigidWallFile.is_open())
        {
            if ( ' ' ==line[0])
            {
                line = line.insert(20, " ");
                line = line.insert(51, " ");
                RigidWallFile << line << " ";
            }
        }

        //梁单元
        if ("*ELEMENT_BEAM" == line)
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            ElaFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            RigidWallFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            EleBFileString = getFileName(line);
            EleBFile.open(getFileName(line));
            // continue;
        }
        if (EleBFile.is_open())
        {
            getdigit2(EleBFile, line);
        }

        //壳单元
        if ( "*ELEMENT_SHELL"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            ElaFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            EleShFileString = getFileName(line);
            EleShFile.open(getFileName(line));
            EleShFile.clear();
            // continue;
        }
        if (EleShFile.is_open())
        {
            getdigit2(EleShFile, line);
        }

        //SECTION梁
        if ( "*SECTION_BEAM"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            ElaFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            SecBeamFileString = getFileName(line);
            SecBeamFile.open(getFileName(line));
            continue;
        }
        if (SecBeamFile.is_open())
        {
            if ( ' '==line[0]  || isalpha(line[0]) || isdigit(line[0]))
            {
                line = line.insert(0, AdditionalDigit);
                SecBeamFile << line << " ";
            }
        }

        //SECTION壳
        if ( "*SECTION_SHELL"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();

            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            ElaFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            SecShellFileString = getFileName(line);
            SecShellFileString2 = getFileName2(line, AdditionalDigit);
            SecShellFile.open(SecShellFileString2);
            SecShellFile.clear();
            SecShellFile << endl;
            // continue;
        }
        if (SecShellFile.is_open())
        {
            if ( ' '==line[0] )
            {
                SecShellFile << line << " ";
            }
        }

        //SECTION实体
        if ( "*SECTION_SOLID"==line )
		{
			LoadBodyYFile.close();

			LoadBodyZFile.close();
            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            ElaFile.close();
            PlaFile.close();
            PartFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			line = line.erase(0, 1);
            SecSolidFileString = getFileName(line);
            SecSolidFile.open(getFileName(line));
            //continue;
        }
        if (SecSolidFile.is_open())
        {
            getdigit2(SecSolidFile, line);
        };
        if ( "*END"==line )
		{
			LoadBodyYFile.close();
			LoadBodyZFile.close();
            WallSlaveNodeFile.close();
            BoundarySetFile.close();
            HourglassFile.close();
            RigidWallFile.close();
            ComputingTimeFile.close();
            TimeIncrementFile.close();
            NodeVelocityFile.close();
            NodeFile.close();
            ElaFile.close();
            PlaFile.close();
            PartFile.close();
            SecSolidFile.close();
            MasterNodeFile.close();
            ContactFile.close();
            EleSoFile.close();
            SlaveNodeFile.close();
            BoundaryFile.close();
            EleBFile.close();
            EleShFile.close();
            SecBeamFile.close();
            SecShellFile.close();
            SetFile.close();
            LoadNodeFile.close();
            DefineCurveFile.close();
			PanduanSecondpart = 1;
        }



    }
    In.close();

     //SecShell文件
	  InSecShell.open(SecShellFileString2);
     SecShellFile2.open(SecShellFileString);
    while (getline(InSecShell,LineSecShell))
    {
        if (SecShellFile2.is_open())
        {
            if ( ' '==LineSecShell[0] )
            {
                SecShellFile2 << LineSecShell << endl;
            }
        }

    }
    SecShellFile2.close();
    InSecShell.close();

    //Contact 文件
	 InContact.open(ContactFileString2);
    ContactFile2.open(ContactFileString);
    while (getline(InContact, LineContact))
    {
        if (ContactFile2.is_open())
        {
            if (  ' '==LineContact[0])
            {
                ContactFile2 << LineContact << endl;
            }
        }
    }
    ContactFile2.close();
    InContact.close();

    //RIGIDWALL_PLANAR_FINITE_ID
    InRigidwall.open(RigidWallFileString2);
    RigidWallFile2.open(RigidWallFileString);
	while (getline(InRigidwall, LineRigidwall))
	{
		if (RigidWallFile2.is_open())
		{
			if ( ' '==LineRigidwall[0] )
			{
                RigidWallFile2 << LineRigidwall << endl;
			}
		}

	}
    RigidWallFile2.close();
    InRigidwall.close();

	SetNode* pSetNode = new SetNode;
	lsmap* ls = new lsmap;

    //SegmentSet 文件
    InSegmentSet.open(fileToOpen);
    while (getline(InSegmentSet, LineSegmentSet))
    {
        //主面节点
        if ( "*SET_SEGMENT"==LineSegmentSet )
        {
            SetSegment = LineSegmentSet.erase(0, 1);
			PanduanSegmentSetNode = 1;

        }
        if ( (1==PanduanSegmentSetNode)&& ("         1                                        MECH      "==LineSegmentSet) )
        {
			LineSegmentSet=LineSegmentSet.erase(0, 9);
			LineSegmentSet = LineSegmentSet.erase(1,50);
            SegmentSetId1 = LineSegmentSet.at(0) - '0';
            SegmentSetFile1String = getFileName2(SetSegment, LineSegmentSet);
            SegmentSetFile1.open(SegmentSetFile1String);
        }
        if (SegmentSetFile1.is_open())
        {
            getdigit3(SegmentSetFile1, LineSegmentSet, 19);
        }
        if ( (1 == PanduanSegmentSetNode )&&  ("         2                                        MECH      "==LineSegmentSet ))
        {
            SegmentSetFile1.close();
			LineSegmentSet = LineSegmentSet.erase(0, 9);
			LineSegmentSet = LineSegmentSet.erase(1,50);
            SegmentSetId2 = LineSegmentSet.at(0) - '0';
            SegmentSetFile2String = getFileName2(SetSegment, LineSegmentSet);
            SegmentSetFile2.open(SegmentSetFile2String);
        }
        if (SegmentSetFile2.is_open())
        {
            getdigit3(SegmentSetFile2, LineSegmentSet, 19);
        }
		if ( (1==PanduanSegmentSetNode ) && ( "         3                                        MECH      "==LineSegmentSet) )
		{
			SegmentSetFile1.close();
			SegmentSetFile2.close();

			LineSegmentSet = LineSegmentSet.erase(0, 9);
			LineSegmentSet = LineSegmentSet.erase(1, 50);
			SegmentSetId3 = LineSegmentSet.at(0) - '0';
			SegmentSetFile3String = getFileName2(SetSegment, LineSegmentSet);
			SegmentSetFile3.open(SegmentSetFile3String);
		}
		if (SegmentSetFile3.is_open())
		{
			getdigit3(SegmentSetFile3, LineSegmentSet, 19);
		}
		if (( 1==PanduanSegmentSetNode  )&& ( "         4                                        MECH      "==LineSegmentSet) )
		{
			SegmentSetFile1.close();
			SegmentSetFile3.close();
			SegmentSetFile2.close();
			LineSegmentSet = LineSegmentSet.erase(0, 9);
			LineSegmentSet = LineSegmentSet.erase(1, 50);
			SegmentSetId4 = LineSegmentSet.at(0) - '0';
			SegmentSetFile4String = getFileName2(SetSegment, LineSegmentSet);
			SegmentSetFile4.open(SegmentSetFile4String);
		}
		if (SegmentSetFile4.is_open())
		{
			getdigit3(SegmentSetFile4, LineSegmentSet, 19);
		}
		if (( 1== PanduanSegmentSetNode) &&  ("         5                                        MECH      " ==LineSegmentSet))
		{
			SegmentSetFile1.close();
			SegmentSetFile3.close();
			SegmentSetFile2.close();
			SegmentSetFile4.close();

			LineSegmentSet = LineSegmentSet.erase(0, 9);
			LineSegmentSet = LineSegmentSet.erase(1, 50);
			SegmentSetId5 = LineSegmentSet.at(0) - '0';
			SegmentSetFile5String = getFileName2(SetSegment, LineSegmentSet);
			SegmentSetFile5.open(SegmentSetFile5String);
		}
		if (SegmentSetFile5.is_open())
		{
			getdigit3(SegmentSetFile5, LineSegmentSet, 19);
		}
        if (( 1==PanduanSegmentSetNode)  &&  ("         6                                        MECH      "== LineSegmentSet))
		{
			SegmentSetFile1.close();
			SegmentSetFile3.close();
			SegmentSetFile2.close();
			SegmentSetFile4.close();
			SegmentSetFile5.close();
			LineSegmentSet = LineSegmentSet.erase(0, 9);
			LineSegmentSet = LineSegmentSet.erase(1, 50);
			SegmentSetId6 = LineSegmentSet.at(0) - '0';
			SegmentSetFile6String = getFileName2(SetSegment, LineSegmentSet);
			SegmentSetFile6.open(SegmentSetFile6String);
		}
		if (SegmentSetFile6.is_open())
		{
			getdigit3(SegmentSetFile6, LineSegmentSet, 19);
		}
        if (("*CONTACT_AUTOMATIC_NODES_TO_SURFACE_ID" ==LineSegmentSet) ||( "*CONTACT_NODES_TO_SURFACE_ID"==LineSegmentSet ) || ("*RIGIDWALL_PLANAR_FINITE_ID" == LineSegmentSet) || ("*ELEMENT_BEAM" == LineSegmentSet)
			|| ("*ELEMENT_SHELL" == LineSegmentSet) || ("*ELEMENT_SOLID" == LineSegmentSet) || ("*SET_NODE_LIST" == LineSegmentSet) || ("*DEFINE_CURVE" == LineSegmentSet) || ("*SET_PART_LIST" == LineSegmentSet)
			|| ("*END" == LineSegmentSet))
        {
			SegmentSetFile1.close();
			SegmentSetFile2.close();
			SegmentSetFile3.close();
			SegmentSetFile4.close();
			SegmentSetFile6.close();
			SegmentSetFile5.close();
            
			//LineSegmentSet = nullptr;
			PanduanSegmentSetNode = 0;
        }
    }
	InSegmentSet.close();

	//SetNode
 //   InSetNode.open(fileToOpen);
	//while (getline(InSetNode, LineSetNode))
	//{
	//	if ("*SET_NODE_LIST" == LineSetNode)
	//	{
	//		Setnodelist = LineSetNode.erase(0, 1);
	//		PanduanSetNode = 1;
	//	}
	//	if ((1 == PanduanSetNode) && ("         1                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile2.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile10.close();
	//		SetNodeFile11.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 9);
	//		LineSetNode = LineSetNode.erase(1, 50);
	//		SetNodeId1 = LineSetNode.at(0) - '0';
	//		SetNodeFile1String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile1.open(SetNodeFile1String);
	//		continue;
	//	}
	//	if (SetNodeFile1.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile1 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("         2                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile10.close();
	//		SetNodeFile11.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 9);
	//		LineSetNode = LineSetNode.erase(1, 50);
	//		SetNodeId2 = LineSetNode.at(0) - '0';
	//		SetNodeFile2String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile2.open(SetNodeFile2String);
	//		continue;
	//	}
	//	if (SetNodeFile2.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile2 << LineSetNode << " ";
	//		}
	//	}

	//	if ((1 == PanduanSetNode) && ("         3                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile2.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile10.close();
	//		SetNodeFile11.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 9);
	//		LineSetNode = LineSetNode.erase(1, 50);
	//		SetNodeId3 = LineSetNode.at(0) - '0';
	//		SetNodeFile3String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile3.open(SetNodeFile3String);
	//		continue;
	//	}
	//	if (SetNodeFile3.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile3 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("         4                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile2.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile10.close();
	//		SetNodeFile11.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 9);
	//		LineSetNode = LineSetNode.erase(1, 50);
	//		SetNodeId4 = LineSetNode.at(0) - '0';
	//		SetNodeFile4String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile4.open(SetNodeFile4String);
	//		continue;
	//	}
	//	if (SetNodeFile4.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile4 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("         5                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile2.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile10.close();
	//		SetNodeFile11.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 9);
	//		LineSetNode = LineSetNode.erase(1, 50);
	//		SetNodeId5 = LineSetNode.at(0) - '0';
	//		SetNodeFile5String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile5.open(SetNodeFile5String);
	//		continue;
	//	}
	//	if (SetNodeFile5.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile5 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("         6                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile2.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile10.close();
	//		SetNodeFile11.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 9);
	//		LineSetNode = LineSetNode.erase(1, 50);
	//		SetNodeId6 = LineSetNode.at(0) - '0';
	//		SetNodeFile6String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile6.open(SetNodeFile6String);
	//		continue;
	//	}
	//	if (SetNodeFile6.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (LineSetNode[0] == ' ')
	//		{
	//			SetNodeFile6 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("         7                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile2.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile10.close();
	//		SetNodeFile11.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 9);
	//		LineSetNode = LineSetNode.erase(1, 50);
	//		SetNodeId7 = LineSetNode.at(0) - '0';
	//		SetNodeFile7String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile7.open(SetNodeFile7String);
	//		continue;
	//	}
	//	if (SetNodeFile7.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (LineSetNode[0] == ' ')
	//		{
	//			SetNodeFile7 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("         8                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile2.close();
	//		SetNodeFile9.close();
	//		SetNodeFile10.close();
	//		SetNodeFile11.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 9);
	//		LineSetNode = LineSetNode.erase(1, 50);
	//		SetNodeId8 = LineSetNode.at(0) - '0';
	//		SetNodeFile8String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile8.open(SetNodeFile8String);
	//		continue;
	//	}
	//	if (SetNodeFile8.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile8 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("         9                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile11.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 9);
	//		LineSetNode = LineSetNode.erase(1, 50);
	//		SetNodeId9 = LineSetNode.at(0) - '0';
	//		SetNodeFile9String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile9.open(SetNodeFile9String);
	//		continue;
	//	}
	//	if (SetNodeFile9.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile9 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        10                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile11.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId10 = 10;
	//		SetNodeFile10String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile10.open(SetNodeFile10String);
	//		continue;
	//	}
	//	if (SetNodeFile10.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile10 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        11                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId11 = 11;
	//		SetNodeFile11String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile11.open(SetNodeFile11String);
	//		continue;
	//	}
	//	if (SetNodeFile11.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile11 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        12                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile11.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);

	//		SetNodeId12 = 12;
	//		SetNodeFile12String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile12.open(SetNodeFile12String);
	//		continue;
	//	}
	//	if (SetNodeFile12.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile12 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        13                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile11.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId13 = 13;
	//		SetNodeFile13String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile13.open(SetNodeFile13String);
	//		continue;
	//	}
	//	if (SetNodeFile13.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile13 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        14                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile11.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId14 = 14;
	//		SetNodeFile14String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile14.open(SetNodeFile14String);
	//		continue;
	//	}
	//	if (SetNodeFile14.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile14 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        15                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile11.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId15 = 15;
	//		SetNodeFile15String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile15.open(SetNodeFile15String);
	//		continue;
	//	}
	//	if (SetNodeFile15.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile15 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        16                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile11.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId16 = 16;
	//		SetNodeFile16String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile16.open(SetNodeFile16String);
	//		continue;
	//	}
	//	if (SetNodeFile16.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile16 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        17                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile11.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId17 = 17;
	//		SetNodeFile17String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile17.open(SetNodeFile17String);
	//		continue;
	//	}
	//	if (SetNodeFile17.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile17 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        18                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile11.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId18 = 18;
	//		SetNodeFile18String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile18.open(SetNodeFile18String);
	//		continue;
	//	}
	//	if (SetNodeFile18.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile18 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        19                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile11.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId19 = 19;
	//		SetNodeFile19String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile19.open(SetNodeFile19String);
	//		continue;
	//	}
	//	if (SetNodeFile19.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile19 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        20                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile11.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId20 = 20;
	//		SetNodeFile20String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile20.open(SetNodeFile20String);
	//		continue;
	//	}
	//	if (SetNodeFile20.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile20 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        21                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile11.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId21 = 21;
	//		SetNodeFile21String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile21.open(SetNodeFile21String);
	//		continue;
	//	}
	//	if (SetNodeFile21.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile21 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        22                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile11.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId22 = 22;
	//		SetNodeFile22String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile22.open(SetNodeFile22String);
	//		continue;
	//	}
	//	if (SetNodeFile22.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile22 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        23                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile11.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId23 = 23;
	//		SetNodeFile23String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile23.open(SetNodeFile23String);
	//		continue;
	//	}
	//	if (SetNodeFile23.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile23 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        24                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile11.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId24 = 24;
	//		SetNodeFile24String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile24.open(SetNodeFile24String);
	//		continue;
	//	}
	//	if (SetNodeFile24.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile24 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        25                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile11.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId25 = 25;
	//		SetNodeFile25String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile25.open(SetNodeFile25String);
	//		continue;
	//	}
	//	if (SetNodeFile25.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile25 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        26                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile11.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId26 = 26;
	//		SetNodeFile26String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile26.open(SetNodeFile26String);
	//		continue;
	//	}
	//	if (SetNodeFile26.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile26 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        27                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile11.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId27 = 27;
	//		SetNodeFile27String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile27.open(SetNodeFile27String);
	//		continue;
	//	}
	//	if (SetNodeFile27.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile27 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        28                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile11.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId28 = 28;
	//		SetNodeFile28String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile28.open(SetNodeFile28String);
	//		continue;
	//	}
	//	if (SetNodeFile28.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile28 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        29                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile11.close();
	//		SetNodeFile30.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId29 = 29;
	//		SetNodeFile29String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile29.open(SetNodeFile29String);
	//		continue;
	//	}
	//	if (SetNodeFile29.is_open() && (LineSetNode.find("MECH") == string::npos))
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile29 << LineSetNode << " ";
	//		}
	//	}
	//	if ((1 == PanduanSetNode) && ("        30                                        MECH      " == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile2.close();
	//		SetNodeFile10.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile11.close();
	//		LineSetNode = LineSetNode.erase(0, 8);
	//		LineSetNode = LineSetNode.erase(2, 50);
	//		SetNodeId30 = 30;
	//		SetNodeFile30String = getFileName2(Setnodelist, LineSetNode);
	//		SetNodeFile30.open(SetNodeFile30String);
	//		continue;
	//	}
	//	if (SetNodeFile30.is_open())
	//	{
	//		if (' ' == LineSetNode[0])
	//		{
	//			SetNodeFile30 << LineSetNode << " ";
	//		}
	//	}

	//	if (("*END" == LineSetNode) || ("*DEFINE_CURVE" == LineSetNode) || ("*BOUNDARY_SPC_NODE" == LineSetNode) || ("*SET_PART_LIST" == LineSetNode) || ("*CONTACT_NODES_TO_SURFACE_ID" == LineSetNode))
	//	{
	//		SetNodeFile1.close();
	//		SetNodeFile3.close();
	//		SetNodeFile4.close();
	//		SetNodeFile5.close();
	//		SetNodeFile6.close();
	//		SetNodeFile7.close();
	//		SetNodeFile8.close();
	//		SetNodeFile9.close();
	//		SetNodeFile10.close();
	//		SetNodeFile11.close();
	//		SetNodeFile12.close();
	//		SetNodeFile13.close();
	//		SetNodeFile14.close();
	//		SetNodeFile15.close();
	//		SetNodeFile16.close();
	//		SetNodeFile17.close();
	//		SetNodeFile18.close();
	//		SetNodeFile19.close();
	//		SetNodeFile20.close();
	//		SetNodeFile21.close();
	//		SetNodeFile22.close();
	//		SetNodeFile23.close();
	//		SetNodeFile24.close();
	//		SetNodeFile25.close();
	//		SetNodeFile26.close();
	//		SetNodeFile27.close();
	//		SetNodeFile28.close();
	//		SetNodeFile29.close();
	//		SetNodeFile30.close();
	//		SetNodeFile2.close();
	//		
	//		//LineSetNode = nullptr;
	//		PanduanSetNode = 0;
	//	}
	//}
	//InSetNode.close();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//SetNode  TEST
	InSetNode.open(fileToOpen);
	while (getline(InSetNode, LineSetNode))
	{
		if ("*SET_NODE_LIST" == LineSetNode)
		{
			Setnodelist = LineSetNode.erase(0, 1);
			SetNodeFile1String = getFileName( LineSetNode);
			SetNodeFile1.open(SetNodeFile1String);
			SetNodeFile1.clear();
			SetNodeFile1 << endl;
			PanduanSetNode = 1;
		}
		if (SetNodeFile1.is_open())
		{
			if (' ' == LineSetNode[0])
			{
				SetNodeFile1 << LineSetNode << " ";
			}
		}
		if (("*END" == LineSetNode) || ("*DEFINE_CURVE" == LineSetNode) || ("*BOUNDARY_SPC_NODE" == LineSetNode) || ("*SET_PART_LIST" == LineSetNode) || ("*CONTACT_NODES_TO_SURFACE_ID" == LineSetNode))
		{
			SetNodeFile1.close();
			PanduanSetNode = 0;
		}
	}
	InSetNode.close();

	ifstream InSetNode2;
	InSetNode2.open(SetNodeFile1String);
	SetNodeFile2String = "SETNODELIST_TEST.txt";
	string LineSetNode2;
	int panduanneirong=0;
	while (getline(InSetNode2, LineSetNode2))
	{
		ofstream SetNodeFile2(SetNodeFile2String);
		if (' ' == LineSetNode2[0])
		{
			LineSetNode2.erase(50, 4);
			SetNodeFile2 << LineSetNode2 << flush;
			panduanneirong = 1;
		}
		if ((panduanneirong == 1) && (1 == isFileExists(SetNodeFile2String)))
		{
			Matrix<int, Dynamic, Dynamic>SetNode = LinearMSTMMSolver::openDataInt(SetNodeFile2String);
			pSetNode->SetId = SetNode(0, 0);
			pSetNode->SetNodeID = SetNode.rightCols(SetNode.size() - 1);
			(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
		};
	}
	SetNodeFile2.close();
	InSetNode2.close();

	cout << ls->AllSetNode[4].SetNodeID;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//FORCE
	InForce.open(fileToOpen);
	while (getline(InForce, LineForce))
	{
		if ("*END" == LineForce)
		{
			PanduanForce = 1;
		}
		if (("*BOUNDARY_FORCE_SET" == LineForce)&&(PanduanForce == 1))
		{
			LineForce = LineForce.erase(0, 1);
			ForceBOUNDARYFileString = getFileName(LineForce);
			ForceBOUNDARYFile.open(ForceBOUNDARYFileString);
		}
		if (ForceBOUNDARYFile.is_open())
		{
			getdigit2(ForceBOUNDARYFile, LineForce);
		}
		if (("*SET_NODE_LIST_FORCE" == LineForce) && (PanduanForce == 1))
		{
			ForceBOUNDARYFile.close();
			LineForce = LineForce.erase(0, 1);
			ForceSetNodeFileString = getFileName(LineForce);
			ForceSetNodeFile.open(ForceSetNodeFileString);
		}
		if (ForceSetNodeFile.is_open())
		{
			if (' ' == LineForce[0])
			{
				ForceSetNodeFile << LineForce << " ";
			}
		}
		if (("*FORCE" == LineForce) && (PanduanForce == 1))
		{
			ForceBOUNDARYFile.close();
			ForceSetNodeFile.close();
			LineForce = LineForce.erase(0, 1);
			ForceFileString = getFileName(LineForce);
			ForceFile.open(ForceFileString);
		}
		if (ForceFile.is_open())
		{
			getdigit2(ForceFile, LineForce);

		}
		if (("*END2" == LineForce) && (PanduanForce == 1))
		{
			ForceBOUNDARYFile.close();
			ForceSetNodeFile.close();
			ForceFile.close();
			PanduanForce = 0;
		}
		
	}
	InForce.close();


     //分割结束，开始读写///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    
    //LoadBodyZ信息
	if (1 ==isFileExists(LoadBodyZFileString) )
	{
		Matrix<int, Dynamic, Dynamic>LoadBodyZ1 = LinearMSTMMSolver::openDataInt(LoadBodyZFileString);
		Matrix<double, Dynamic, Dynamic>LoadBodyZ2 = LinearMSTMMSolver::openData(LoadBodyZFileString);
        LoadBodyZ* pLoadBodyZ = new LoadBodyZ;
        pLoadBodyZ->LoadBodyZCurveID = LoadBodyZ1(0, 0);
		pLoadBodyZ->LoadCurveScaleFactor = LoadBodyZ2(0, 1);
		(void)ls->AllLoadBodyZ.insert(make_pair(pLoadBodyZ->LoadBodyZCurveID, (*pLoadBodyZ)));
        delete pLoadBodyZ;
        pLoadBodyZ = nullptr;
	};

	//LoadBodyY信息
	if (1 ==isFileExists(LoadBodyYFileString) )
	{
		Matrix<int, Dynamic, Dynamic>LoadBodyY1 = LinearMSTMMSolver::openDataInt(LoadBodyYFileString);
		Matrix<double, Dynamic, Dynamic>LoadBodyY2 = LinearMSTMMSolver::openData(LoadBodyYFileString);
		LoadBodyY* pLoadBodyY = new LoadBodyY;
        pLoadBodyY->LoadBodyYCurveID = LoadBodyY1(0, 0);
        pLoadBodyY->LoadCurveScaleFactor = LoadBodyY2(0, 1);
		(void)ls->AllLoadBodyY.insert(make_pair(pLoadBodyY->LoadBodyYCurveID, (*pLoadBodyY)));
		delete pLoadBodyY;
        pLoadBodyY = nullptr;

	};

	
	//SetNode* pSetNode = new SetNode;
    //SET集信息
	//if (1 == isFileExists(SetNodeFile1String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode1 = LinearMSTMMSolver::openDataInt(SetNodeFile1String);
	//	pSetNode->SetId = SetNodeId1;
	//	pSetNode->SetNodeID = SetNode1;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile2String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode2 = LinearMSTMMSolver::openDataInt(SetNodeFile2String);
	//	pSetNode->SetId = SetNodeId2;
	//	pSetNode->SetNodeID = SetNode2;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile3String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode3 = LinearMSTMMSolver::openDataInt(SetNodeFile3String);
	//	pSetNode->SetId = SetNodeId3;
	//	pSetNode->SetNodeID = SetNode3;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile4String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode4 = LinearMSTMMSolver::openDataInt(SetNodeFile4String);
	//	pSetNode->SetId = SetNodeId4;
	//	pSetNode->SetNodeID = SetNode4;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile5String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode5 = LinearMSTMMSolver::openDataInt(SetNodeFile5String);
	//	pSetNode->SetId = SetNodeId5;
	//	pSetNode->SetNodeID = SetNode5;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile6String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode6 = LinearMSTMMSolver::openDataInt(SetNodeFile6String);
	//	pSetNode->SetId = SetNodeId6;
	//	pSetNode->SetNodeID = SetNode6;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile7String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode7 = LinearMSTMMSolver::openDataInt(SetNodeFile7String);
	//	pSetNode->SetId = SetNodeId7;
	//	pSetNode->SetNodeID = SetNode7;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile8String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode8 = LinearMSTMMSolver::openDataInt(SetNodeFile8String);
	//	pSetNode->SetId = SetNodeId8;
	//	pSetNode->SetNodeID = SetNode8;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile9String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode9 = LinearMSTMMSolver::openDataInt(SetNodeFile9String);
	//	pSetNode->SetId = SetNodeId9;
	//	pSetNode->SetNodeID = SetNode9;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile10String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode10 = LinearMSTMMSolver::openDataInt(SetNodeFile10String);
	//	pSetNode->SetId = SetNodeId10;
	//	pSetNode->SetNodeID = SetNode10;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile11String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode11 = LinearMSTMMSolver::openDataInt(SetNodeFile11String);
	//	pSetNode->SetId = SetNodeId11;
	//	pSetNode->SetNodeID = SetNode11;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile12String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode12 = LinearMSTMMSolver::openDataInt(SetNodeFile12String);
	//	pSetNode->SetId = SetNodeId12;
	//	pSetNode->SetNodeID = SetNode12;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile13String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode13 = LinearMSTMMSolver::openDataInt(SetNodeFile13String);
	//	pSetNode->SetId = SetNodeId13;
	//	pSetNode->SetNodeID = SetNode13;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile14String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode14 = LinearMSTMMSolver::openDataInt(SetNodeFile14String);
	//	pSetNode->SetId = SetNodeId14;
	//	pSetNode->SetNodeID = SetNode14;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile15String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode15 = LinearMSTMMSolver::openDataInt(SetNodeFile15String);
	//	pSetNode->SetId = SetNodeId15;
	//	pSetNode->SetNodeID = SetNode15;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile16String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode16 = LinearMSTMMSolver::openDataInt(SetNodeFile16String);
	//	pSetNode->SetId = SetNodeId16;
	//	pSetNode->SetNodeID = SetNode16;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile17String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode17 = LinearMSTMMSolver::openDataInt(SetNodeFile17String);
	//	pSetNode->SetId = SetNodeId17;
	//	pSetNode->SetNodeID = SetNode17;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile18String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode18 = LinearMSTMMSolver::openDataInt(SetNodeFile18String);
	//	pSetNode->SetId = SetNodeId18;
	//	pSetNode->SetNodeID = SetNode18;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile19String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode19 = LinearMSTMMSolver::openDataInt(SetNodeFile19String);
	//	pSetNode->SetId = SetNodeId19;
	//	pSetNode->SetNodeID = SetNode19;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile20String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode20 = LinearMSTMMSolver::openDataInt(SetNodeFile20String);
	//	pSetNode->SetId = SetNodeId20;
	//	pSetNode->SetNodeID = SetNode20;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile21String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode21 = LinearMSTMMSolver::openDataInt(SetNodeFile21String);
	//	pSetNode->SetId = SetNodeId21;
	//	pSetNode->SetNodeID = SetNode21;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile22String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode22 = LinearMSTMMSolver::openDataInt(SetNodeFile22String);
	//	pSetNode->SetId = SetNodeId22;
	//	pSetNode->SetNodeID = SetNode22;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile23String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode23 = LinearMSTMMSolver::openDataInt(SetNodeFile23String);
	//	pSetNode->SetId = SetNodeId23;
	//	pSetNode->SetNodeID = SetNode23;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile24String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode24 = LinearMSTMMSolver::openDataInt(SetNodeFile24String);
	//	pSetNode->SetId = SetNodeId24;
	//	pSetNode->SetNodeID = SetNode24;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile25String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode25 = LinearMSTMMSolver::openDataInt(SetNodeFile25String);
	//	pSetNode->SetId = SetNodeId25;
	//	pSetNode->SetNodeID = SetNode25;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile26String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode26 = LinearMSTMMSolver::openDataInt(SetNodeFile26String);
	//	pSetNode->SetId = SetNodeId26;
	//	pSetNode->SetNodeID = SetNode26;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile27String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode27 = LinearMSTMMSolver::openDataInt(SetNodeFile27String);
	//	pSetNode->SetId = SetNodeId27;
	//	pSetNode->SetNodeID = SetNode27;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile28String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode28 = LinearMSTMMSolver::openDataInt(SetNodeFile28String);
	//	pSetNode->SetId = SetNodeId28;
	//	pSetNode->SetNodeID = SetNode28;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile29String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode29 = LinearMSTMMSolver::openDataInt(SetNodeFile29String);
	//	pSetNode->SetId = SetNodeId29;
	//	pSetNode->SetNodeID = SetNode29;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	//if (1 == isFileExists(SetNodeFile30String))
	//{
	//	Matrix<int, Dynamic, Dynamic>SetNode30 = LinearMSTMMSolver::openDataInt(SetNodeFile30String);
	//	pSetNode->SetId = SetNodeId30;
	//	pSetNode->SetNodeID = SetNode30;
	//	(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
	//};
	delete pSetNode;
    pSetNode = nullptr;


    SetSegmentNode* pSegment = new SetSegmentNode;
    //SegmentSet信息
	if (1 == isFileExists(SegmentSetFile1String))
	{
		Matrix<int, Dynamic, Dynamic>SegmentSet1 = LinearMSTMMSolver::openDataInt(SegmentSetFile1String);
		pSegment->SetSegmentId = SegmentSetId1;
		pSegment->SetSegmentNodeID = SegmentSet1;
		(void)ls->AllSetSegment.insert(make_pair(pSegment->SetSegmentId, (*pSegment)));
	};
	if (1 == isFileExists(SegmentSetFile2String))
	{
		Matrix<int, Dynamic, Dynamic>SegmentSet2 = LinearMSTMMSolver::openDataInt(SegmentSetFile2String);
		pSegment->SetSegmentId = SegmentSetId2;
		pSegment->SetSegmentNodeID = SegmentSet2;
		(void)ls->AllSetSegment.insert(make_pair(pSegment->SetSegmentId, (*pSegment)));
	};
	if (1 == isFileExists(SegmentSetFile3String))
	{
		Matrix<int, Dynamic, Dynamic>SegmentSet3 = LinearMSTMMSolver::openDataInt(SegmentSetFile3String);
		pSegment->SetSegmentId = SegmentSetId3;
		pSegment->SetSegmentNodeID = SegmentSet3;
		(void)ls->AllSetSegment.insert(make_pair(pSegment->SetSegmentId, (*pSegment)));
	};
	if (1 == isFileExists(SegmentSetFile4String))
	{
		Matrix<int, Dynamic, Dynamic>SegmentSet4 = LinearMSTMMSolver::openDataInt(SegmentSetFile4String);
		pSegment->SetSegmentId = SegmentSetId4;
		pSegment->SetSegmentNodeID = SegmentSet4;
		(void)ls->AllSetSegment.insert(make_pair(pSegment->SetSegmentId, (*pSegment)));
	};
	if (1 == isFileExists(SegmentSetFile5String))
	{
		Matrix<int, Dynamic, Dynamic>SegmentSet5 = LinearMSTMMSolver::openDataInt(SegmentSetFile5String);
		pSegment->SetSegmentId = SegmentSetId5;
		pSegment->SetSegmentNodeID = SegmentSet5;
		(void)ls->AllSetSegment.insert(make_pair(pSegment->SetSegmentId, (*pSegment)));
	};
	if (1 == isFileExists(SegmentSetFile6String))
	{
		Matrix<int, Dynamic, Dynamic>SegmentSet6 = LinearMSTMMSolver::openDataInt(SegmentSetFile6String);
		pSegment->SetSegmentId = SegmentSetId6;
		pSegment->SetSegmentNodeID = SegmentSet6;
		(void)ls->AllSetSegment.insert(make_pair(pSegment->SetSegmentId, (*pSegment)));
	};

    delete pSegment;
    pSegment = nullptr;

    //Part 信息
    if ( 1==isFileExists(PartFileString) )
    {
        Matrix<int, Dynamic, Dynamic>PartImformation = LinearMSTMMSolver::openDataInt(PartFileString);
        Part* IP = new Part;
        for (int i = 0; i < PartImformation.rows(); i++)
        {
			IP->Pid = PartImformation(i, 0);
			IP->SectionID = PartImformation(i, 1);
			IP->Mid = PartImformation(i, 2);
			(void)ls->AllPart.insert(make_pair(IP->Pid, (*IP)));
        };
        delete IP;
        IP = nullptr;

    }

    //Sec_Beam信息
    if ( 1==isFileExists(SecBeamFileString) )
    {
        Matrix<int, Dynamic, Dynamic>SecBImformation1 = LinearMSTMMSolver::openDataInt(SecBeamFileString);
        Matrix<double, Dynamic, Dynamic>SecBImformation2 = LinearMSTMMSolver::openData(SecBeamFileString);
        //cout << SecBImformation2 << endl;
        sectionbeam* ISB = new sectionbeam;
        /*lsmap* ls = new lsmap;*/
        for (int i = 0; i < SecBImformation2.rows(); i++)
        {
            ISB->secidbeam = SecBImformation1(i, 1);
            ISB->TS = SecBImformation2(i, 5);
            ISB->TT = SecBImformation2(i, 6);
			(void)ls->AllSectionbeam.insert(make_pair(ISB->secidbeam, (*ISB)));
        }
        delete ISB;
        ISB = nullptr;
    };


    //Sec_Shell信息
    if ( 1==isFileExists(SecShellFileString) )
    {
        Matrix<int, Dynamic, Dynamic>SecSHImformation1 = LinearMSTMMSolver::openDataInt(SecShellFileString);
        Matrix<double, Dynamic, Dynamic>SecSHImformation2 = LinearMSTMMSolver::openData(SecShellFileString);
        sectionshell* ISSH = new sectionshell;
        //cout << SecSHImformation1;
        /*lsmap* ls = new lsmap;*/
        if (SecSHImformation2.cols() == 5)
        {
			for (int i = 0; i < SecSHImformation2.rows(); i++)
			{
				ISSH->secidshell = SecSHImformation1(i, 0);
				ISSH->T1 = SecSHImformation2(i, 1);
				ISSH->T2 = SecSHImformation2(i, 2);
				ISSH->T3 = SecSHImformation2(i, 3);
				ISSH->T4 = SecSHImformation2(i, 4);
				(void)ls->AllSectionshell.insert(make_pair(ISSH->secidshell, (*ISSH)));

			};
        }
        else
        {
			for (int i = 0; i < SecSHImformation2.rows(); i++)
			{
				ISSH->secidshell = SecSHImformation1(i, 0);
				ISSH->T1 = SecSHImformation2(i, 2);
				ISSH->T2 = SecSHImformation2(i, 3);
				ISSH->T3 = SecSHImformation2(i, 4);
				ISSH->T4 = SecSHImformation2(i, 5);
				(void)ls->AllSectionshell.insert(make_pair(ISSH->secidshell, (*ISSH)));

			};
        }
        delete ISSH;
        ISSH = nullptr;

    }

    //Velocity 初速度信息
    if ( 1==isFileExists(NodeVelocityFileString) )
    {
        Matrix<int, Dynamic, Dynamic>NodeVelocityFileImformation1 = LinearMSTMMSolver::openDataInt(NodeVelocityFileString);
        Matrix<double, Dynamic, Dynamic>NodeVelocityFileImformation2 = LinearMSTMMSolver::openData(NodeVelocityFileString);
        Velocity* IVelocity = new Velocity;
        for (int i = 0; i < NodeVelocityFileImformation1.rows(); i++)
        {
            IVelocity->SetNodeid = NodeVelocityFileImformation1(i, 0);
            IVelocity->SetType = NodeVelocityFileImformation1(i, 1);
            IVelocity->XVelocity = NodeVelocityFileImformation2(i, 2);
            IVelocity->YVelocity = NodeVelocityFileImformation2(i, 3);
            IVelocity->ZVelocity = NodeVelocityFileImformation2(i, 4);
			(void)ls->AllVelocity.insert(make_pair(IVelocity->SetNodeid, (*IVelocity)));
        }
        delete IVelocity;
        IVelocity = nullptr;

    }
    //cout << (*ls).AllVelocity[2].XVelocity << endl;

    ////写入inputdate.h//////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    InputAllDate* IAD = new InputAllDate;

    //节点信息
    if ( 1==isFileExists(NodeFileString) )
    {
        Matrix<double, Dynamic, Dynamic>NodeImformation1 = LinearMSTMMSolver::openData(NodeFileString);
        Matrix<int, Dynamic, Dynamic>NodeImformation2 = LinearMSTMMSolver::openDataInt(NodeFileString);
        InputNode* INN = new InputNode;
        for (int i = 0; i < NodeImformation1.rows(); i++)
        {
            INN->NodeID = NodeImformation2(i, 0);
            INN->NodeCoordinates = NodeImformation1.row(i).rightCols(3).adjoint();
			(void)IAD->InputAllNode.insert(make_pair(INN->NodeID, (*INN)));
        };
        //cout << (*IAD).InputAllNode[5].NodeCoordinates;
        delete INN;
        INN = nullptr;

    }

    //实体单元信息
    if (1 ==isFileExists(EleSoFileString) )
    {
        Matrix<int, Dynamic, Dynamic>EleSoImformation = LinearMSTMMSolver::openDataInt(EleSoFileString);
        /* cout << EleSoImformation;*/
        InputElement* InESo = new InputElement;
        /*  InputAllDate* IAD = new InputAllDate;*/
        //cout<< EleSoImformation.row(1).rightCols(8).adjoint();
        for (int i = 0; i < EleSoImformation.rows(); i++)
        {
            (*InESo).ElementID = EleSoImformation(i, 0);      /* cout << (*INE_SO).ElementID << endl;*/
            (*InESo).ElementTypeID = 0;
            (*InESo).MaterialID = (*ls).AllPart[EleSoImformation(i, 1)].Mid;
            (*InESo).ElementNodeID.resize(8, 1);
            (*InESo).ElementNodeID = EleSoImformation.row(i).rightCols(8).adjoint();
            (*InESo).ElementNodeCoordinates.resize(8, 3);
            for (int J = 0; J < 8; J++)
            {
                (*InESo).ElementNodeCoordinates.row(J) = (*IAD).InputAllNode[(*InESo).ElementNodeID(J, 0)].NodeCoordinates.adjoint();
            }
            /* cout << (*InESo).ElementNodeCoordinates<<endl ;*/

			(void)IAD->InputAllElement.insert(make_pair((*InESo).ElementID, (*InESo)));
        }
        delete InESo;
        InESo = nullptr;

    };

    // 壳单元信息
    if ( 1==isFileExists(EleShFileString) )
    {
        Matrix<int, Dynamic, Dynamic>EleShImformation = LinearMSTMMSolver::openDataInt(EleShFileString);
        InputElement* InESh = new InputElement;
        /*  InputAllDate* IAD = new InputAllDate;*/
        for (int i = 0; i < EleShImformation.rows(); i++)
        {
            (*InESh).ElementID = EleShImformation(i, 0);
            (*InESh).ElementTypeID = 1;
            (*InESh).MaterialID = (*ls).AllPart[EleShImformation(i, 1)].Mid;
            (*InESh).ElementNodeID.resize(4, 1);
            (*InESh).ElementNodeID = EleShImformation.row(i).rightCols(4).adjoint();
            (*InESh).ElementNodeCoordinates.resize(4, 3);
			for (int A = {0}; A < 4; A++)
            {
                (*InESh).ElementNodeCoordinates.row(A) = (*IAD).InputAllNode[(*InESh).ElementNodeID(A, 0)].NodeCoordinates.adjoint();
            }
            (*InESh).ShellGeometricParameter(0, 0) = (*ls).AllSectionshell[(*ls).AllPart[EleShImformation(i, 1)].SectionID].T1;
            (*InESh).ShellGeometricParameter(1, 0) = (*ls).AllSectionshell[(*ls).AllPart[EleShImformation(i, 1)].SectionID].T2;
            (*InESh).ShellGeometricParameter(2, 0) = (*ls).AllSectionshell[(*ls).AllPart[EleShImformation(i, 1)].SectionID].T3;
            (*InESh).ShellGeometricParameter(3, 0) = (*ls).AllSectionshell[(*ls).AllPart[EleShImformation(i, 1)].SectionID].T4;

			(void)(*IAD).InputAllElement.insert(make_pair((*InESh).ElementID, (*InESh)));
        }
        //cout << (*IAD).InputAllElement[95475].ShellGeometricParameter << endl;
        delete InESh;
        InESh = nullptr;

    };


    // 梁单元信息
    if ( 1==isFileExists(EleBFileString) )
    {
        Matrix<int, Dynamic, Dynamic>EleBImformation = LinearMSTMMSolver::openDataInt(EleBFileString);
        InputElement* InEB = new InputElement;
        /*  InputAllDate* IAD = new InputAllDate;*/
        for (int i = 0; i < EleBImformation.rows(); i++)
        {
            (*InEB).ElementID = EleBImformation(i, 0);      /* cout << (*INE).ElementID << endl;*/
            (*InEB).ElementTypeID = 2;
            (*InEB).MaterialID = (*ls).AllPart[EleBImformation(i, 1)].Mid;
            (*InEB).ElementNodeID.resize(2, 1);
            (*InEB).ElementNodeID(0, 0) = EleBImformation(i, 2);
            (*InEB).ElementNodeID(1, 0) = EleBImformation(i, 3);
            (*InEB).ReferencePoint = (*IAD).InputAllNode[EleBImformation(i, 4)].NodeCoordinates.adjoint();
            (*InEB).ElementNodeCoordinates.resize(2, 3);
            for (int j = 0; j < 2; j++)
            {
                (*InEB).ElementNodeCoordinates.row(j) = (*IAD).InputAllNode[(*InEB).ElementNodeID(j, 0)].NodeCoordinates.adjoint();
            }
            (*InEB).ElementGeometricParameter(0, 0) = (*ls).AllSectionbeam[(*ls).AllPart[EleBImformation(i, 1)].SectionID].TS;   //只有宽和高目前，SECTION文件里， ts1和ts2是宽  
            (*InEB).ElementGeometricParameter(1, 0) = (*ls).AllSectionbeam[(*ls).AllPart[EleBImformation(i, 1)].SectionID].TT;
            /* cout << (*InEB).ElementGeometricParameter<<endl;*/
			(void)(*IAD).InputAllElement.insert(make_pair((*InEB).ElementID, (*InEB)));
        }
        delete InEB;
        InEB = nullptr;

    };



    //设置初始速度，节点集
    map<int, int> NodeNumber;
	for (auto& IEDN : IAD->InputAllElement)
	{
        if ( 0==IEDN.second.ElementTypeID )
        {
            Matrix<int, 8, 1> NID = IEDN.second.ElementNodeID;
            for (int i = 0; i < 8; i++)
            {
                map<int, int>::iterator NoPo = NodeNumber.find(NID(i));
                if (NoPo == NodeNumber.end())
                {
					(void)NodeNumber.insert(make_pair(NID(i), 3));
                };
            };
        };
        if ( 2==IEDN.second.ElementTypeID )
        {
            Matrix<int, 2, 1> NID = IEDN.second.ElementNodeID;
            for (int i = 0; i < 2; i++)
            {
                NodeNumber[NID(i)] = 6;
            };
        };
        if ( 1==IEDN.second.ElementTypeID )
        {
            Matrix<int, 4, 1> NID = IEDN.second.ElementNodeID;
            for (int i = 0; i < 4; i++)
            {
                NodeNumber[NID(i)] = 6;
            };
        };
    };
    for (auto& IEDN : IAD->InputAllElement)
    {
        Matrix<int, Dynamic, 1> NodeIDq = IEDN.second.ElementNodeID;
        int Row = NodeIDq.rows();
        (void)IEDN.second.ElementBodyForce.setZero(3, 1);
        for (int NId = 0; NId < Row; NId++)
        {
			(void)IAD->InputAllNode[NodeIDq(NId, 0)].NodeAcceleration.setZero(NodeNumber[NodeIDq(NId, 0)], 1);
			(void)IAD->InputAllNode[NodeIDq(NId, 0)].NodeVelocity.setZero(NodeNumber[NodeIDq(NId, 0)], 1);
			(void)IAD->InputAllNode[NodeIDq(NId, 0)].NodeDisplacement.setZero(NodeNumber[NodeIDq(NId, 0)], 1);
        };
    };
     //赋速度
    if ( 1==isFileExists(NodeVelocityFileString) )
    {
        for (auto& it : ls->AllVelocity)
        {
			const int setrow = ls->AllSetNode[it.first].SetNodeID.rows();
			const int setcol = ls->AllSetNode[it.first].SetNodeID.cols();
			// cout << setrow;
			for (int i = 0; i < setrow; i++)
			{
				for (int j = 0; j < setcol; j++)
				{
					if (IAD->InputAllNode[ls->AllSetNode[it.second.SetNodeid].SetNodeID(i, j)].NodeVelocity.rows() != 0)
					{
					IAD->InputAllNode[ls->AllSetNode[it.second.SetNodeid].SetNodeID(i, j)].NodeVelocity(0, 0) = it.second.XVelocity;
					IAD->InputAllNode[ls->AllSetNode[it.second.SetNodeid].SetNodeID(i, j)].NodeVelocity(1, 0) = it.second.YVelocity;
					IAD->InputAllNode[ls->AllSetNode[it.second.SetNodeid].SetNodeID(i, j)].NodeVelocity(2, 0) = it.second.ZVelocity;
					};
				}
			}
        }
        //cout << IAD->InputAllNode[108552].NodeVelocity;
    }	
    //赋加速度
	if (1 ==isFileExists(LoadBodyZFileString) )
	{
		for (auto& itLoad : ls->AllLoadBodyZ)
		{
			for (auto &it: IAD->InputAllElement)
			{
                it.second.ElementBodyForce(2, 0)=itLoad.second.LoadCurveScaleFactor;			
			} 
            							
		}
		//cout << IAD->InputAllNode[108552].NodeVelocity;
	}
	if (1 ==isFileExists(LoadBodyYFileString) )
	{
		for (auto& itLoad : ls->AllLoadBodyY)
		{
			for (auto& it : IAD->InputAllElement)
		    {
		    	it.second.ElementBodyForce(1, 0) = itLoad.second.LoadCurveScaleFactor;
		    }		
		}
        //cout << IAD->InputAllElement[2].ElementBodyForce;
	}

    //1号弹性材料信息
    if ( 1==isFileExists(ElaFileString) )
    {
        Matrix<double, Dynamic, Dynamic>MaEImformation1 = LinearMSTMMSolver::openData(ElaFileString);
        Matrix<int, Dynamic, Dynamic>MaEImformation2 = LinearMSTMMSolver::openDataInt(ElaFileString);
        /*cout << MaEImformation1 << endl ;*/
        InputMaterial* InME = new InputMaterial;
        /*  InputAllDate* IAD = new InputAllDate;*/
        for (int i = 0; i < MaEImformation1.rows(); i++)
        {
            (*InME).MaterialID = MaEImformation2(i, 0);
            (*InME).MaterialType = 1;
            (*InME).Density = MaEImformation1(i, 1);
            (*InME).ElasticModulu = MaEImformation1(i, 2);
            (*InME).PoissonsRatio = MaEImformation1(i, 3);

			(void)(*IAD).InputAllMaterial.insert(make_pair((*InME).MaterialID, (*InME)));
        }
        delete InME;
        InME = nullptr;

        /* cout << (*IAD).InputAllMaterial[6].Density;*/
    }

    //3号塑性材料信息
    if (1 ==isFileExists(PlaFileString) )
    {
        Matrix<double, Dynamic, Dynamic>MaPImformation1 = LinearMSTMMSolver::openData(PlaFileString);
        Matrix<int, Dynamic, Dynamic>MaPImformation2 = LinearMSTMMSolver::openDataInt(PlaFileString);
        /* cout << MaPImformation1 << endl;*/
         //cout << MaPImformation2 << endl;
        InputMaterial* InMP = new InputMaterial;
        /*  InputAllDate* IAD = new InputAllDate;*/
        for (int i = 0; i < MaPImformation1.rows(); i++)
        {
            (*InMP).MaterialID = MaPImformation2(i, 0);
            (*InMP).MaterialType = 2;   //待定
            (*InMP).Density = MaPImformation1(i, 1);
            (*InMP).ElasticModulu = MaPImformation1(i, 2);
            (*InMP).PoissonsRatio = MaPImformation1(i, 3);
            (*InMP).InitialYieldStress = MaPImformation1(i, 4);
            (*InMP).TangentialModulus = MaPImformation1(i, 5);
            //(*InMP).MixedHardeningParameter = MaPImformation1(i, 6);    //混合硬化参数,3号塑性材料。BETA Hardening parameter, 0-1.
            (void)(*IAD).InputAllMaterial.insert(make_pair((*InMP).MaterialID, (*InMP)));
        }
        delete InMP;
        InMP = nullptr;

        //cout << (*IAD).InputAllMaterial[7].InitialYieldStress;
    }


    //contact 信息
	if ( 1==isFileExists(ContactFileString) )
	{
        //Contact 关键字信息
		Matrix<double, Dynamic, Dynamic>ContactImformation = LinearMSTMMSolver::openData(ContactFileString);
		Matrix<int, Dynamic, Dynamic>ContactImformation2 = LinearMSTMMSolver::openDataInt(ContactFileString);		
        //cout << ContactImformation;
		for (int i = 0; i < ContactImformation.rows(); i++)
		{
            InputContact* InCta = new InputContact;
			InCta->ContactNumber = ContactImformation2(i, 0);
			InCta->ContactType = 0;
            if ( (0==ContactImformation(i, 5))  &&  (0==ContactImformation(i, 6)) )
            {
                InCta->FrictionJudgment = 1;
            }
            else
            {
                InCta->FrictionJudgment = 0;
            };
            //节点集号
			InCta->SlaveNodeSetId = ContactImformation2(i, 1);
			InCta->MasterNodeSetId = ContactImformation2(i, 2);
			InCta->SlaveNodeSetType = ContactImformation2(i, 3);
			InCta->MasterNodeSetType = ContactImformation2(i, 4);
            //摩擦系数
			InCta->StaticFrictionCoefficient = ContactImformation(i, 5);
			InCta->DynamicFrictionCoefficient = ContactImformation(i, 6);
            //主从面节点号
            for (int j = 0; j < ls->AllSetSegment[InCta->MasterNodeSetId].SetSegmentNodeID.rows(); j++)
            {
				(void)InCta->MasterContactNode.insert(make_pair((j + 1), ls->AllSetSegment[InCta->MasterNodeSetId].SetSegmentNodeID.row(j).adjoint()));
            };
            for (int k = 0; k < ls->AllSetNode[InCta->SlaveNodeSetId].SetNodeID.rows(); k++)
            {
				(void)InCta->SlaveContactNode.insert(make_pair((k + 1), ls->AllSetNode[InCta->SlaveNodeSetId].SetNodeID.row(k).adjoint()));
            };
			(void)IAD->InputAllContact.insert(make_pair(InCta->ContactNumber, (*InCta)));
            delete InCta;
            InCta = nullptr;

		}
		
	}

	InputConstraint* InConstraint = new InputConstraint;
    //边界约束条件信息
    if ( 1==isFileExists(BoundaryFileString) )
    {
        Matrix<int, Dynamic, Dynamic>BoundaryIntImformation = LinearMSTMMSolver::openDataInt(BoundaryFileString);
        //Matrix<double, Dynamic, Dynamic>BoundaryDouImformation = LinearMSTMMSolver::openData(BoundaryFileString);
      
        /*  InputAllDate* IAD = new InputAllDate;*/
        if (  7==BoundaryIntImformation.cols())
        {
        for (int i = 0; i < BoundaryIntImformation.rows(); i++)
        {
            (*InConstraint).ConstraintType = 0;
            (*InConstraint).ConstraintNodeID = BoundaryIntImformation(i, 0);
			if ((0 == BoundaryIntImformation(i, 4) )&& (0 == BoundaryIntImformation(i, 5)) &&( 0 == BoundaryIntImformation(i, 6)))
			{
				if ((1 == BoundaryIntImformation(i, 1)) &&( 1== BoundaryIntImformation(i, 2) ) &&  (1== BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2, 3;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) &&( 0== BoundaryIntImformation(i, 2) ) &&  (1== BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(2, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 3;
					(*InConstraint).NodeExternalConstraint.resize(2, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) &&( 1== BoundaryIntImformation(i, 2) ) &&  (0== BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(2, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2;
					(*InConstraint).NodeExternalConstraint.resize(2, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) &&( 0== BoundaryIntImformation(i, 2) ) &&  (0== BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(1, 1);
					(*InConstraint).ConstraintNodeDofID << 1;
					(*InConstraint).NodeExternalConstraint.resize(1, 1);
					(*InConstraint).NodeExternalConstraint << 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) &&( 1== BoundaryIntImformation(i, 2) ) &&  (1== BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(2, 1);
					(*InConstraint).ConstraintNodeDofID << 2, 3;
					(*InConstraint).NodeExternalConstraint.resize(2, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) &&( 0== BoundaryIntImformation(i, 2) ) &&  (1== BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(1, 1);
					(*InConstraint).ConstraintNodeDofID << 3;
					(*InConstraint).NodeExternalConstraint.resize(1, 1);
					(*InConstraint).NodeExternalConstraint << 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) &&( 1== BoundaryIntImformation(i, 2) ) &&  (0== BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(1, 1);
					(*InConstraint).ConstraintNodeDofID << 2;
					(*InConstraint).NodeExternalConstraint.resize(1, 1);
					(*InConstraint).NodeExternalConstraint << 0;
				}
				/* if (BoundaryIntImformation(i, 1) == 0 && BoundaryIntImformation(i, 2) == 0 && BoundaryIntImformation(i, 3) == 0)
				 {
					 (*InConstraint).ConstraintNodeDofID <<0;
				 }*/
			}
			if ((0 == BoundaryIntImformation(i, 4) )&& (1 == BoundaryIntImformation(i, 5)) &&( 0 == BoundaryIntImformation(i, 6)))
			{
				if ((1 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(4, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2, 3, 5;
					(*InConstraint).NodeExternalConstraint.resize(4, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 3, 5;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2, 5;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(2, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 5;
					(*InConstraint).NodeExternalConstraint.resize(2, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 2, 3, 5;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(2, 1);
					(*InConstraint).ConstraintNodeDofID << 3, 5;
					(*InConstraint).NodeExternalConstraint.resize(2, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(2, 1);
					(*InConstraint).ConstraintNodeDofID << 2, 5;
					(*InConstraint).NodeExternalConstraint.resize(2, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1) )&& (0 == BoundaryIntImformation(i, 2)) &&( 0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(1, 1);
					(*InConstraint).ConstraintNodeDofID << 5;
					(*InConstraint).NodeExternalConstraint.resize(1, 1);
					(*InConstraint).NodeExternalConstraint << 0;
				}
			}
			if ((0 == BoundaryIntImformation(i, 4) )&& (0 == BoundaryIntImformation(i, 5)) &&( 1 == BoundaryIntImformation(i, 6)))
			{
				if ((1 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(4, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2, 3, 6;
					(*InConstraint).NodeExternalConstraint.resize(4, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 3, 6;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2, 6;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(2, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 6;
					(*InConstraint).NodeExternalConstraint.resize(2, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 2, 3, 6;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(2, 1);
					(*InConstraint).ConstraintNodeDofID << 3, 6;
					(*InConstraint).NodeExternalConstraint.resize(2, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(2, 1);
					(*InConstraint).ConstraintNodeDofID << 2, 6;
					(*InConstraint).NodeExternalConstraint.resize(2, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(1, 1);
					(*InConstraint).ConstraintNodeDofID << 6;
					(*InConstraint).NodeExternalConstraint.resize(1, 1);
					(*InConstraint).NodeExternalConstraint << 0;
				}
			}
			if ((0 == BoundaryIntImformation(i, 4) )&& (1 == BoundaryIntImformation(i, 5)) &&( 1 == BoundaryIntImformation(i, 6)))
			{
				if ((1 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(5, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2, 3, 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(5, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(4, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 3, 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(4, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(4, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2, 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(4, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(4, 1);
					(*InConstraint).ConstraintNodeDofID << 2, 3, 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(4, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 3, 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 2, 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(2, 1);
					(*InConstraint).ConstraintNodeDofID << 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(2, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0;
				}
			}
			if ((1 == BoundaryIntImformation(i, 4) )&& (0 == BoundaryIntImformation(i, 5)) &&( 0 == BoundaryIntImformation(i, 6)))
			{
				if ((1 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(4, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2, 3, 4;
					(*InConstraint).NodeExternalConstraint.resize(4, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 3, 4;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2, 4;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(2, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 4;
					(*InConstraint).NodeExternalConstraint.resize(2, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 2, 3, 4;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(2, 1);
					(*InConstraint).ConstraintNodeDofID << 3, 4;
					(*InConstraint).NodeExternalConstraint.resize(2, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(2, 1);
					(*InConstraint).ConstraintNodeDofID << 2, 4;
					(*InConstraint).NodeExternalConstraint.resize(2, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(1, 1);
					(*InConstraint).ConstraintNodeDofID << 4;
					(*InConstraint).NodeExternalConstraint.resize(1, 1);
					(*InConstraint).NodeExternalConstraint << 0;
				}
			}
			if ((1 == BoundaryIntImformation(i, 4) )&& (1 == BoundaryIntImformation(i, 5)) &&( 0 == BoundaryIntImformation(i, 6)))
			{
				if ((1 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(5, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2, 3, 4, 5;
					(*InConstraint).NodeExternalConstraint.resize(5, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(4, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 3, 4, 5;
					(*InConstraint).NodeExternalConstraint.resize(4, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(4, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2, 4, 5;
					(*InConstraint).NodeExternalConstraint.resize(4, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 4, 5;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(4, 1);
					(*InConstraint).ConstraintNodeDofID << 2, 3, 4, 5;
					(*InConstraint).NodeExternalConstraint.resize(4, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 3, 4, 5;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 2, 4, 5;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(2, 1);
					(*InConstraint).ConstraintNodeDofID << 4, 5;
					(*InConstraint).NodeExternalConstraint.resize(2, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0;
				}
			}
			if ((1 == BoundaryIntImformation(i, 4) )&& (1 == BoundaryIntImformation(i, 5)) &&( 1 == BoundaryIntImformation(i, 6)))
			{
				if ((1 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(6, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2, 3, 4, 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(6, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(5, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 3, 4, 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(5, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(5, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2, 4, 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(5, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(4, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 4, 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(4, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(5, 1);
					(*InConstraint).ConstraintNodeDofID << 2, 3, 4, 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(5, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(4, 1);
					(*InConstraint).ConstraintNodeDofID << 3, 4, 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(4, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(4, 1);
					(*InConstraint).ConstraintNodeDofID << 2, 4, 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(4, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 4, 5, 6;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
			}
			if ((1 == BoundaryIntImformation(i, 4) )&& (0 == BoundaryIntImformation(i, 5)) &&( 1 == BoundaryIntImformation(i, 6)))
            {
				if ((1 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(5, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2, 3, 4, 6;
					(*InConstraint).NodeExternalConstraint.resize(5, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(4, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 3, 4, 6;
					(*InConstraint).NodeExternalConstraint.resize(4, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(4, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 2, 4, 6;
					(*InConstraint).NodeExternalConstraint.resize(4, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
				}
				if ((1 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 1, 4, 6;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(4, 1);
					(*InConstraint).ConstraintNodeDofID << 2, 3, 4, 6;
					(*InConstraint).NodeExternalConstraint.resize(4, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 3, 4, 6;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
				{
					(*InConstraint).ConstraintNodeDofID.resize(3, 1);
					(*InConstraint).ConstraintNodeDofID << 2, 4, 6;
					(*InConstraint).NodeExternalConstraint.resize(3, 1);
					(*InConstraint).NodeExternalConstraint << 0, 0, 0;
				}
				if ((0 == BoundaryIntImformation(i, 1)) && (0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)))
                {
                    (*InConstraint).ConstraintNodeDofID.resize(2, 1);
                    (*InConstraint).ConstraintNodeDofID << 4, 6;
                    (*InConstraint).NodeExternalConstraint.resize(2, 1);
                    (*InConstraint).NodeExternalConstraint << 0, 0;
                }
            }
			(void)(*IAD).InputAllConstraint.insert(make_pair((*InConstraint).ConstraintNodeID, (*InConstraint)));
        }
        }
         if( 8==BoundaryIntImformation.cols() )
         {
             for (int i = 0; i < BoundaryIntImformation.rows(); i++)
             {
                 (*InConstraint).ConstraintType = 0;
                 (*InConstraint).ConstraintNodeID = BoundaryIntImformation(i, 0);
				 if ((0 == BoundaryIntImformation(i, 5)) && (0 == BoundaryIntImformation(i, 6)) && (0 == BoundaryIntImformation(i, 7)))
				 {
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2, 3;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(2, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 3;
						 (*InConstraint).NodeExternalConstraint.resize(2, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(2, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2;
						 (*InConstraint).NodeExternalConstraint.resize(2, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(1, 1);
						 (*InConstraint).ConstraintNodeDofID << 1;
						 (*InConstraint).NodeExternalConstraint.resize(1, 1);
						 (*InConstraint).NodeExternalConstraint << 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(2, 1);
						 (*InConstraint).ConstraintNodeDofID << 2, 3;
						 (*InConstraint).NodeExternalConstraint.resize(2, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(1, 1);
						 (*InConstraint).ConstraintNodeDofID << 3;
						 (*InConstraint).NodeExternalConstraint.resize(1, 1);
						 (*InConstraint).NodeExternalConstraint << 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(1, 1);
						 (*InConstraint).ConstraintNodeDofID << 2;
						 (*InConstraint).NodeExternalConstraint.resize(1, 1);
						 (*InConstraint).NodeExternalConstraint << 0;
					 }
					 /* if (BoundaryIntImformation(i, 1) == 0 && BoundaryIntImformation(i, 2) == 0 && BoundaryIntImformation(i, 3) == 0)
					  {
						  (*InConstraint).ConstraintNodeDofID <<0;
					  }*/
				 }
				 if ((0 == BoundaryIntImformation(i, 5)) && (1 == BoundaryIntImformation(i, 6)) && (0 == BoundaryIntImformation(i, 7)))
				 {
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(4, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2, 3, 5;
						 (*InConstraint).NodeExternalConstraint.resize(4, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 3, 5;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2, 5;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(2, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 5;
						 (*InConstraint).NodeExternalConstraint.resize(2, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 2, 3, 5;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(2, 1);
						 (*InConstraint).ConstraintNodeDofID << 3, 5;
						 (*InConstraint).NodeExternalConstraint.resize(2, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(2, 1);
						 (*InConstraint).ConstraintNodeDofID << 2, 5;
						 (*InConstraint).NodeExternalConstraint.resize(2, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(1, 1);
						 (*InConstraint).ConstraintNodeDofID << 5;
						 (*InConstraint).NodeExternalConstraint.resize(1, 1);
						 (*InConstraint).NodeExternalConstraint << 0;
					 }
				 }
				 if ((0 == BoundaryIntImformation(i, 5)) && (0 == BoundaryIntImformation(i, 6)) && (1 == BoundaryIntImformation(i, 7)))
				 {
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(4, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2, 3, 6;
						 (*InConstraint).NodeExternalConstraint.resize(4, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 3, 6;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2, 6;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(2, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 6;
						 (*InConstraint).NodeExternalConstraint.resize(2, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 2, 3, 6;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(2, 1);
						 (*InConstraint).ConstraintNodeDofID << 3, 6;
						 (*InConstraint).NodeExternalConstraint.resize(2, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(2, 1);
						 (*InConstraint).ConstraintNodeDofID << 2, 6;
						 (*InConstraint).NodeExternalConstraint.resize(2, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(1, 1);
						 (*InConstraint).ConstraintNodeDofID << 6;
						 (*InConstraint).NodeExternalConstraint.resize(1, 1);
						 (*InConstraint).NodeExternalConstraint << 0;
					 }
				 }
				 if ((0 == BoundaryIntImformation(i, 5)) && (1 == BoundaryIntImformation(i, 6)) && (1 == BoundaryIntImformation(i, 7)))
				 {
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(5, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2, 3, 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(5, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(4, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 3, 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(4, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(4, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2, 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(4, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(4, 1);
						 (*InConstraint).ConstraintNodeDofID << 2, 3, 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(4, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 3, 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 2, 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(2, 1);
						 (*InConstraint).ConstraintNodeDofID << 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(2, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0;
					 }
				 }
				 if ((1 == BoundaryIntImformation(i, 5)) && (0 == BoundaryIntImformation(i, 6)) && (0 == BoundaryIntImformation(i, 7)))
				 {
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(4, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2, 3, 4;
						 (*InConstraint).NodeExternalConstraint.resize(4, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 3, 4;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2, 4;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(2, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 4;
						 (*InConstraint).NodeExternalConstraint.resize(2, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 2, 3, 4;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(2, 1);
						 (*InConstraint).ConstraintNodeDofID << 3, 4;
						 (*InConstraint).NodeExternalConstraint.resize(2, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(2, 1);
						 (*InConstraint).ConstraintNodeDofID << 2, 4;
						 (*InConstraint).NodeExternalConstraint.resize(2, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(1, 1);
						 (*InConstraint).ConstraintNodeDofID << 4;
						 (*InConstraint).NodeExternalConstraint.resize(1, 1);
						 (*InConstraint).NodeExternalConstraint << 0;
					 }
				 }
				 if ((1 == BoundaryIntImformation(i, 5)) && (1 == BoundaryIntImformation(i, 6)) && (0 == BoundaryIntImformation(i, 7)))
				 {
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(5, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2, 3, 4, 5;
						 (*InConstraint).NodeExternalConstraint.resize(5, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(4, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 3, 4, 5;
						 (*InConstraint).NodeExternalConstraint.resize(4, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(4, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2, 4, 5;
						 (*InConstraint).NodeExternalConstraint.resize(4, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 4, 5;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(4, 1);
						 (*InConstraint).ConstraintNodeDofID << 2, 3, 4, 5;
						 (*InConstraint).NodeExternalConstraint.resize(4, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 3, 4, 5;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 2, 4, 5;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(2, 1);
						 (*InConstraint).ConstraintNodeDofID << 4, 5;
						 (*InConstraint).NodeExternalConstraint.resize(2, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0;
					 }
				 }
				 if ((1 == BoundaryIntImformation(i, 5)) && (1 == BoundaryIntImformation(i, 6)) && (1 == BoundaryIntImformation(i, 7)))
				 {
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(6, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2, 3, 4, 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(6, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(5, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 3, 4, 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(5, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(5, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2, 4, 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(5, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(4, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 4, 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(4, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(5, 1);
						 (*InConstraint).ConstraintNodeDofID << 2, 3, 4, 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(5, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(4, 1);
						 (*InConstraint).ConstraintNodeDofID << 3, 4, 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(4, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(4, 1);
						 (*InConstraint).ConstraintNodeDofID << 2, 4, 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(4, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 4, 5, 6;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
				 }
				 if ((1 == BoundaryIntImformation(i, 5)) && (0 == BoundaryIntImformation(i, 6)) && (1 == BoundaryIntImformation(i, 7)))
                 {
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(5, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2, 3, 4, 6;
						 (*InConstraint).NodeExternalConstraint.resize(5, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(4, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 3, 4, 6;
						 (*InConstraint).NodeExternalConstraint.resize(4, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(4, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 2, 4, 6;
						 (*InConstraint).NodeExternalConstraint.resize(4, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
					 }
					 if ((1 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 1, 4, 6;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(4, 1);
						 (*InConstraint).ConstraintNodeDofID << 2, 3, 4, 6;
						 (*InConstraint).NodeExternalConstraint.resize(4, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (1 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 3, 4, 6;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (1 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
					 {
						 (*InConstraint).ConstraintNodeDofID.resize(3, 1);
						 (*InConstraint).ConstraintNodeDofID << 2, 4, 6;
						 (*InConstraint).NodeExternalConstraint.resize(3, 1);
						 (*InConstraint).NodeExternalConstraint << 0, 0, 0;
					 }
					 if ((0 == BoundaryIntImformation(i, 2)) && (0 == BoundaryIntImformation(i, 3)) && (0 == BoundaryIntImformation(i, 4)))
                     {
                         (*InConstraint).ConstraintNodeDofID.resize(2, 1);
                         (*InConstraint).ConstraintNodeDofID << 4, 6;
                         (*InConstraint).NodeExternalConstraint.resize(2, 1);
                         (*InConstraint).NodeExternalConstraint << 0, 0;
                     }
                 }

				 (void)(*IAD).InputAllConstraint.insert(make_pair((*InConstraint).ConstraintNodeID, (*InConstraint)));
             }
         }

        /* auto pr = (*IAD).InputAllConstraint.find(173546);
         if (pr != std::end((*IAD).InputAllConstraint))
         {
         std:cout << pr->first << " is " <<endl<< pr->second.ConstraintNodeDofID << endl;
         }*/
    }

    //刚性墙
    if ( 1==isFileExists(RigidWallFileString) )
    {
        Matrix<double, Dynamic, Dynamic>RigidWallImformation1 = LinearMSTMMSolver::openData(RigidWallFileString);
        Matrix<int, Dynamic, Dynamic>RigidWallImformation2 = LinearMSTMMSolver::openDataInt(RigidWallFileString);
        for (int i = 0; i < RigidWallImformation1.rows(); i++)
        {
			InputRigidWallContact* InRigidWall = new InputRigidWallContact;
            InRigidWall->ContactNumber = RigidWallImformation2(i, 0);
            InRigidWall->NodeSetID = RigidWallImformation2(i, 1);
            if ( 0==RigidWallImformation1(i, 8)  )
            {
                InRigidWall->FrictionJudgment = 1;
            }
            else
            {
                InRigidWall->FrictionJudgment = 0;
            }
             InRigidWall->Length = RigidWallImformation1(i, 12);
             InRigidWall->Width = RigidWallImformation1(i, 13);
             InRigidWall->FrictionCoefficient = RigidWallImformation1(i, 8);
             InRigidWall->RigidWallNormal(0, 0) = RigidWallImformation1(i, 5);
             InRigidWall->RigidWallNormal(1, 0) = RigidWallImformation1(i, 6);
             InRigidWall->RigidWallNormal(2, 0) = RigidWallImformation1(i, 7);
             InRigidWall->RigidWallorigin(0, 0) = RigidWallImformation1(i, 2);
             InRigidWall->RigidWallorigin(1, 0) = RigidWallImformation1(i, 3);
             InRigidWall->RigidWallorigin(2, 0) = RigidWallImformation1(i, 4);
             InRigidWall->RigidWallTangential(0, 0) = RigidWallImformation1(i, 9);
             InRigidWall->RigidWallTangential(1, 0) = RigidWallImformation1(i, 10);
             InRigidWall->RigidWallTangential(2, 0) = RigidWallImformation1(i, 11);                     
			 (void)InRigidWall->SlaveContactNode.insert(make_pair(RigidWallImformation2(i, 1),ls->AllSetNode[RigidWallImformation2(i, 1)].SetNodeID.adjoint()));
			 (void)IAD->InputAllRigidContact.insert(make_pair(InRigidWall->ContactNumber, (*InRigidWall)));
            delete InRigidWall;
            InRigidWall = nullptr;

        }
       
    }
    //cout << IAD->InputAllNode[IAD->InputAllRigidContact[6].SlaveContactNode[3](0,0)].NodeID;
    
	//定载荷约束信息
	if (1 == isFileExists(ForceBOUNDARYFileString))
	{
		Matrix<int, Dynamic, Dynamic>ForceBOUNDARYImformation = LinearMSTMMSolver::openDataInt(ForceBOUNDARYFileString);
		Matrix<int, Dynamic, Dynamic>ForceSetNodeImformation = LinearMSTMMSolver::openDataInt(ForceSetNodeFileString);
		Matrix<double, Dynamic, Dynamic>ForceFileImformation = LinearMSTMMSolver::openData(ForceFileString);
		for (int i = 0; i < ForceSetNodeImformation.cols(); i++)
		{
			(*InConstraint).ConstraintType = 1;
			InConstraint->ConstraintNodeID = ForceSetNodeImformation(0, i);
			if ((1 == ForceBOUNDARYImformation(0, 1)) && (1 == ForceBOUNDARYImformation(0, 2)) && (1 == ForceBOUNDARYImformation(0, 3)))
			{
				(*InConstraint).ConstraintNodeDofID.resize(3, 1);
				(*InConstraint).ConstraintNodeDofID << 1, 2, 3;
				(*InConstraint).NodeExternalConstraint.resize(3, 1);
				(*InConstraint).NodeExternalConstraint << ForceFileImformation;
			}
			if ((1 == ForceBOUNDARYImformation(0, 1)) && (0 == ForceBOUNDARYImformation(0, 2)) && (1 == ForceBOUNDARYImformation(0, 3)))
			{
				(*InConstraint).ConstraintNodeDofID.resize(2, 1);
				(*InConstraint).ConstraintNodeDofID << 1, 3;
				(*InConstraint).NodeExternalConstraint.resize(2, 1);
				(*InConstraint).NodeExternalConstraint << ForceFileImformation(0,0), ForceFileImformation(0, 2);
			}
			if ((1 == ForceBOUNDARYImformation(0, 1)) && (1 == ForceBOUNDARYImformation(0, 2)) && (0 == ForceBOUNDARYImformation(0, 3)))
			{
				(*InConstraint).ConstraintNodeDofID.resize(2, 1);
				(*InConstraint).ConstraintNodeDofID << 1, 2;
				(*InConstraint).NodeExternalConstraint.resize(2, 1);
				(*InConstraint).NodeExternalConstraint << ForceFileImformation(0, 0), ForceFileImformation(0, 1);
			}
			if ((1 == ForceBOUNDARYImformation(0, 1)) && (0 == ForceBOUNDARYImformation(0, 2)) && (0 == ForceBOUNDARYImformation(0, 3)))
			{
				(*InConstraint).ConstraintNodeDofID.resize(1, 1);
				(*InConstraint).ConstraintNodeDofID << 1;
				(*InConstraint).NodeExternalConstraint.resize(1, 1);
				(*InConstraint).NodeExternalConstraint << ForceFileImformation(0, 0);
			}
			if ((0 == ForceBOUNDARYImformation(0, 1)) && (1 == ForceBOUNDARYImformation(0, 2)) && (1 == ForceBOUNDARYImformation(0, 3)))
			{
				(*InConstraint).ConstraintNodeDofID.resize(2, 1);
				(*InConstraint).ConstraintNodeDofID << 2, 3;
				(*InConstraint).NodeExternalConstraint.resize(2, 1);
				(*InConstraint).NodeExternalConstraint << ForceFileImformation(0, 1), ForceFileImformation(0, 2);
			}
			if ((0 == ForceBOUNDARYImformation(0, 1)) && (0 == ForceBOUNDARYImformation(0, 2)) && (1 == ForceBOUNDARYImformation(0, 3)))
			{
				(*InConstraint).ConstraintNodeDofID.resize(1, 1);
				(*InConstraint).ConstraintNodeDofID << 3;
				(*InConstraint).NodeExternalConstraint.resize(1, 1);
				(*InConstraint).NodeExternalConstraint << ForceFileImformation(0, 2);
			}
			if ((0 == ForceBOUNDARYImformation(0, 1)) && (1 == ForceBOUNDARYImformation(0, 2)) && (0 == ForceBOUNDARYImformation(0, 3)))
			{
				(*InConstraint).ConstraintNodeDofID.resize(1, 1);
				(*InConstraint).ConstraintNodeDofID << 2;
				(*InConstraint).NodeExternalConstraint.resize(1, 1);
				(*InConstraint).NodeExternalConstraint << ForceFileImformation(0, 1);
			}
			(void)(*IAD).InputAllConstraint.insert(make_pair((*InConstraint).ConstraintNodeID, (*InConstraint)));
		}	
	}
	delete InConstraint;
	InConstraint = nullptr;
	delete ls;
    ls = nullptr;


    //删除文件
  /*  remove(DefineCurveFileString.c_str());
    remove(HourglassFileString.c_str());
    remove(SecBeamFileString.c_str());
    remove(EleShFileString.c_str());
    remove(EleBFileString.c_str());
    remove(BoundaryFileString.c_str());
    remove(SetFileString.c_str());
    remove(SlaveNodeFileString.c_str());
    remove(EleSoFileString.c_str());
    remove(MasterNodeFileString.c_str());
    remove(NodeVelocityFileString.c_str());
    remove(SecSolidFileString.c_str());
    remove(PartFileString.c_str());
    remove(NodeFileString.c_str());
    remove(TimeIncrementFileString.c_str());
    remove(ComputingTimeFileString.c_str());
    remove(PlaFileString.c_str());
    remove(ElaFileString.c_str());
    remove(BoundarySetFileString.c_str());
    remove(WallSlaveNodeFileString.c_str());
    remove(LoadNodeFileString.c_str());

	remove(SetNodeFile1String.c_str());
	remove(SetNodeFile2String.c_str());
	remove(SetNodeFile3String.c_str());
	remove(SetNodeFile4String.c_str());
	remove(SetNodeFile5String.c_str());
	remove(SetNodeFile6String.c_str());
	remove(SetNodeFile7String.c_str());
	remove(SetNodeFile8String.c_str());
	remove(SetNodeFile9String.c_str());
	remove(SetNodeFile10String.c_str());
	remove(SegmentSetFile1String.c_str());
	remove(SegmentSetFile2String.c_str());
	remove(SegmentSetFile3String.c_str());
	remove(SegmentSetFile4String.c_str());
	remove(SegmentSetFile5String.c_str());
	remove(SegmentSetFile6String.c_str());
	remove(LoadBodyYFileString.c_str());
	remove(LoadBodyZFileString.c_str());


    remove(ContactFileString2.c_str());
    remove(SecShellFileString2.c_str());
	remove(RigidWallFileString2.c_str());
	remove(SecShellFileString.c_str());
	remove(RigidWallFileString.c_str());
	remove(ContactFileString.c_str());*/



    return IAD;
}

InputFileProject::InputFileProject()
{
	 SetNodeId1 = 0;
	 SetNodeId2 = 0;
	 SetNodeId3 = 0;
	 SetNodeId4 = 0;
	 SetNodeId5 = 0;
	 SetNodeId6 = 0;
	 SetNodeId7 = 0;
	 SetNodeId8 = 0;
	 SetNodeId9 = 0;
     SetNodeId10 = 0;
	 SegmentSetId1 = 0;
	 SegmentSetId2 = 0;
	 SegmentSetId3 = 0;
	 SegmentSetId4 = 0;
	 SegmentSetId5 = 0;
	 SegmentSetId6 = 0;
	 PanduanSetNode=0;
	 PanduanSegmentSetNode=0;
	 AdditionalDigit = "1";
	 PanduanSecondpart = 0;
};

Part::Part()
{
	 Pid = 0;
	 SectionID = 0;
	 Mid = 0;
};
sectionbeam::sectionbeam()
{
	 secidbeam = 0;
	 TS = 0;
     TT = 0;
};
sectionshell::sectionshell()
{
	 secidshell=0;
	 T1=0;
	 T2=0;
	 T3=0;
	 T4=0;
};
Velocity::Velocity()
{
	 SetType=3;     // 1: part set ID
				 // 2: part ID
				 // 3: node set ID
	 SetNodeid = 0;
	 XVelocity = 0;
	 YVelocity = 0;
	 ZVelocity = 0;
};
SetNode::SetNode()
{
	 SetType = 4;
	 SetId=0; //set 集号
	 (void)SetNodeID.setZero();  //set 集节点号
};
SetSegmentNode::SetSegmentNode()
{
	 SetType = 0;
	 SetSegmentId=0; //SetSegment集号
	 (void)SetSegmentNodeID.setZero();  //SetSegment集节点号
};
LoadBodyZ::LoadBodyZ()
{
	 LoadBodyZCurveID=0;
	 LoadCurveScaleFactor=0;
};
LoadBodyY::LoadBodyY()
{
	 LoadBodyYCurveID=0;
	 LoadCurveScaleFactor=0;
};
LoadBodyX::LoadBodyX()
{
	 LoadBodyXCurveID=0;
	 LoadCurveScaleFactor=0;
};

FilenameCombine::FilenameCombine(string file1, string file2)
{
	m_file1 = file1;
	m_file2 = file2;
}

FilenameCombine2::FilenameCombine2(string file1, string file2, string file3)
{
	m_file1 = file1;
	m_file2 = file2;
	m_file3 = file3;
}

MBNode::MBNode()
{
	NodeID = 0;
	NodeCoordinates.fill(0);
};
MBSetNode::MBSetNode()
{
	SetId = 0;
	SetNodeID.fill(0);
};
MBSetSegmentNode:: MBSetSegmentNode()
{
	SetSegmentId = 0;
	SetSegmentNodeID.fill(0);
};