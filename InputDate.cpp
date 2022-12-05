#include "InputDate.h"
InputMaterial::InputMaterial()
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




InputNode::InputNode()
{
	NodeID = 0;
	NodeCoordinates.fill(0);
}

InputElement::InputElement()
{
	ElementID = 0;
	ElementTypeID = 0;
	MaterialID = 0;
	ElementGeometricParameter.fill(0);
	ReferencePoint.fill(0);
	ElementBodyForce.fill(0);
	ShellGeometricParameter.fill(0);
	ShellNodalNormal.fill(0);
	
};

InputConstraint::InputConstraint()
{
	ConstraintType = 0;
	ConstraintNodeID = 0;
};

InputCouplingPoint::InputCouplingPoint()
{
	CouplingPointID = 1;
	CPDof = 1;
};

InputCouplingEquation::InputCouplingEquation()
{
	CouplingEquationID = 1;
	CE.fill(0);
};

InputContact::InputContact()
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
	Dummy = 0;//0代表有限元单元间接触，1代表有限元单元和假人接触
};

InputFEMtoMBContact::InputFEMtoMBContact()
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
	Dummy = 0;//0代表有限元单元间接触，1代表有限元单元和假人接触
};
InputRigidWallContact::InputRigidWallContact()
{
	NodeSetID = 0;
	ContactNumber = 0;
	Length = 0.;
	Width = 0.;
	RigidWallNormal.fill(0);
	RigidWallTangential.fill(0);
	RigidWallorigin.fill(0);
	FrictionCoefficient = 0.;
	FrictionJudgment = 1;
};




DynamicCalculation::DynamicCalculation()
{
	ComputingTime = 0;
	TimeIncrement = 0.1;
};

InputAllDate::InputAllDate()
{
	AF = 0;
	BT = 0;//瑞利阻尼系数
};