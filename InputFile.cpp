#include "InputFile.h"
#include"csv_MatrixXd_IO.h"


//读人体模型文件函数
int InputFileProject::inputMBFunction(const std::string& MBfileToOpen, InputAllDate* IADate)
{
	DummyInformation* DummyIn = new DummyInformation;
	DummyIn->InMB.open(MBfileToOpen);
	(void)DummyIn->InMB.seekg(0, ios::end); //将文件指针指向文件末端
     fp = DummyIn->InMB.tellg(); //fp 为文件指针的偏移量
	if (int(fp) <= 0) // 偏移量为0，证明文件为空，为首次进入系统
	{
		return 0;
	}
	else
	{
		DummyIn->InMB.seekg(0, ios::beg);
		while (getline(DummyIn->InMB, DummyIn->LineMB))
		{
			//刚体
			if (DummyIn->LineMB == "*RigidBody")
			{
				DummyIn->ColumHingeFile.close();
				DummyIn->MBNodeFile.close();
				DummyIn->BallJointFile.close();
				DummyIn->MBContactFile.close();
				(void)DummyIn->LineMB.erase(0, 1);
				DummyIn->RigidBodyFileString = getFileName(DummyIn->LineMB);
				DummyIn->RigidBodyFile.open(getFileName(DummyIn->LineMB));
			}
			if (DummyIn->RigidBodyFile.is_open())
			{
				getdigit2(DummyIn->RigidBodyFile, DummyIn->LineMB);
			};
			//柱铰
			if (DummyIn->LineMB == "*ColumHinge")
			{
				DummyIn->RigidBodyFile.close();
				DummyIn->BallJointFile.close();
				DummyIn->MBNodeFile.close();
				DummyIn->MBContactFile.close();
				(void)DummyIn->LineMB.erase(0, 1);
				DummyIn->ColumHingeFileString = getFileName(DummyIn->LineMB);
				DummyIn->ColumHingeFile.open(getFileName(DummyIn->LineMB));
			}
			if (DummyIn->ColumHingeFile.is_open())
			{
				getdigit2(DummyIn->ColumHingeFile, DummyIn->LineMB);
			};
			//球铰
			if (DummyIn->LineMB == "*BallJoint")
			{
				DummyIn->ColumHingeFile.close();
				DummyIn->RigidBodyFile.close();
				DummyIn->MBNodeFile.close();
				DummyIn->MBContactFile.close();
				(void)DummyIn->LineMB.erase(0, 1);
				DummyIn->BallJointFileString = getFileName(DummyIn->LineMB);
				DummyIn->BallJointFile.open(getFileName(DummyIn->LineMB));
			}
			if (DummyIn->BallJointFile.is_open())
			{
				getdigit2(DummyIn->BallJointFile, DummyIn->LineMB);
			};

			//NODE
			if (DummyIn->LineMB == "*NODE")
			{
				DummyIn->ColumHingeFile.close();
				DummyIn->RigidBodyFile.close();
				DummyIn->BallJointFile.close();
				DummyIn->MBContactFile.close();
				(void)DummyIn->LineMB.erase(0, 1);
				DummyIn->MBNodeFileString = getFileName2(DummyIn->Multibody, DummyIn->LineMB);
				DummyIn->MBNodeFile.open(DummyIn->MBNodeFileString);
			}
			if (DummyIn->MBNodeFile.is_open())
			{
				getdigit2(DummyIn->MBNodeFile, DummyIn->LineMB);
			};

			//接触
			if (DummyIn->LineMB == "*CONTACT_NODES_TO_SURFACE_ID")
			{
				DummyIn->ColumHingeFile.close();
				DummyIn->RigidBodyFile.close();
				DummyIn->BallJointFile.close();
				DummyIn->MBNodeFile.close();
				(void)DummyIn->LineMB.erase(0, 1);
				DummyIn->MBContactFileString = "MBContact.txt";
				DummyIn->MBContactFileString2 = "MBContactTemp.txt";
				DummyIn->MBContactFile.open(DummyIn->MBContactFileString2);
				DummyIn->MBContactFile.clear();
				DummyIn->MBContactFile << endl;
			}
			if (DummyIn->MBContactFile.is_open())
			{
				if (' ' == DummyIn->LineMB[0])
				{
					DummyIn->MBContactFile << DummyIn->LineMB << " ";
				}
			}

			if (DummyIn->LineMB == "*SET_NODE_LIST")
			{
				DummyIn->ColumHingeFile.close();
				DummyIn->RigidBodyFile.close();
				DummyIn->BallJointFile.close();
				DummyIn->MBNodeFile.close();
				DummyIn->MBContactFile.close();
			}
			if (DummyIn->LineMB == "*SET_SEGMENT")
			{
				DummyIn->ColumHingeFile.close();
				DummyIn->RigidBodyFile.close();
				DummyIn->BallJointFile.close();
				DummyIn->MBNodeFile.close();
				DummyIn->MBContactFile.close();
			}
			if (DummyIn->LineMB == "*END")
			{
				DummyIn->ColumHingeFile.close();
				DummyIn->RigidBodyFile.close();
				DummyIn->BallJointFile.close();
				DummyIn->MBNodeFile.close();
				DummyIn->MBContactFile.close();
			}
			if ("*ConnectNode" == DummyIn->LineMB)
			{
				DummyIn->LineMB = DummyIn->LineMB.erase(0, 1);
				DummyIn->ConnectNodeFileString = getFileName(DummyIn->LineMB);
				DummyIn->ConnectNodeFile.open(DummyIn->ConnectNodeFileString);
			}
			if (DummyIn->ConnectNodeFile.is_open())
			{
				getdigit2(DummyIn->ConnectNodeFile, DummyIn->LineMB);
			}
			if (DummyIn->LineMB == "*END2")
			{
				DummyIn->ConnectNodeFile.close();
			}
		}
		DummyIn->InMB.close();

		//Contact 文件
		DummyIn->MBInContact.open(DummyIn->MBContactFileString2);
		DummyIn->MBContactFile2.open(DummyIn->MBContactFileString);
		while (getline(DummyIn->MBInContact, DummyIn->MBLineContact))
		{
			if (DummyIn->MBContactFile2.is_open())
			{
				if (' ' == DummyIn->MBLineContact[0])
				{
					DummyIn->MBContactFile2 << DummyIn->MBLineContact << endl;
				}
			}
		}
		DummyIn->MBContactFile2.close();
		DummyIn->MBInContact.close();

		//SegmentSet 文件
		MBlsmap* mbls = new MBlsmap;
		MBSetSegmentNode* pMBSetSegmentNode = new MBSetSegmentNode;
		DummyIn->InSegmentSet.open(MBfileToOpen);
		while (getline(DummyIn->InSegmentSet, DummyIn->LineSegmentSet))
		{
			//主面节点
			if ("*SET_SEGMENT" == DummyIn->LineSegmentSet)
			{
				DummyIn->LineSegmentSet = ("MB") + (DummyIn->LineSegmentSet.erase(0, 1));
				DummyIn->SegmentSetFile1String = getFileName(DummyIn->LineSegmentSet);
				DummyIn->SegmentSetFile1.open(DummyIn->SegmentSetFile1String);
				DummyIn->SegmentSetFile1.clear();
				DummyIn->SegmentSetFile1 << endl;
			}
			if (DummyIn->SegmentSetFile1.is_open())
			{
				if (' ' == DummyIn->LineSegmentSet[0])
				{
					DummyIn->SegmentSetFile1 << DummyIn->LineSegmentSet << " ";
				}
			}
			if (("*CONTACT_AUTOMATIC_NODES_TO_SURFACE_ID" == DummyIn->LineSegmentSet) || ("*CONTACT_NODES_TO_SURFACE_ID" == DummyIn->LineSegmentSet) || ("*RIGIDWALL_PLANAR_FINITE_ID" == DummyIn->LineSegmentSet) || ("*ELEMENT_BEAM" == DummyIn->LineSegmentSet)
				|| ("*ELEMENT_SHELL" == DummyIn->LineSegmentSet) || ("*ELEMENT_SOLID" == DummyIn->LineSegmentSet) || ("*SET_NODE_LIST" == DummyIn->LineSegmentSet) || ("*DEFINE_CURVE" == DummyIn->LineSegmentSet) || ("*SET_PART_LIST" == DummyIn->LineSegmentSet)
				|| ("*END" == DummyIn->LineSegmentSet))
			{
				DummyIn->SegmentSetFile1.close();
			}
		}
		DummyIn->InSegmentSet.close();
		ifstream InSegmentSet2;
		InSegmentSet2.open(DummyIn->SegmentSetFile1String);
		DummyIn->SegmentSetFile2String = "MBSegmentSet.txt";
		string LineSegmentSet2;
		int panduanneirongSegmentSet = 0;
		while (getline(InSegmentSet2, LineSegmentSet2))
		{
			ofstream SegmentSetFile2(DummyIn->SegmentSetFile2String);
			if (' ' == LineSegmentSet2[0])
			{
				(void)LineSegmentSet2.erase(50, 4);
				SegmentSetFile2 << LineSegmentSet2 << flush;
				panduanneirongSegmentSet = 1;
			}
			if ((panduanneirongSegmentSet == 1) && (1 == isFileExists(DummyIn->SegmentSetFile2String)))
			{
				Matrix<int, Dynamic, Dynamic>SegmentSet = LinearMSTMMSolver::openDataInt(DummyIn->SegmentSetFile2String);
				pMBSetSegmentNode->SetSegmentId = SegmentSet(0, 0);
				pMBSetSegmentNode->SetSegmentNodeID = SegmentSet;
				(void)mbls->AllMBSetSegmentNode.insert(make_pair(pMBSetSegmentNode->SetSegmentId, (*pMBSetSegmentNode)));
			};
		}
		InSegmentSet2.close();
		delete pMBSetSegmentNode;
		pMBSetSegmentNode = nullptr;

		MBSetNode* pMBSetNode = new MBSetNode;
		//NODE
		if (1 == isFileExists(DummyIn->MBNodeFileString))
		{
			Matrix<int, Dynamic, Dynamic>MBNode1 = LinearMSTMMSolver::openDataInt(DummyIn->MBNodeFileString);
			Matrix<double, Dynamic, Dynamic>MBNode2 = LinearMSTMMSolver::openData(DummyIn->MBNodeFileString);
			MBNode* pMBNode = new MBNode;
			for (int i = 0; i < MBNode1.rows(); i++)
			{
				pMBNode->NodeID = MBNode1(i, 0);
				pMBNode->NodeCoordinates = MBNode2.row(i).rightCols(3);
				(void)mbls->AllMBNode.insert(make_pair(pMBNode->NodeID, (*pMBNode)));
			};
			delete pMBNode;
			pMBNode = nullptr;
		};

		//SetNode
		DummyIn->InSetNode.open(MBfileToOpen);
		while (getline(DummyIn->InSetNode, DummyIn->LineSetNode))
		{
			if ("*SET_NODE_LIST" == DummyIn->LineSetNode)
			{
				DummyIn->LineSetNode = ("MB") + (DummyIn->LineSetNode.erase(0, 1));
				DummyIn->SetNodeFile1String = getFileName(DummyIn->LineSetNode);
				DummyIn->SetNodeFile1.open(DummyIn->SetNodeFile1String);
				DummyIn->SetNodeFile1.clear();
				DummyIn->SetNodeFile1 << endl;
			}
			if (DummyIn->SetNodeFile1.is_open())
			{
				if (' ' == DummyIn->LineSetNode[0])
				{
					DummyIn->SetNodeFile1 << DummyIn->LineSetNode << " ";
				}
			}
			if (("*END" == DummyIn->LineSetNode) || ("*DEFINE_CURVE" == DummyIn->LineSetNode) || ("*BOUNDARY_SPC_NODE" == DummyIn->LineSetNode) || ("*SET_PART_LIST" == DummyIn->LineSetNode) || ("*CONTACT_NODES_TO_SURFACE_ID" == DummyIn->LineSetNode))
			{
				DummyIn->SetNodeFile1.close();
			}
		}
		DummyIn->InSetNode.close();
		ifstream InSetNode2;
		InSetNode2.open(DummyIn->SetNodeFile1String);
		DummyIn->SetNodeFile2String = "MBSETNODELIST.txt";
		string LineSetNode2;
		int panduanneirong = 0;
		while (getline(InSetNode2, LineSetNode2))
		{
			ofstream SetNodeFile2(DummyIn->SetNodeFile2String);
			if (' ' == LineSetNode2[0])
			{
				(void)LineSetNode2.erase(50, 4);
				SetNodeFile2 << LineSetNode2 << flush;
				panduanneirong = 1;
			}
			if ((panduanneirong == 1) && (1 == isFileExists(DummyIn->SetNodeFile2String)))
			{
				Matrix<int, Dynamic, Dynamic>SetNodeMatrix = LinearMSTMMSolver::openDataInt(DummyIn->SetNodeFile2String);
				pMBSetNode->SetId = SetNodeMatrix(0, 0);
				pMBSetNode->SetNodeID = SetNodeMatrix.rightCols(SetNodeMatrix.size() - 1);
				(void)mbls->AllMBSetNode.insert(make_pair(pMBSetNode->SetId, (*pMBSetNode)));
			};
		}
		InSetNode2.close();
		delete pMBSetNode;
		pMBSetNode = nullptr;

		//开始读入数据
		///////////////////////////////////////////////////////////////////////////////////////////////////

		// 刚体信息
		if (isFileExists(DummyIn->RigidBodyFileString) == 1)
		{
			Matrix<int, Dynamic, Dynamic>RigidBodyImformation1 = LinearMSTMMSolver::openDataInt(DummyIn->RigidBodyFileString);
			Matrix<double, Dynamic, Dynamic>RigidBodyImformation2 = LinearMSTMMSolver::openData(DummyIn->RigidBodyFileString);
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
				(void)(*InRigidBody).J.setZero(3, 3);
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
				for (int j = 0; j < mbls->AllMBSetNode[InRigidBody->RigidBodySetID].SetNodeID.cols(); j++)
				{

					(void)InRigidBody->MeshCoor.insert(make_pair(mbls->AllMBSetNode[InRigidBody->RigidBodySetID].SetNodeID(0, j), mbls->AllMBNode[mbls->AllMBSetNode[InRigidBody->RigidBodySetID].SetNodeID(0, j)].NodeCoordinates));
				}
				(void)(*IADate).inputAllRigidBody.insert(make_pair((*InRigidBody).RigidBodyID, (*InRigidBody)));
				delete InRigidBody;
			}
			IADate->inputAllRigidBody[29].HumanID = "Part_human001";
			IADate->inputAllRigidBody[27].HumanID = "Part_human002";
			IADate->inputAllRigidBody[17].HumanID = "Part_human003";
			IADate->inputAllRigidBody[23].HumanID = "Part_human004";
			IADate->inputAllRigidBody[15].HumanID = "Part_human005";
			IADate->inputAllRigidBody[21].HumanID = "Part_human006";
			IADate->inputAllRigidBody[13].HumanID = "Part_human007";
			IADate->inputAllRigidBody[19].HumanID = "Part_human008";
			IADate->inputAllRigidBody[5].HumanID = "Part_human009";
			IADate->inputAllRigidBody[3].HumanID = "Part_human010";
			IADate->inputAllRigidBody[11].HumanID = "Part_human011";
			IADate->inputAllRigidBody[9].HumanID = "Part_human012";
			IADate->inputAllRigidBody[7].HumanID = "Part_human013";
			IADate->inputAllRigidBody[1].HumanID = "Part_human014";
			IADate->inputAllRigidBody[25].HumanID = "Part_human";
		};

		// 柱铰信息
		if (isFileExists(DummyIn->ColumHingeFileString) == 1)
		{
			Matrix<int, Dynamic, Dynamic>ColumHingeImformation1 = LinearMSTMMSolver::openDataInt(DummyIn->ColumHingeFileString);
			Matrix<double, Dynamic, Dynamic>ColumHingeImformation2 = LinearMSTMMSolver::openData(DummyIn->ColumHingeFileString);
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
				(void)(*IADate).inputAllColumnHinge.insert(make_pair((*InColumnHinge).ColumnHingeID, (*InColumnHinge)));
			}
			delete InColumnHinge;
		};

		// 球铰信息
		if (isFileExists(DummyIn->BallJointFileString) == 1)
		{
			Matrix<int, Dynamic, Dynamic>BallJointImformation1 = LinearMSTMMSolver::openDataInt(DummyIn->BallJointFileString);
			Matrix<double, Dynamic, Dynamic>BallJointImformation2 = LinearMSTMMSolver::openData(DummyIn->BallJointFileString);
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
				(void)(*InBallJoint).K.setZero(3, 3);
				(*InBallJoint).K(0, 0) = BallJointImformation2(i, 1);
				(*InBallJoint).K(1, 1) = BallJointImformation2(i, 2);
				(*InBallJoint).K(2, 2) = BallJointImformation2(i, 3);
				(void)(*InBallJoint).C.setZero(3, 3);
				(*InBallJoint).C(0, 0) = BallJointImformation2(i, 4);
				(*InBallJoint).C(1, 1) = BallJointImformation2(i, 5);
				(*InBallJoint).C(2, 2) = BallJointImformation2(i, 6);
				(*InBallJoint).Md(0, 0) = BallJointImformation2(i, 7);
				(*InBallJoint).Md(1, 0) = BallJointImformation2(i, 8);
				(*InBallJoint).Md(2, 0) = BallJointImformation2(i, 9);
				(void)(*IADate).inputAllBallJoint.insert(make_pair((*InBallJoint).BallJointID, (*InBallJoint)));
			}
			delete InBallJoint;
		};

		//Contact
		if (1 == isFileExists(DummyIn->MBContactFileString))
		{
			//Contact 关键字信息
			Matrix<double, Dynamic, Dynamic>MBContactImformation = LinearMSTMMSolver::openData(DummyIn->MBContactFileString);
			Matrix<int, Dynamic, Dynamic>MBContactImformation2 = LinearMSTMMSolver::openDataInt(DummyIn->MBContactFileString);
			//cout << ContactImformation;
			for (int i = 0; i < MBContactImformation.rows(); i++)
			{
				InputFEMtoMBContact* MBInCta = new InputFEMtoMBContact;
				MBInCta->ContactNumber = MBContactImformation2(i, 0);
				MBInCta->ContactType = 1;
				if (( MBContactImformation(i, 5)<1e-5) && ( MBContactImformation(i, 6) < 1e-5))
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
				int k = 1;
				//主从面节点号
				for (int j = 0; j < ((mbls->AllMBSetSegmentNode[MBInCta->MasterNodeSetId].SetSegmentNodeID.cols() - 1) / 4); j++)
				{
					Matrix<int, 4, 1> SetSegmentRow = mbls->AllMBSetSegmentNode[MBInCta->MasterNodeSetId].SetSegmentNodeID.block<1, 4>(0, k).adjoint();
					(void)MBInCta->MasterContactNode.insert(make_pair((j + 1), SetSegmentRow));
					k += 4;
				};
				for (int n = 0; n < mbls->AllMBSetNode[MBInCta->SlaveNodeSetId].SetNodeID.rows(); n++)
				{
					(void)MBInCta->SlaveContactNode.insert(make_pair((n + 1), mbls->AllMBSetNode[MBInCta->SlaveNodeSetId].SetNodeID.row(n).adjoint()));
				};
				(void)IADate->InputAllFEMtoMBContact.insert(make_pair(MBInCta->ContactNumber, (*MBInCta)));
				delete MBInCta;
				MBInCta = nullptr;

			}

		}

		//ConnectNodeFileString
		if (isFileExists(DummyIn->ConnectNodeFileString) == 1)
		{
			Matrix<int, Dynamic, Dynamic>ConnectNodeImformation = LinearMSTMMSolver::openDataInt(DummyIn->ConnectNodeFileString);
			IADate->ConnectNode = ConnectNodeImformation(0, 0);

		}

		delete mbls;
		mbls = nullptr;

		//删除文件
		(void)remove(DummyIn->MBContactFileString.c_str());
		(void)remove(DummyIn->MBNodeFileString.c_str());
		(void)remove(DummyIn->RigidBodyFileString.c_str());
		(void)remove(DummyIn->ColumHingeFileString.c_str());
		(void)remove(DummyIn->BallJointFileString.c_str());
		(void)remove(DummyIn->MBContactFileString2.c_str());
		(void)remove(DummyIn->ConnectNodeFileString.c_str());
		(void)remove(DummyIn->SegmentSetFile2String.c_str());
		(void)remove(DummyIn->SetNodeFile2String.c_str());
		(void)remove(DummyIn->SegmentSetFile1String.c_str());
		(void)remove(DummyIn->SetNodeFile1String.c_str());

		delete DummyIn;
		DummyIn = nullptr;
		return 1;

	}
};

