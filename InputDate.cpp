#include "InputDate.h"
/**
 * @file InputDate.cpp
 * @brief 模型输入信息各个类的构造函数的源代码。
 */

InputMaterial::InputMaterial(void)
{
	MaterialID = 0;
	MaterialType = 0;
	Density = 0.;
	ElasticModulu = 0.;
	PoissonsRatio = 0.;
	InitialYieldStress = 0.;//初始屈服应力
	MixedHardeningParameter = 0.;//混合硬化参数
	TangentialModulus = 0.;//切线模量
};


InputNode::InputNode(void)
{
	NodeID = 0;
	NodeCoordinates.fill(0.);
}

InputElement::InputElement(void)
{
	InElementID = 0;
	ElementTypeID = 0;
	MaterialID = 0;
	ElementGeometricParameter.fill(0.);
	ReferencePoint.fill(0.);
	ElementBodyForce.fill(0.);
	ShellGeometricParameter.fill(0.);

};

InputConstraint::InputConstraint(void)
{
	ConstraintType = 0;
	ConstraintNodeID = 0;
};


InputContact::InputContact(void)
{
	SlaveNodeSetType = 0;
	MasterNodeSetType = 0;
	SlaveNodeSetId = 0;
	MasterNodeSetId = 0;
	ContactNumber = 0;
	ContactType = 0;
	StaticFrictionCoefficient = 0.;
	DynamicFrictionCoefficient = 0.;
	FrictionJudgment = 0;
	NormalPenaltyFactor = 0.08;
	TangentialPenaltyFactor = 1.;
	NREps = 1.E-6;//罚因子,NR迭代的精度
};

InputRigidWallContact::InputRigidWallContact(void)
{
	NodeSetID = 0;
	ContactNumber = 0;
	Length = 0.;
	Width = 0.;
	RigidWallNormal.fill(0.);
	RigidWallTangential.fill(0.);
	RigidWallorigin.fill(0.);
	FrictionCoefficient = 0.;
	FrictionJudgment = 1;
};

InputFEMtoMBContact::InputFEMtoMBContact(void)
{
	SlaveNodeSetId = 0;
	MasterNodeSetId = 0;
	ContactNumber = 0;
	ContactType = 0;
	StaticFrictionCoefficient = 0.;
	DynamicFrictionCoefficient = 0.;
	FrictionJudgment = 0;
	NormalPenaltyFactor = 0.08;
	TangentialPenaltyFactor = 1.;
	NREps = 1.E-6;//罚因子,NR迭代的精度
};


DynamicCalculation::DynamicCalculation(void)
{
	ComputingTime = 0.;
	TimeIncrement = 0.1;
	OutIncrement = 0.1;
};

InputAllDate::InputAllDate(void)
{
	AF = 0.;
	BT = 0.;//瑞利阻尼系数
	ConnectNode = 1;
};

//inputRigidBody::inputRigidBody(void)
//{
//	RigidBodySetID = 1;
//	RigidBodyType = 1;
//	RigidBodyID = 1;
//	HumanID = 's';///<刚体名字
//	/*ZbO = MXdZero(6, 1);///<加速度状态矢量
//	Fc = MXdZero(3, 1);///<外力
//	Mc = MXdZero(3, 1);///<外弯矩
//	RI1 = MXdZero(3, 1);///<1号输入点在全局坐标系中的投影
//	RI2 = MXdZero(3, 1);///<2号输入点在总体坐标系上的投影
//	RI3 = MXdZero(3, 1);///<3号输入点在总体坐标系上的投影
//	RO = MXdZero(3, 1);///<1号输出点在总体坐标系上的投影
//	RC = MXdZero(3, 1);///<质心在总体坐标系上的投影
//	J = MXdZero(3, 3);///<转动惯量
//	OuO = MXdZero(3, 1);///<角速度在总体坐标系下的投影
//	VO = MXdZero(3, 1);///<1号输入点的线速度在总体坐标系下的投影*/
//	M = 0.;///<质量
//	OuLa1 = 0.;///<0
//	OuLa2 = 0.;///<0
//	OuLa3 = 0.;///<0
//	OuLa4 = 0.;
//};
//
//inputColumnHinge::inputColumnHinge(void)
//{
//	ColumnHingeID = 1;///<元件编号
//	/*RO = MXdZero(3, 1);///<输出点在全局坐标系的位矢
//	RI = MXdZero(3, 1);///<输入点在全局坐标系的位矢
//	SeiTa0 = MXdZero(3, 1);///< 关节初始角度
//	WR = MXdZero(3, 1);///<角速度
//	K = MXdZero(1, 3);///<刚度
//	C = MXdZero(1, 3);///<阻尼*/
//	//Md = 0.;///<控制力矩
//};
//
//inputBallJoint::inputBallJoint(void)
//{
//	BallJointID = 1;
//	/*RO = MXdZero(3, 1);
//	RI = MXdZero(3, 1);
//	K = MXdZero(3, 3);
//	C = MXdZero(3, 3);
//	Md = MXdZero(3, 1);
//	SeiTa0 = MXdZero(3, 1);
//	WR = MXdZero(3, 1);*/
//}