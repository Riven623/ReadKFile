#pragma once
#include "IClude.h"

class InputMaterial
{
public:
    int MaterialID;//表示第几种材料
    int MaterialType;//材料类型1代表弹性、2代表双线性、3代表多线性
    double Density;//密度
    double ElasticModulu;//弹性模量
    double PoissonsRatio;//泊松比
    double InitialYieldStress;//初始屈服应力
    double MixedHardeningParameter;//混合硬化参数
    double TangentialModulus;//切线模量
    Matrix<double, Dynamic, 2> StrainStressCurve;//多线性材料应力应变参数，第一列是应变，第二列为对应的应力,当材料不是多线性时，如果没有此参数，则为0
//双线性、混合强化、Mises 屈服准则、J2流动理论
    InputMaterial();
};


class InputNode//节点初始位移、速度、加速度
{
public:
    int NodeID;//节点编号
    Matrix<double, 3, 1> NodeCoordinates;//坐标（x,y,z）的值
    Matrix<double, Dynamic, 1> NodeAcceleration;//前三列分别为（x,y,z）的方向上的线加速度值，后三列分别为（x,y,z）的方向上的角加速度值，Dynamic：梁、壳为6，实体为3
    Matrix<double, Dynamic, 1> NodeVelocity;//前三列分别为（x,y,z）的方向上的线速度值，后三列分别为（x,y,z）的方向上的角速度值
    Matrix<double, Dynamic, 1> NodeDisplacement;//前三列分别为（x,y,z）的方向上的线速度值，后三列分别为（x,y,z）的方向上的角速度值
    InputNode();
};

class InputElement
{
public:
    int ElementID;//单元编号
    int ElementTypeID;//单元类型编号，0表示8节点实体，1代表4节点壳，2代表2节点欧拉梁
    int MaterialID;//材料编号,表示第几种材料
    Matrix<double, Dynamic, 3> ElementNodeCoordinates;//xyz坐标；自己拼出，Dynamic,数等于节点数
    Matrix<int, Dynamic, 1> ElementNodeID;//节点编号；ElementGeometricParameter;Dynamic,数等于节点数
    Matrix<double, 2, 1>  ElementGeometricParameter;//梁单元的长、宽、高,可以改成beam。。。。
    Matrix<double, 1, 3> ReferencePoint;//梁单元得参考点坐标
    Matrix<double, 3, 1> ElementBodyForce;//x，y，z三个方向的体力，例如重力
    Matrix<double, 4, 1> ShellGeometricParameter;// 对于梁Dynamic应该是4
    Matrix<double, 4, 3> ShellNodalNormal;

    InputElement();
};

class InputConstraint
{
public:
    int ConstraintType;//0表示给定位移，1表示给定载荷
    int ConstraintNodeID;//约束的节点号
    Matrix<int, Dynamic, 1 > ConstraintNodeDofID;//存储被约束的自由度，xyz及对应转角分别为1，2，3，4，5，6，对于Dynamic个数为给定力或位移的个数，实体最多为3，梁壳最多为6
    Matrix<double, Dynamic, 1> NodeExternalConstraint;//后面分别分别为给定约束或给定自由度上的载荷，完全约束 就是0，
    InputConstraint();
};

class InputCouplingPoint
{
public:
    int CouplingPointID; //节点的自由度完全完全一致的节点集，即绑定约束
    vector<int> CPNodeID;//耦合的节点编号 ，第一个数字为主节点编号
    int CPDof;//耦合的自由度（1-6），分别代表三个方向的位移、三个方向的转角
    InputCouplingPoint();
};

class InputCouplingEquation
{
public:
    int CouplingEquationID; //约束方程编号
    Matrix<int, 14, 1> CE;
    /*第一个值为约束方程常数，第二个为第一个约束节点编号，第三个为该节点的自由度（1，2，3，4，5，6），第四个为该自由度的系数，
                      *第五个为第二个约束节点编号，第六个为该节点的自由度（1，2，3，4，5，6），第七个为该自由度的系数，
                      第八个为第三个约束节点编号，第九个为该节点的自由度（1，2，3，4，5，6），第10到14个为该自由度的（10系数，11节点编号、12自由度（1，2，3）、13节点编号、14自由度（1，2，3））
                      *CE,1,0,626,UX,1,2328,UX,-1,1,ROTY,-ABS(NZ(626)-NZ(2328))
     */
    InputCouplingEquation();
};

class InputContact
{
public:
	int SlaveNodeSetType;// 4: node set ID for node to surface contact.                        
	int MasterNodeSetType;// 0: segment set ID for surface-to-surface contact.
	int SlaveNodeSetId;
	int MasterNodeSetId;
    int ContactNumber;//接触对编号
    int ContactType;//0表示有限元单元间接触，1表示FEM和假人间接触
    double StaticFrictionCoefficient;
    double  DynamicFrictionCoefficient;//摩擦系数
    int FrictionJudgment;//0表示有摩擦，1表示无摩擦
    double NormalPenaltyFactor;
    double TangentialPenaltyFactor;
    double NREps;//罚因子,NR迭代的精度
    int Dummy;//0代表有限元单元间接触，1代表有限元单元和假人接触
    map<int, Matrix<int, Dynamic, 1>> MasterContactNode;//第一个int为单元号，Matrix为单元接触表面节点号
    map<int, Matrix<int, Dynamic, 1>> SlaveContactNode;//int为单元号，Matrix为单元表面节点号,节点号要按逆时针给出
    InputContact();
};