//读文件主函数
InputAllDate* InputFileProject::inputFunction(const std::string& fileToOpen)
{
	VehicleInformation* VehicleIn = new VehicleInformation;
	VehicleIn->In.open(fileToOpen);
    while (getline(VehicleIn->In, VehicleIn->line))
    {
		//跳过注释行
		if (VehicleIn->line[0] == '$')
		{
			continue;
		}

        //*LOAD_BODY_PARTS
        if ("*LOAD_BODY_PARTS" ==VehicleIn->line )
        {
            VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->LoadBodyYFile.close();
        }

        //*SET_PART_LIST
        if ( "*SET_PART_LIST"==VehicleIn->line )
        {
            VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->LoadBodyYFile.close();
        }

        //*LOAD_BODY_Y
        if ( "*LOAD_BODY_Y"== VehicleIn->line)
        {
            VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->LoadNodeFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
            VehicleIn->LoadBodyYFileString = getFileName(VehicleIn->line);
            VehicleIn->LoadBodyYFile.open(VehicleIn->LoadBodyYFileString);
			continue;
        }
        if (VehicleIn->LoadBodyYFile.is_open() && (VehicleIn->line[0] != '*'))
        {
			VehicleIn->LoadBodyYFile << VehicleIn->line << endl;
        };

        //*LOAD_BODY_Z
		if ( "*LOAD_BODY_Z"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->WallSlaveNodeFile.close();
			VehicleIn->BoundarySetFile.close();
			VehicleIn->HourglassFile.close();
			VehicleIn->RigidWallFile.close();
			VehicleIn->TimeIncrementFile.close();
			VehicleIn->NodeVelocityFile.close();
			VehicleIn->PlaFile.close();
			VehicleIn->PartFile.close();
			VehicleIn->SecSolidFile.close();
			VehicleIn->MasterNodeFile.close();
			VehicleIn->ContactFile.close();
			VehicleIn->EleSoFile.close();
			VehicleIn-> SlaveNodeFile.close();
			VehicleIn->BoundaryFile.close();
			VehicleIn->EleBFile.close();
			VehicleIn->EleShFile.close();
			VehicleIn->SecBeamFile.close();
			VehicleIn->SecShellFile.close();
			VehicleIn->SetFile.close();
			VehicleIn->ComputingTimeFile.close();
			VehicleIn->LoadNodeFile.close();
			VehicleIn->line=VehicleIn->line.erase(0, 1);
            VehicleIn->LoadBodyZFileString = getFileName(VehicleIn->line);
            VehicleIn->LoadBodyZFile.open(VehicleIn->LoadBodyZFileString);
			continue;
		}
		if (VehicleIn->LoadBodyZFile.is_open() && (VehicleIn->line[0] != '*'))
		{
			VehicleIn->LoadBodyZFile << VehicleIn->line << endl;
		};

        //*DEFINE_CURVE
        if ( "*DEFINE_CURVE"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
            VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->LoadNodeFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
            VehicleIn->DefineCurveFileString = getFileName(VehicleIn->line);
            VehicleIn->DefineCurveFile.open(VehicleIn->DefineCurveFileString);
			continue;
        }
        if (VehicleIn->DefineCurveFile.is_open() && (VehicleIn->line[0] != '*'))
        {
			VehicleIn->DefineCurveFile << VehicleIn->line << endl;
        };

        //*LOAD_NODE_SET
        if ( "*LOAD_NODE_SET"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->LoadNodeFileString = getFileName(VehicleIn->line);
            VehicleIn->LoadNodeFile.open(VehicleIn->LoadNodeFileString);
			continue;
        }
        if (VehicleIn->LoadNodeFile.is_open() && (VehicleIn->line[0] != '*'))
        {
			VehicleIn->LoadNodeFile << VehicleIn->line << endl;
        };

        //计算时长
        if ( "*CONTROL_TERMINATION"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->ComputingTimeFileString = getFileName(VehicleIn->line);
            VehicleIn->ComputingTimeFile.open(VehicleIn->ComputingTimeFileString);
			continue;
        }
        if (VehicleIn->ComputingTimeFile.is_open() && (VehicleIn->line[0] != '*'))
        {
			VehicleIn->ComputingTimeFile << VehicleIn->line << endl;
        };

        //步长
        if (  "*CONTROL_TIMESTEP"== VehicleIn->line)
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->TimeIncrementFileString = getFileName(VehicleIn->line);
            VehicleIn->TimeIncrementFile.open(getFileName(VehicleIn->line));
			continue;
        }
        if (VehicleIn->TimeIncrementFile.is_open() && (VehicleIn->line[0] != '*'))
        {
			VehicleIn->TimeIncrementFile<< VehicleIn->line << endl;
        };

		if ( "*DATABASE_BINARY_D3PLOT"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
			VehicleIn->WallSlaveNodeFile.close();
			VehicleIn->BoundarySetFile.close();
			VehicleIn->HourglassFile.close();
			VehicleIn->RigidWallFile.close();
			VehicleIn->ComputingTimeFile.close();
			VehicleIn->TimeIncrementFile.close();
			VehicleIn->NodeVelocityFile.close();
			VehicleIn->PlaFile.close();
			VehicleIn->PartFile.close();
			VehicleIn->SecSolidFile.close();
			VehicleIn->MasterNodeFile.close();
			VehicleIn->ContactFile.close();
			VehicleIn->EleSoFile.close();
			VehicleIn-> SlaveNodeFile.close();
			VehicleIn->BoundaryFile.close();
			VehicleIn->EleBFile.close();
			VehicleIn->EleShFile.close();
			VehicleIn->SecBeamFile.close();
			VehicleIn->SecShellFile.close();
			VehicleIn->SetFile.close();
			VehicleIn->LoadNodeFile.close();
			VehicleIn->DefineCurveFile.close();
		};

        if ( "*DATABASE_GLSTAT"== VehicleIn->line)
		{
			VehicleIn->LoadBodyYFile.close();

			VehicleIn->LoadBodyZFile.close();

            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
        };

        if ( "*CONTROL_IMPLICIT_EIGENVALUE"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();

			VehicleIn->LoadBodyZFile.close();

            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
        };

        //节点
        if ( "*NODE"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->NodeFileString = getFileName(VehicleIn->line);
            VehicleIn->NodeFile.open(VehicleIn->NodeFileString);
            VehicleIn->NodeFile.clear();
            continue;
        }
        if (VehicleIn->NodeFile.is_open() && (VehicleIn->line[0] != '*'))
        {
			VehicleIn->NodeFile << VehicleIn->line << endl;
        }

        //材料部分最终输出文件见最下方，InputElaFile，InputPlaFile。
        if ( "*MAT_ELASTIC"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
            VehicleIn->line=VehicleIn->line.erase(0, 1);
			VehicleIn->ElaFileString = getFileName(VehicleIn->line);
			VehicleIn->ElaFile.open(getFileName(VehicleIn->line));
			VehicleIn->ElaFile.clear();
            continue;
        }
        if (VehicleIn->ElaFile.is_open() && (VehicleIn->line[0] != '*'))
        {
                VehicleIn->line = VehicleIn->line.insert(10, " ");
				VehicleIn->line = VehicleIn->line.insert(21, " ");
				VehicleIn->ElaFile << VehicleIn->line << endl;
        }

        if ( "*MAT_PLASTIC_KINEMATIC"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->PlaFileString = getFileName(VehicleIn->line);
            VehicleIn->PlaFile.open(getFileName(VehicleIn->line));
            VehicleIn->PlaFile.clear();
            continue;
        }
        if (VehicleIn->PlaFile.is_open() && (VehicleIn->line[0] != '*'))
        {
                VehicleIn->line = VehicleIn->line.insert(10, " ");
                VehicleIn->PlaFile << VehicleIn->line << endl;
        }

        //Part
        if ( "*PART"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->PartFileString = getFileName(VehicleIn->line);
            VehicleIn->PartFile.open(getFileName(VehicleIn->line));
            continue;
        }
        if (VehicleIn->PartFile.is_open()&&(' ' == VehicleIn->line[0]))
        {
				VehicleIn->line = VehicleIn->line.erase(49, 2);
                VehicleIn->PartFile << VehicleIn->line << endl;
        };

        //沙漏
        if ( "*HOURGLASS"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->HourglassFileString = getFileName(VehicleIn->line);
            VehicleIn->HourglassFile.open(getFileName(VehicleIn->line));
            continue;
        }
        if (VehicleIn->HourglassFile.is_open() && (VehicleIn->line[0] != '*'))
        {
			VehicleIn->HourglassFile << VehicleIn->line << endl;
        }

        //初始速度*INITIAL_VELOCITY_GENERATION
        if ( "*INITIAL_VELOCITY_GENERATION"== VehicleIn->line)
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->NodeVelocityFileString = getFileName(VehicleIn->line);
            VehicleIn->NodeVelocityFile.open(getFileName(VehicleIn->line));
			continue;
        }
        if (VehicleIn->NodeVelocityFile.is_open() && (VehicleIn->line[0] != '*'))
        {
             VehicleIn->NodeVelocityFile << VehicleIn->line << " ";
        }

        //*BOUNDARY_SPC_SET
        if ( "*BOUNDARY_SPC_SET"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->BoundarySetFileString = getFileName(VehicleIn->line);
            VehicleIn->BoundarySetFile.open(getFileName(VehicleIn->line));
            continue;
        }
        if (VehicleIn->BoundarySetFile.is_open() && (VehicleIn->line[0] != '*'))
        {
			VehicleIn->BoundarySetFile << VehicleIn->line << endl;
        }

        if ( "*SET_SEGMENT"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
			VehicleIn->WallSlaveNodeFile.close();
			VehicleIn->BoundarySetFile.close();
			VehicleIn->HourglassFile.close();
			VehicleIn->RigidWallFile.close();
			VehicleIn->ComputingTimeFile.close();
			VehicleIn->TimeIncrementFile.close();
			VehicleIn->NodeVelocityFile.close();
			VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
			VehicleIn->PlaFile.close();
			VehicleIn->PartFile.close();
			VehicleIn->SecSolidFile.close();
			VehicleIn->MasterNodeFile.close();
			VehicleIn->ContactFile.close();
			VehicleIn->EleSoFile.close();
			VehicleIn-> SlaveNodeFile.close();
			VehicleIn->BoundaryFile.close();
			VehicleIn->EleBFile.close();
			VehicleIn->EleShFile.close();
			VehicleIn->SecBeamFile.close();
			VehicleIn->SecShellFile.close();
			VehicleIn->SetFile.close();
			VehicleIn->LoadNodeFile.close();
			VehicleIn->DefineCurveFile.close();
        }

        //接触
        if ( "*CONTACT_AUTOMATIC_NODES_TO_SURFACE_ID"==VehicleIn->line  ||  "*CONTACT_NODES_TO_SURFACE_ID"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->ContactFileString = "Contact.txt";
			VehicleIn->ContactFileString2 = "ContactTemp.txt";
            VehicleIn->ContactFile.open(VehicleIn->ContactFileString2);
            VehicleIn->ContactFile.clear();
            VehicleIn->ContactFile << endl;
            continue;
        }
        if (VehicleIn->ContactFile.is_open() && (VehicleIn->line[0] != '*'))
        {
                VehicleIn->ContactFile << VehicleIn->line << " ";
        }

        //实体单元   
        if ( "*ELEMENT_SOLID"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->EleSoFileString = getFileName(VehicleIn->line);
            VehicleIn->EleSoFile.open(getFileName(VehicleIn->line));
			VehicleIn->EleSoFile.clear();
            continue;
        }
        if (VehicleIn->EleSoFile.is_open() && (VehicleIn->line[0] != '*'))
        {
			VehicleIn->EleSoFile << VehicleIn->line << endl;
        }

        //从面节点
        if ( "*SET_NODE_LIST"== VehicleIn->line)
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
        }

        //边界条件
        if (  "*BOUNDARY_SPC_NODE"==VehicleIn->line)
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->BoundaryFileString = getFileName(VehicleIn->line);
            VehicleIn->BoundaryFile.open(getFileName(VehicleIn->line));
            continue;
        }
        if (VehicleIn->BoundaryFile.is_open() && (VehicleIn->line[0] != '*'))
        {
			VehicleIn->BoundaryFile << VehicleIn->line << endl;
        }

        //刚性墙
        if ( "*RIGIDWALL_PLANAR_FINITE_ID"== VehicleIn->line)
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->RigidWallFileString2 = getFileName2(VehicleIn->line, VehicleIn->AdditionalDigit);
			VehicleIn->RigidWallFileString = getFileName(VehicleIn->line);
            VehicleIn->RigidWallFile.open(VehicleIn->RigidWallFileString2);
            VehicleIn->RigidWallFile.clear();
            VehicleIn->RigidWallFile << endl;
			continue;
        }
        if (VehicleIn->RigidWallFile.is_open() && (VehicleIn->line[0] != '*'))
        {
                VehicleIn->line = VehicleIn->line.insert(20, " ");
                VehicleIn->line = VehicleIn->line.insert(51, " ");
                VehicleIn->RigidWallFile << VehicleIn->line << " ";
        }

        //梁单元
        if ("*ELEMENT_BEAM" == VehicleIn->line)
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->EleBFileString = getFileName(VehicleIn->line);
            VehicleIn->EleBFile.open(getFileName(VehicleIn->line));
            continue;
        }
        if (VehicleIn->EleBFile.is_open() && (VehicleIn->line[0] != '*'))
        {
			VehicleIn->EleBFile << VehicleIn->line << endl;
        }

        //壳单元
        if ( "*ELEMENT_SHELL"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->EleShFileString = getFileName(VehicleIn->line);
            VehicleIn->EleShFile.open(getFileName(VehicleIn->line));
            VehicleIn->EleShFile.clear();
            continue;
        }
        if (VehicleIn->EleShFile.is_open() && (VehicleIn->line[0] != '*'))
        {
			VehicleIn->EleShFile << VehicleIn->line << endl;
        }

        //SECTION梁
        if ( "*SECTION_BEAM"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->SecBeamFileString = getFileName(VehicleIn->line);
            VehicleIn->SecBeamFile.open(getFileName(VehicleIn->line));
            continue;
        }
        if (VehicleIn->SecBeamFile.is_open() && (VehicleIn->line[0] != '*'))
        {
                VehicleIn->line = VehicleIn->line.insert(0, VehicleIn->AdditionalDigit);
                VehicleIn->SecBeamFile << VehicleIn->line << " ";
        }

        //SECTION壳
        if ( "*SECTION_SHELL"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->SecShellFileString = getFileName(VehicleIn->line);
			VehicleIn->SecShellFileString2 = getFileName2(VehicleIn->line, VehicleIn->AdditionalDigit);
            VehicleIn->SecShellFile.open(VehicleIn->SecShellFileString2);
            VehicleIn->SecShellFile.clear();
            VehicleIn->SecShellFile << endl;
            continue;
        }
        if (VehicleIn->SecShellFile.is_open() && (VehicleIn->line[0] != '*'))
        {
                VehicleIn->SecShellFile << VehicleIn->line << " ";
        }

        //SECTION实体
        if ( "*SECTION_SOLID"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
			VehicleIn->line = VehicleIn->line.erase(0, 1);
			VehicleIn->SecSolidFileString = getFileName(VehicleIn->line);
            VehicleIn->SecSolidFile.open(getFileName(VehicleIn->line));
            continue;
        }
        if (VehicleIn->SecSolidFile.is_open() && (VehicleIn->line[0] != '*'))
        {
			VehicleIn->SecSolidFile << VehicleIn->line << endl;
        };
        if ( "*END"==VehicleIn->line )
		{
			VehicleIn->LoadBodyYFile.close();
			VehicleIn->LoadBodyZFile.close();
            VehicleIn->WallSlaveNodeFile.close();
            VehicleIn->BoundarySetFile.close();
            VehicleIn->HourglassFile.close();
            VehicleIn->RigidWallFile.close();
            VehicleIn->ComputingTimeFile.close();
            VehicleIn->TimeIncrementFile.close();
            VehicleIn->NodeVelocityFile.close();
            VehicleIn->NodeFile.close();
			VehicleIn->ElaFile.close();
            VehicleIn->PlaFile.close();
            VehicleIn->PartFile.close();
            VehicleIn->SecSolidFile.close();
            VehicleIn->MasterNodeFile.close();
            VehicleIn->ContactFile.close();
            VehicleIn->EleSoFile.close();
            VehicleIn-> SlaveNodeFile.close();
            VehicleIn->BoundaryFile.close();
            VehicleIn->EleBFile.close();
            VehicleIn->EleShFile.close();
            VehicleIn->SecBeamFile.close();
            VehicleIn->SecShellFile.close();
            VehicleIn->SetFile.close();
            VehicleIn->LoadNodeFile.close();
            VehicleIn->DefineCurveFile.close();
        }
    }
	VehicleIn->In.close();

     //SecShell文件
	VehicleIn->InSecShell.open(VehicleIn->SecShellFileString2);
	VehicleIn->SecShellFile2.open(VehicleIn->SecShellFileString);
    while (getline(VehicleIn->InSecShell, VehicleIn->LineSecShell))
    {
        if (VehicleIn->SecShellFile2.is_open())
        {
            if ( ' '== VehicleIn->LineSecShell[0] )
            {
				VehicleIn->SecShellFile2 << VehicleIn->LineSecShell << endl;
            }
        }

    }
	VehicleIn->SecShellFile2.close();
	VehicleIn->InSecShell.close();

    //Contact 文件
	VehicleIn->InContact.open(VehicleIn->ContactFileString2);
	VehicleIn->ContactFile2.open(VehicleIn->ContactFileString);
    while (getline(VehicleIn->InContact, VehicleIn->LineContact))
    {
        if (VehicleIn->ContactFile2.is_open())
        {
            if (  ' '== VehicleIn->LineContact[0])
            {
				VehicleIn->ContactFile2 << VehicleIn->LineContact << endl;
            }
        }
    }
	VehicleIn->ContactFile2.close();
	VehicleIn->InContact.close();

    //RIGIDWALL_PLANAR_FINITE_ID
	VehicleIn->InRigidwall.open(VehicleIn->RigidWallFileString2);
	VehicleIn->RigidWallFile2.open(VehicleIn->RigidWallFileString);
	while (getline(VehicleIn->InRigidwall, VehicleIn->LineRigidwall))
	{
		if (VehicleIn->RigidWallFile2.is_open())
		{
			if ( ' '== VehicleIn->LineRigidwall[0] )
			{
				VehicleIn->RigidWallFile2 << VehicleIn->LineRigidwall << endl;
			}
		}

	}
	VehicleIn->RigidWallFile2.close();
	VehicleIn->InRigidwall.close();

    //SegmentSet test
	lsmap* ls = new lsmap;
	SetSegmentNode* pSegment = new SetSegmentNode;
	VehicleIn->InSegmentSet.open(fileToOpen);
	while (getline(VehicleIn->InSegmentSet, VehicleIn->LineSegmentSet))
	{
		//跳过注释行
		if (VehicleIn->LineSegmentSet[0] == '$')
		{
			continue;
		}
		//主面节点
		if ("*SET_SEGMENT" == VehicleIn->LineSegmentSet)
		{
			VehicleIn->SetSegment = VehicleIn->LineSegmentSet.erase(0, 1);
			VehicleIn->SegmentSetFile1String = getFileName(VehicleIn->LineSegmentSet);
			VehicleIn->SegmentSetFile1.open(VehicleIn->SegmentSetFile1String);
			VehicleIn->SegmentSetFile1.clear();
			VehicleIn->SegmentSetFile1 << endl;
			continue;
		}
		if (VehicleIn->SegmentSetFile1.is_open() && (VehicleIn->LineSegmentSet[0] != '*'))
		{
			VehicleIn->SegmentSetFile1 << VehicleIn->LineSegmentSet << " ";
		}
		if (("*CONTACT_AUTOMATIC_NODES_TO_SURFACE_ID" == VehicleIn->LineSegmentSet) || ("*CONTACT_NODES_TO_SURFACE_ID" == VehicleIn->LineSegmentSet) || ("*RIGIDWALL_PLANAR_FINITE_ID" == VehicleIn->LineSegmentSet) || ("*ELEMENT_BEAM" == VehicleIn->LineSegmentSet)
			|| ("*ELEMENT_SHELL" == VehicleIn->LineSegmentSet) || ("*ELEMENT_SOLID" == VehicleIn->LineSegmentSet) || ("*SET_NODE_LIST" == VehicleIn->LineSegmentSet) || ("*DEFINE_CURVE" == VehicleIn->LineSegmentSet) || ("*SET_PART_LIST" == VehicleIn->LineSegmentSet)
			|| ("*END" == VehicleIn->LineSegmentSet))
		{
			VehicleIn->SegmentSetFile1.close();
		}
	}
	VehicleIn->InSegmentSet.close();
	ifstream InSegmentSet2;
	InSegmentSet2.open(VehicleIn->SegmentSetFile1String);
	VehicleIn->SegmentSetFile2String = "SegmentSet.txt";
	string LineSegmentSet2;
	int panduanneirongSegmentSet = 0;
	while (getline(InSegmentSet2, LineSegmentSet2))
	{
		ofstream SegmentSetFile2(VehicleIn->SegmentSetFile2String);
		if (' ' == LineSegmentSet2[0])
		{
			(void)LineSegmentSet2.erase(50, 4);
			SegmentSetFile2 << LineSegmentSet2 << flush;
			panduanneirongSegmentSet = 1;
		}
		if ((panduanneirongSegmentSet == 1) && (1 == isFileExists(VehicleIn->SegmentSetFile2String)))
		{
			Matrix<int, Dynamic, Dynamic>SegmentSet = LinearMSTMMSolver::openDataInt(VehicleIn->SegmentSetFile2String);
			pSegment->SetSegmentId = SegmentSet(0, 0);
			pSegment->SetSegmentNodeID = SegmentSet;
			(void)ls->AllSetSegment.insert(make_pair(pSegment->SetSegmentId, (*pSegment)));
		};
	}
	InSegmentSet2.close();
	delete pSegment;
	pSegment = nullptr;


	//SetNode信息  
	SetNode* pSetNode = new SetNode;
	VehicleIn->InSetNode.open(fileToOpen);
	while (getline(VehicleIn->InSetNode, VehicleIn->LineSetNode))
	{
		//跳过注释行
		if (VehicleIn->LineSetNode[0] == '$')
		{
			continue;
		}
		if ("*SET_NODE_LIST" == VehicleIn->LineSetNode)
		{
			VehicleIn->Setnodelist = VehicleIn->LineSetNode.erase(0, 1);
			VehicleIn->SetNodeFile1String = getFileName(VehicleIn->LineSetNode);
			VehicleIn->SetNodeFile1.open(VehicleIn->SetNodeFile1String);
			VehicleIn->SetNodeFile1.clear();
			VehicleIn->SetNodeFile1 << endl;
			VehicleIn->PanduanSetNode = 1;
			continue;
		}
		if (VehicleIn->SetNodeFile1.is_open() && (VehicleIn->LineSetNode[0] != '*'))
		{
			VehicleIn->SetNodeFile1 << VehicleIn->LineSetNode << " ";
		}
		if (("*END" == VehicleIn->LineSetNode) || ("*DEFINE_CURVE" == VehicleIn->LineSetNode) || ("*BOUNDARY_SPC_NODE" == VehicleIn->LineSetNode) || ("*SET_PART_LIST" == VehicleIn->LineSetNode) || ("*CONTACT_NODES_TO_SURFACE_ID" == VehicleIn->LineSetNode))
		{
			VehicleIn->SetNodeFile1.close();
			VehicleIn->PanduanSetNode = 0;
		}
	}
	VehicleIn->InSetNode.close();
	ifstream InSetNode2;
	InSetNode2.open(VehicleIn->SetNodeFile1String);
	VehicleIn->SetNodeFile2String = "SETNODELIST.txt";
	string LineSetNode2;
	int panduanneirong=0;
	while (getline(InSetNode2, LineSetNode2))
	{
		ofstream SetNodeFile2(VehicleIn->SetNodeFile2String);
		if (' ' == LineSetNode2[0])
		{
			(void)LineSetNode2.erase(50, 4);
			SetNodeFile2 << LineSetNode2 << flush;
			panduanneirong = 1;
		}
		if ((panduanneirong == 1) && (1 == isFileExists(VehicleIn->SetNodeFile2String)))
		{
			Matrix<int, Dynamic, Dynamic>SetNodeMatrix = LinearMSTMMSolver::openDataInt(VehicleIn->SetNodeFile2String);
			pSetNode->SetId = SetNodeMatrix(0, 0);
			pSetNode->SetNodeID = SetNodeMatrix.rightCols(SetNodeMatrix.size() - 1);
			(void)ls->AllSetNode.insert(make_pair(pSetNode->SetId, (*pSetNode)));
		};
	}
	//SetNodeFile2.close();
	InSetNode2.close();
	delete pSetNode;
	pSetNode = nullptr;
	//cout << ls->AllSetNode[4].SetNodeID << endl;
	
	//FORCE
	VehicleIn->InForce.open(fileToOpen);
	while (getline(VehicleIn->InForce, VehicleIn->LineForce))
	{
		if ("*END" == VehicleIn->LineForce)
		{
			VehicleIn->PanduanForce = 1;
		}
		if (("*BOUNDARY_FORCE_SET" == VehicleIn->LineForce)&&(VehicleIn->PanduanForce == 1))
		{
			VehicleIn->LineForce = VehicleIn->LineForce.erase(0, 1);
			VehicleIn->ForceBOUNDARYFileString = getFileName(VehicleIn->LineForce);
			VehicleIn->ForceBOUNDARYFile.open(VehicleIn->ForceBOUNDARYFileString);
		}
		if (VehicleIn->ForceBOUNDARYFile.is_open())
		{
			getdigit2(VehicleIn->ForceBOUNDARYFile, VehicleIn->LineForce);
		}
		if (("*SET_NODE_LIST_FORCE" == VehicleIn->LineForce) && (VehicleIn->PanduanForce == 1))
		{
			VehicleIn->ForceBOUNDARYFile.close();
			VehicleIn->LineForce = VehicleIn->LineForce.erase(0, 1);
			VehicleIn->ForceSetNodeFileString = getFileName(VehicleIn->LineForce);
			VehicleIn->ForceSetNodeFile.open(VehicleIn->ForceSetNodeFileString);
		}
		if (VehicleIn->ForceSetNodeFile.is_open())
		{
			if (' ' == VehicleIn->LineForce[0])
			{
				VehicleIn->ForceSetNodeFile << VehicleIn->LineForce << " ";
			}
		}
		if (("*FORCE" == VehicleIn->LineForce) && (VehicleIn->PanduanForce == 1))
		{
			VehicleIn->ForceBOUNDARYFile.close();
			VehicleIn->ForceSetNodeFile.close();
			VehicleIn->LineForce = VehicleIn->LineForce.erase(0, 1);
			VehicleIn->ForceFileString = getFileName(VehicleIn->LineForce);
			VehicleIn->ForceFile.open(VehicleIn->ForceFileString);
		}
		if (VehicleIn->ForceFile.is_open())
		{
			getdigit2(VehicleIn->ForceFile, VehicleIn->LineForce);

		}
		if (("*END2" == VehicleIn->LineForce) && (VehicleIn->PanduanForce == 1))
		{
			VehicleIn->ForceBOUNDARYFile.close();
			VehicleIn->ForceSetNodeFile.close();
			VehicleIn->ForceFile.close();
			VehicleIn->PanduanForce = 0;
		}
		
	}
	VehicleIn->InForce.close();
    
    //LoadBodyZ信息
	if (1 ==isFileExists(VehicleIn->LoadBodyZFileString) )
	{
		Matrix<int, Dynamic, Dynamic>LoadBodyZ1 = LinearMSTMMSolver::openDataInt(VehicleIn->LoadBodyZFileString);
		Matrix<double, Dynamic, Dynamic>LoadBodyZ2 = LinearMSTMMSolver::openData(VehicleIn->LoadBodyZFileString);
        LoadBodyZ* pLoadBodyZ = new LoadBodyZ;
        pLoadBodyZ->LoadBodyZCurveID = LoadBodyZ1(0, 0);
		pLoadBodyZ->LoadCurveScaleFactor = LoadBodyZ2(0, 1);
		(void)ls->AllLoadBodyZ.insert(make_pair(pLoadBodyZ->LoadBodyZCurveID, (*pLoadBodyZ)));
        delete pLoadBodyZ;
        pLoadBodyZ = nullptr;
	};

	//LoadBodyY信息
	if (1 ==isFileExists(VehicleIn->LoadBodyYFileString) )
	{
		Matrix<int, Dynamic, Dynamic>LoadBodyY1 = LinearMSTMMSolver::openDataInt(VehicleIn->LoadBodyYFileString);
		Matrix<double, Dynamic, Dynamic>LoadBodyY2 = LinearMSTMMSolver::openData(VehicleIn->LoadBodyYFileString);
		LoadBodyY* pLoadBodyY = new LoadBodyY;
        pLoadBodyY->LoadBodyYCurveID = LoadBodyY1(0, 0);
        pLoadBodyY->LoadCurveScaleFactor = LoadBodyY2(0, 1);
		(void)ls->AllLoadBodyY.insert(make_pair(pLoadBodyY->LoadBodyYCurveID, (*pLoadBodyY)));
		delete pLoadBodyY;
        pLoadBodyY = nullptr;

	};

    //Part 信息
    if ( 1==isFileExists(VehicleIn->PartFileString) )
    {
        Matrix<int, Dynamic, Dynamic>PartImformation = LinearMSTMMSolver::openDataInt(VehicleIn->PartFileString);
		KFilePart* IP = new KFilePart;
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
    if ( 1==isFileExists(VehicleIn->SecBeamFileString) )
    {
        Matrix<int, Dynamic, Dynamic>SecBImformation1 = LinearMSTMMSolver::openDataInt(VehicleIn->SecBeamFileString);
        Matrix<double, Dynamic, Dynamic>SecBImformation2 = LinearMSTMMSolver::openData(VehicleIn->SecBeamFileString);
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
    if ( 1==isFileExists(VehicleIn->SecShellFileString) )
    {
        Matrix<int, Dynamic, Dynamic>SecSHImformation1 = LinearMSTMMSolver::openDataInt(VehicleIn->SecShellFileString);
        Matrix<double, Dynamic, Dynamic>SecSHImformation2 = LinearMSTMMSolver::openData(VehicleIn->SecShellFileString);
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
    if ( 1==isFileExists(VehicleIn->NodeVelocityFileString) )
    {
        Matrix<int, Dynamic, Dynamic>NodeVelocityFileImformation1 = LinearMSTMMSolver::openDataInt(VehicleIn->NodeVelocityFileString);
        Matrix<double, Dynamic, Dynamic>NodeVelocityFileImformation2 = LinearMSTMMSolver::openData(VehicleIn->NodeVelocityFileString);
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

    ////开始写入inputdate.h//////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    InputAllDate* IAD = new InputAllDate;

    //节点信息
    if ( 1==isFileExists(VehicleIn->NodeFileString) )
    {
        Matrix<double, Dynamic, Dynamic>NodeImformation1 = LinearMSTMMSolver::openData(VehicleIn->NodeFileString);
        Matrix<int, Dynamic, Dynamic>NodeImformation2 = LinearMSTMMSolver::openDataInt(VehicleIn->NodeFileString);
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
    if (1 ==isFileExists(VehicleIn->EleSoFileString) )
    {
        Matrix<int, Dynamic, Dynamic>EleSoImformation = LinearMSTMMSolver::openDataInt(VehicleIn->EleSoFileString);
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
    if ( 1==isFileExists(VehicleIn->EleShFileString) )
    {
        Matrix<int, Dynamic, Dynamic>EleShImformation = LinearMSTMMSolver::openDataInt(VehicleIn->EleShFileString);
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
    if ( 1==isFileExists(VehicleIn->EleBFileString) )
    {
        Matrix<int, Dynamic, Dynamic>EleBImformation = LinearMSTMMSolver::openDataInt(VehicleIn->EleBFileString);
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
    if ( 1==isFileExists(VehicleIn->NodeVelocityFileString) )
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
	if (1 ==isFileExists(VehicleIn->LoadBodyZFileString) )
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
	if (1 ==isFileExists(VehicleIn->LoadBodyYFileString) )
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
    if ( 1==isFileExists(VehicleIn->ElaFileString) )
    {
        Matrix<double, Dynamic, Dynamic>MaEImformation1 = LinearMSTMMSolver::openData(VehicleIn->ElaFileString);
        Matrix<int, Dynamic, Dynamic>MaEImformation2 = LinearMSTMMSolver::openDataInt(VehicleIn->ElaFileString);
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
    if (1 ==isFileExists(VehicleIn->PlaFileString) )
    {
        Matrix<double, Dynamic, Dynamic>MaPImformation1 = LinearMSTMMSolver::openData(VehicleIn->PlaFileString);
        Matrix<int, Dynamic, Dynamic>MaPImformation2 = LinearMSTMMSolver::openDataInt(VehicleIn->PlaFileString);
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
	if ( 1==isFileExists(VehicleIn->ContactFileString) )
	{
        //Contact 关键字信息
		Matrix<double, Dynamic, Dynamic>ContactImformation = LinearMSTMMSolver::openData(VehicleIn->ContactFileString);
		Matrix<int, Dynamic, Dynamic>ContactImformation2 = LinearMSTMMSolver::openDataInt(VehicleIn->ContactFileString);
        //cout << ContactImformation;
		for (int i = 0; i < ContactImformation.rows(); i++)
		{
            InputContact* InCta = new InputContact;
			InCta->ContactNumber = ContactImformation2(i, 0);
			InCta->ContactType = 0;
            if ( (ContactImformation(i, 5)<1e-5)  &&  (ContactImformation(i, 6)<1e-5) )
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
			int k = 1;
            //主从面节点号
            for (int j = 0; j < ((ls->AllSetSegment[InCta->MasterNodeSetId].SetSegmentNodeID.cols()-1)/4); j++)
            {
				Matrix<int, 4, 1> SetSegmentRow = ls->AllSetSegment[InCta->MasterNodeSetId].SetSegmentNodeID.block<1, 4>(0, k).adjoint();
				(void)InCta->MasterContactNode.insert(make_pair((j + 1), SetSegmentRow));
				k += 4;
            };
            for (int n = 0; n < ls->AllSetNode[InCta->SlaveNodeSetId].SetNodeID.rows(); n++)
            {
				(void)InCta->SlaveContactNode.insert(make_pair((n + 1), ls->AllSetNode[InCta->SlaveNodeSetId].SetNodeID.row(n).adjoint()));
            };
			(void)IAD->InputAllContact.insert(make_pair(InCta->ContactNumber, (*InCta)));
            delete InCta;
            InCta = nullptr;
		}
		
	}

	InputConstraint* InConstraint = new InputConstraint;
    //边界约束条件信息
    if ( 1==isFileExists(VehicleIn->BoundaryFileString) )
    {
        Matrix<int, Dynamic, Dynamic>BoundaryIntImformation = LinearMSTMMSolver::openDataInt(VehicleIn->BoundaryFileString);
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
    if ( 1==isFileExists(VehicleIn->RigidWallFileString) )
    {
        Matrix<double, Dynamic, Dynamic>RigidWallImformation1 = LinearMSTMMSolver::openData(VehicleIn->RigidWallFileString);
        Matrix<int, Dynamic, Dynamic>RigidWallImformation2 = LinearMSTMMSolver::openDataInt(VehicleIn->RigidWallFileString);
        for (int i = 0; i < RigidWallImformation1.rows(); i++)
        {
			InputRigidWallContact* InRigidWall = new InputRigidWallContact;
            InRigidWall->ContactNumber = RigidWallImformation2(i, 0);
            InRigidWall->NodeSetID = RigidWallImformation2(i, 1);
            if ( RigidWallImformation1(i, 8) <1e-5 )
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
	if (1 == isFileExists(VehicleIn->ForceBOUNDARYFileString))
	{
		Matrix<int, Dynamic, Dynamic>ForceBOUNDARYImformation = LinearMSTMMSolver::openDataInt(VehicleIn->ForceBOUNDARYFileString);
		Matrix<int, Dynamic, Dynamic>ForceSetNodeImformation = LinearMSTMMSolver::openDataInt(VehicleIn->ForceSetNodeFileString);
		Matrix<double, Dynamic, Dynamic>ForceFileImformation = LinearMSTMMSolver::openData(VehicleIn->ForceFileString);
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
	(void)remove(VehicleIn->DefineCurveFileString.c_str());
	(void)remove(VehicleIn->HourglassFileString.c_str());
	(void)remove(VehicleIn->SecBeamFileString.c_str());
	(void)remove(VehicleIn->EleShFileString.c_str());
	(void)remove(VehicleIn->EleBFileString.c_str());
	(void)remove(VehicleIn->BoundaryFileString.c_str());
	(void)remove(VehicleIn->SetFileString.c_str());
	(void)remove(VehicleIn->SlaveNodeFileString.c_str());
	(void)remove(VehicleIn->EleSoFileString.c_str());
	(void)remove(VehicleIn->MasterNodeFileString.c_str());
	(void)remove(VehicleIn->NodeVelocityFileString.c_str());
	(void)remove(VehicleIn->SecSolidFileString.c_str());
	(void)remove(VehicleIn->PartFileString.c_str());
	(void)remove(VehicleIn->NodeFileString.c_str());
	(void)remove(VehicleIn->TimeIncrementFileString.c_str());
	(void)remove(VehicleIn->ComputingTimeFileString.c_str());
	(void)remove(VehicleIn->PlaFileString.c_str());
	(void)remove(VehicleIn->ElaFileString.c_str());
	(void)remove(VehicleIn->BoundarySetFileString.c_str());
	(void)remove(VehicleIn->WallSlaveNodeFileString.c_str());
	(void)remove(VehicleIn->LoadNodeFileString.c_str());
	(void)remove(VehicleIn->SetNodeFile1String.c_str());
	(void)remove(VehicleIn->SetNodeFile2String.c_str());
	(void)remove(VehicleIn->SegmentSetFile1String.c_str());
	(void)remove(VehicleIn->SegmentSetFile2String.c_str());
	(void)remove(VehicleIn->LoadBodyYFileString.c_str());
	(void)remove(VehicleIn->LoadBodyZFileString.c_str());
	(void)remove(VehicleIn->ContactFileString2.c_str());
	(void)remove(VehicleIn->SecShellFileString2.c_str());
	(void)remove(VehicleIn->RigidWallFileString2.c_str());
	(void)remove(VehicleIn->SecShellFileString.c_str());
	(void)remove(VehicleIn->RigidWallFileString.c_str());
	(void)remove(VehicleIn->ContactFileString.c_str());

	delete VehicleIn;
	VehicleIn = nullptr;

    return IAD;
}

VehicleInformation::VehicleInformation(void)
{
	SetNodeId1 = 0;
	SetNodeId2 = 0;
	SegmentSetId1 = 0;
	PanduanSetNode = 0;
	PanduanSegmentSetNode = 0;
	AdditionalDigit = "1";
	PanduanSecondpart = 0;
};
DummyInformation::DummyInformation(void)
{
	Multibody = "MB";
};
KFilePart::KFilePart(void)
{
	Pid = 0;
	SectionID = 0;
	Mid = 0;
};
sectionbeam::sectionbeam(void)
{
	secidbeam = 0;
	TS = 0;
	TT = 0;
};
sectionshell::sectionshell(void)
{
	secidshell = 0;
	T1 = 0;
	T2 = 0;
	T3 = 0;
	T4 = 0;
};
Velocity::Velocity(void)
{
	SetType = 3;     // 1: part set ID
				// 2: part ID
				// 3: node set ID
	SetNodeid = 0;
	XVelocity = 0;
	YVelocity = 0;
	ZVelocity = 0;
};
SetNode::SetNode(void)
{
	SetType = 4;
	SetId = 0; //set 集号
	(void)SetNodeID.setZero();  //set 集节点号
};
SetSegmentNode::SetSegmentNode(void)
{
	SetType = 0;
	SetSegmentId = 0; //SetSegment集号
	(void)SetSegmentNodeID.setZero();  //SetSegment集节点号
};
LoadBodyZ::LoadBodyZ(void)
{
	LoadBodyZCurveID = 0;
	LoadCurveScaleFactor = 0;
};
LoadBodyY::LoadBodyY(void)
{
	LoadBodyYCurveID = 0;
	LoadCurveScaleFactor = 0;
};
LoadBodyX::LoadBodyX(void)
{
	LoadBodyXCurveID = 0;
	LoadCurveScaleFactor = 0;
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

MBNode::MBNode(void)
{
	NodeID = 0;
	NodeCoordinates.fill(0);
};
MBSetNode::MBSetNode(void)
{
	SetType = 0;
	SetId = 0;
	SetNodeID.fill(0);
};
MBSetSegmentNode::MBSetSegmentNode(void)
{
	SetType = 0;
	SetSegmentId = 0;
	SetSegmentNodeID.fill(0);
};

//DynamicCalculation* InputFileProject::setTimeParameters()
//{
//	DynamicCalculation* DC = new DynamicCalculation;
//
//	QString FilePath = QLatin1String("D:/MSTMMSim/MSTMMSimCenter/src/Mod/VehicleCollision/Gui/Parameters.xml");
//	QDomDocument XmlDoc;				///<将XML文件加载到内存中
//	double ComputingTime;					///<计算时间
//	double TimeIncrement;					///<时间步长
//
//	XmlDoc.clear();
//	QFile XmlFile(FilePath);
//	if (!XmlFile.open(QIODevice::ReadOnly))
//	{
//		XmlFile.close();
//	}
//	if (!XmlDoc.setContent(&XmlFile))
//	{
//		XmlFile.close();
//	}
//	XmlFile.close();
//
//	//找到节点
//	QDomElement TimeParametersElement = XmlDoc.documentElement().firstChildElement(QLatin1String("TimeParameters"));
//	QDomElement ComputingTimeElement = TimeParametersElement.firstChildElement(QLatin1String("ComputingTime"));
//	QDomElement TimeIncreElement = TimeParametersElement.firstChildElement(QLatin1String("TimeIncre"));
//
//	//读取节点数据并转换类型
//	ComputingTime = ComputingTimeElement.text().toDouble();
//	TimeIncrement = TimeIncreElement.text().toDouble();
//
//	DC->ComputingTime = ComputingTime;
//	DC->TimeIncrement = TimeIncrement;
//
//	cout << "读文件DC->ComputingTime=" << DC->ComputingTime << endl;
//	return DC;
//};
InputFileProject::InputFileProject(void)
{
	fp = 0;
};