class InputRigidWallContact
{
public:
	int  NodeSetID; //Nodal set ID containing slave nodes
    int ContactNumber;//接触对编号
    double Length;//长
    double Width;//宽
    Matrix<double, 3, 1>  RigidWallNormal;//刚性墙的法向量
    Matrix<double, 3, 1>  RigidWallTangential;//刚性墙的切向量
    Matrix<double, 3, 1>  RigidWallorigin;//刚性墙的原点
    double FrictionCoefficient;//摩擦系数
    int FrictionJudgment;//0表示有摩擦，1表示无摩擦
    map<int, Matrix<int, Dynamic, 1>> SlaveContactNode;//int为从节点集号，矩阵存储从节点集包好的节点号
    InputRigidWallContact();
};


class DynamicCalculation
{
public:
    double ComputingTime;//计算总时长
    double TimeIncrement;//步长
    DynamicCalculation();
};

class inputRigidBody
{
public:
    string HumanID;
    int RigidBodySetID;
	int RigidBodyType;//1代表
	int RigidBodyID;
	Matrix<double, 6, 1>ZbO;//加速度状态矢量
	Matrix<double, 3, 1> Fc;//外力
	Matrix<double, 3, 1> Mc;//外弯矩
	Matrix<double, 3, 1> RI1;//1号输入点在全局坐标系中的投影
	Matrix<double, 3, 1>RI2;//2号输入点在总体坐标系上的投影
	Matrix<double, 3, 1>RI3;//3号输入点在总体坐标系上的投影
	Matrix<double, 3, 1>RO;//1号输出点在总体坐标系上的投影
	Matrix<double, 3, 1>RC;//质心在总体坐标系上的投影
	Matrix<double, 3, 3>J;//转动惯量
	Matrix<double, 3, 1>OuO;//角速度在总体坐标系下的投影
	Matrix<double, 3, 1>VO;//1号输入点的线速度在总体坐标系下的投影
	map<int, Matrix<double, 1, 3>> MeshCoor;
	double M;//质量
	double OuLa1;//0
	double OuLa2;//0
	double OuLa3;//0
	double OuLa4;//1
	inputRigidBody() = default;
};

class inputColumnHinge
{
public:
	int ColumnHingeID;
	Matrix<double, 3, 1>RO;//输出点在全局坐标系的位矢
	Matrix<double, 3, 1>RI;//输入点在全局坐标系的位矢
	Matrix<double, 3, 1> SeiTa0;// 关节初始角度
	Matrix<double, 3, 1>WR;//角速度
	Matrix < double, Dynamic, Dynamic> MeshCoor;//网格点的坐标
	Matrix < double, 1, 3> K;//刚度
	Matrix < double, 1, 3> C;//阻尼
	double Md;//控制力矩

};

class inputBallJoint
{
public:
	int BallJointID;
	Matrix<double, 3, 1>RO;//输出点在全局坐标系位矢
	Matrix<double, 3, 1>RI;//输入点在全局坐标系位矢
	Matrix< double, 3, 3> K;
	Matrix< double, 3, 3> C;
	Matrix< double, 3, 1> Md;
	Matrix<double, 3, 1> SeiTa0;// 关节初始角度
	Matrix<double, 3, 1>WR;//角速度

};

class InputFEMtoMBContact
{
public:
	int SlaveNodeSetId;
	int MasterNodeSetId;
	int ContactNumber;//接触对编号
	int ContactType;//0表示有限元单元间接触，1表示FEM和假人间接触
	double StaticFrictionCoefficient;
	double  DynamicFrictionCoefficient;//摩擦系数
	int FrictionJudgment;//0表示有摩擦，1表示无摩擦
	double NormalPenaltyFactor;
	double TangentialPenaltyFactor;
	double NREps;//罚因子,NR迭代的精度
	int Dummy;//0代表有限元单元间接触，1代表有限元单元和假人接触
	map<int, Matrix<int, Dynamic, 1>> MasterContactNode;//第一个int为单元号，Matrix为单元接触表面节点号
	map<int, Matrix<int, Dynamic, 1>> SlaveContactNode;//int为单元号，Matrix为单元表面节点号,节点号要按逆时针给出
	InputFEMtoMBContact();
};

class InputAllDate
{
public:
    map<int, InputElement > InputAllElement;//每个pair中的key存储单元编号，value存储该单元的所有信息
    map<int, InputMaterial> InputAllMaterial;//每个pair中的key存储材料编号，value存储该材料的所有信息
    multimap<int, InputConstraint> InputAllConstraint;//每个pair中的key存储约束节点编号，value存储该节点的所有约束信息
    map<int, InputContact> InputAllContact;//每个pair中的key存储接触对编号，value存储该接触对的所有信息
    map<int, InputRigidWallContact> InputAllRigidContact;//每个pair中的key存储接触对编号，value存储该接触对的所有信息
    map<int, InputNode> InputAllNode;//每个pair中的key  存储节点编号，value存储该节点的所有信息
    map<int, InputCouplingPoint> InputAllCP;
    map<int, InputCouplingEquation> InputAllCE;
    map<int, inputRigidBody>inputAllRigidBody;//key 代表对象编号，value代表key对象拥有的属性
    map<int, inputColumnHinge>inputAllColumnHinge;//key 代表对象编号，value代表key对象拥有的属性
    map<int, inputBallJoint>inputAllBallJoint;//key 代表对象编号，value代表key对象拥有的属性
    map<int, InputFEMtoMBContact>InputAllFEMtoMBContact;
    double AF;
    double BT;//瑞利阻尼系数
    unsigned int ConnectNode;
    InputAllDate();
    
    // map<int, InputDummy> InputDummy;
};
