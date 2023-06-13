#pragma once
#include "IClude.h"
/**
 * @file InputDate.h
 * @brief 所有模型初始信息头文件。
 */

 /**
  * @brief 材料模型输入信息类
  *
  * @details 目前支持线弹性材料和率无关双线性弹塑性材料。
  *
  */
class InputMaterial
{
public:
    int MaterialID;///<表示第几种材料
    int MaterialType;///<材料类型1代表弹性、2代表双线性、3代表多线性
    double Density;///<密度
    double ElasticModulu;///<弹性模量
    double PoissonsRatio;///<泊松比
    double InitialYieldStress;///<初始屈服应力
    double MixedHardeningParameter;///<混合硬化参数
    double TangentialModulus;///<切线模量
    Matrix<double, Dynamic, 2> StrainStressCurve;///<多线性材料应力应变参数，第一列是应变，第二列为对应的应力,当材料不是多线性时，如果没有此参数，则为0//双线性、混合强化、Mises 屈服准则、J2流动理论

    /**
     * @brief 材料模型输入信息初始化函数，给类内的变量赋初值。
     */
    InputMaterial(void);
};

/**
 * @brief 模型节点输入信息类
 *
 * @details 给定节点初始位移、速度、加速度、坐标。
 *
 */
class InputNode//节点初始位移、速度、加速度
{
public:
    int NodeID;//节点编号
    Matrix<double, 3, 1> NodeCoordinates;///<坐标（x,y,z）的值
    Matrix<double, Dynamic, 1> NodeAcceleration;///<前三列分别为（x,y,z）的方向上的线加速度值，后三列分别为（x,y,z）的方向上的角加速度值，Dynamic：梁、壳为6，实体为3
    Matrix<double, Dynamic, 1> NodeVelocity;///<前三列分别为（x,y,z）的方向上的线速度值，后三列分别为（x,y,z）的方向上的角速度值
    Matrix<double, Dynamic, 1> NodeDisplacement;///<前三列分别为（x,y,z）的方向上的线速度值，后三列分别为（x,y,z）的方向上的角速度值

    /**
     * @brief 模型节点输入信息类初始化函数，给类内的变量赋初值。
     */
    InputNode(void);
};

/**
 * @brief 模型单元输入信息类
 */
class InputElement
{
public:
    int InElementID;///<单元编号
    int ElementTypeID;///<单元类型编号，0表示8节点实体，1代表4节点壳，2代表2节点欧拉梁
    int MaterialID;///<材料编号,表示第几种材料
    Matrix<double, Dynamic, 3> ElementNodeCoordinates;///<xyz坐标；自己拼出，Dynamic,数等于节点数
    Matrix<int, Dynamic, 1> ElementNodeID;///<节点编号；ElementGeometricParameter;Dynamic,数等于节点数
    Matrix<double, 2, 1>  ElementGeometricParameter;///<梁单元的长、宽、高,可以改成beam。。。。
    Matrix<double, 1, 3> ReferencePoint;///<梁单元得参考点坐标
    Matrix<double, 3, 1> ElementBodyForce;///<x，y，z三个方向的体力，例如重力
    Matrix<double, 4, 1> ShellGeometricParameter;///<对于梁Dynamic应该是4

    /**
     * @brief 模型单元输入信息类初始化函数，给类内的变量赋初值。
     */
    InputElement(void);
};

/**
 * @brief 模型约束条件输入信息类
 */
class InputConstraint
{
public:
    int ConstraintType;///<0表示给定位移，1表示给定载荷
    int ConstraintNodeID;///<约束的节点号
    Matrix<int, Dynamic, 1 > ConstraintNodeDofID;///<存储被约束的自由度，xyz及对应转角分别为1，2，3，4，5，6，对于Dynamic个数为给定力或位移的个数，实体最多为3，梁壳最多为6
    Matrix<double, Dynamic, 1> NodeExternalConstraint;///<后面分别分别为给定约束或给定自由度上的载荷，完全约束 就是0，

    /**
     * @brief 模型约束条件类初始化函数，给类内的变量赋初值。
     */
    InputConstraint(void);
};

/**
 * @brief 模型单元间接触输入信息类
 */
class InputContact
{
public:
    int SlaveNodeSetType;///< 4: node set ID for node to surface contact.                        
    int MasterNodeSetType;///< 0: segment set ID for surface-to-surface contact.
    int SlaveNodeSetId;///< 从节点集编号
    int MasterNodeSetId;///< 主节点集编号
    int ContactNumber;///<接触对编号
    int ContactType;///<接触类型0表示有限元单元间接触，1表示FEM和假人间接触
    double StaticFrictionCoefficient;///<静摩擦因子
    double  DynamicFrictionCoefficient;///<动摩擦系数
    int FrictionJudgment;//0表示有摩擦，1表示无摩擦
    double NormalPenaltyFactor;///<法向罚因子
    double TangentialPenaltyFactor;///<切向罚因子
    double NREps;///<NR迭代的精度
    map<int, Matrix<int, Dynamic, 1>> MasterContactNode;///<第一个int为单元号，Matrix为单元接触表面节点号
    map<int, Matrix<int, Dynamic, 1>> SlaveContactNode;///<int为单元号，Matrix为单元表面节点号,节点号要按逆时针给出

    /**
     * @brief 模型单元间接触输入信息类初始化函数，给类内的变量赋初值。
     */
    InputContact(void);
};

/**
 * @brief 模型有限元单元与刚体元件间接触输入信息类
 */
class InputFEMtoMBContact
{
public:
    int SlaveNodeSetId;///< 4: node set ID for node to surface contact.       
    int MasterNodeSetId;;///< 0: segment set ID for surface-to-surface contact.
    int ContactNumber;///<接触对编号
    int ContactType;///<0表示有限元单元间接触，1表示FEM和假人间接触
    double StaticFrictionCoefficient;///<静摩擦因子
    double  DynamicFrictionCoefficient;///<动摩擦系数
    int FrictionJudgment;///<0表示有摩擦，1表示无摩擦
    double NormalPenaltyFactor;///<静摩擦因子
    double TangentialPenaltyFactor;///<切向罚因子
    double NREps;///<NR迭代的精度
    map<int, Matrix<int, Dynamic, 1>> MasterContactNode;///<第一个int为单元号，Matrix为单元接触表面节点号
    map<int, Matrix<int, Dynamic, 1>> SlaveContactNode;///<int为单元号，Matrix为单元表面节点号,节点号要按逆时针给出

    /**
     * @brief 模型有限元单元与刚体元件间接触输入信息类初始化函数，给类内的变量赋初值。
     */
    InputFEMtoMBContact(void);
};


/**
 * @brief 模型有限元单元与刚性墙间接触输入信息类
 */
class InputRigidWallContact
{
public:
    int  NodeSetID; ///<Nodal set ID containing slave nodes
    int ContactNumber;///<接触对编号
    double Length;///<长
    double Width;///<宽
    Matrix<double, 3, 1>  RigidWallNormal;///<刚性墙的法向量
    Matrix<double, 3, 1>  RigidWallTangential;///<刚性墙的切向量
    Matrix<double, 3, 1>  RigidWallorigin;///<刚性墙的原点
    double FrictionCoefficient;///<摩擦系数
    int FrictionJudgment;///<0表示有摩擦，1表示无摩擦
    map<int, Matrix<int, Dynamic, 1>> SlaveContactNode;///<int为从节点集号，矩阵存储从节点集包好的节点号

    /**
     * @brief 模型有限元单元与刚性墙间接触输入信息类初始化函数，给类内的变量赋初值。
     */
    InputRigidWallContact(void);
};


/**
 * @brief 模型动力学计算参数信息类
 */
class DynamicCalculation
{
public:
    double ComputingTime;///<计算总时长
    double TimeIncrement;///<步长
    double OutIncrement;///<输出步长

    /**
     * @brief 模型动力学计算参数信息类初始化函数，给类内的变量赋初值。
     */
    DynamicCalculation(void);
};

/**
 * @brief 模型刚体元件输入信息类
 */
class inputRigidBody
{
public:
    int RigidBodySetID;
    int RigidBodyType;
    int RigidBodyID;
    string HumanID;///<刚体名字
    Matrix<double, 6, 1>ZbO;///<加速度状态矢量
    Matrix<double, 3, 1> Fc;///<外力
    Matrix<double, 3, 1> Mc;///<外弯矩
    Matrix<double, 3, 1> RI1;///<1号输入点在全局坐标系中的投影
    Matrix<double, 3, 1>RI2;///<2号输入点在总体坐标系上的投影
    Matrix<double, 3, 1>RI3;///<3号输入点在总体坐标系上的投影
    Matrix<double, 3, 1>RO;///<1号输出点在总体坐标系上的投影
    Matrix<double, 3, 1>RC;///<质心在总体坐标系上的投影
    Matrix<double, 3, 3>J;///<转动惯量
    Matrix<double, 3, 1>OuO;///<角速度在总体坐标系下的投影
    Matrix<double, 3, 1>VO;///<1号输入点的线速度在总体坐标系下的投影
    map<int, Matrix<double, 1, 3>> MeshCoor;///<网格信息
    double M;///<质量
    double OuLa1;///<0
    double OuLa2;///<0
    double OuLa3;///<0
    double OuLa4;///<1

    /**
     * @brief 模型刚体元件输入信息类初始化函数
     */
    //inputRigidBody(void);
};

/**
 * @brief 模型柱铰元件输入信息类
 */
class inputColumnHinge
{
public:
    int ColumnHingeID;///<元件编号
    Matrix<double, 3, 1>RO;///<输出点在全局坐标系的位矢
    Matrix<double, 3, 1>RI;///<输入点在全局坐标系的位矢
    Matrix<double, 3, 1> SeiTa0;///< 关节初始角度
    Matrix<double, 3, 1>WR;///<角速度
    Matrix < double, 1, 3> K;///<刚度
    Matrix < double, 1, 3> C;///<阻尼
    double Md;///<控制力矩

    /**
     * @brief 模型柱铰元件输入信息类初始化函数
     */
    //inputColumnHinge(void);
};

/**
 * @brief 模型球铰元件输入信息类
 */
class inputBallJoint
{
public:
    int BallJointID;
    Matrix<double, 3, 1>RO;///<输出点在全局坐标系位矢
    Matrix<double, 3, 1>RI;///<输入点在全局坐标系位矢
    Matrix < double, 3, 3> K;///<刚度
    Matrix < double, 3, 3> C;///<阻尼
    Matrix< double, 3, 1> Md;///<控制力矩
    Matrix<double, 3, 1> SeiTa0;// 关节初始角度
    Matrix<double, 3, 1>WR;//角速度

    /**
     * @brief 模型球铰元件输入信息类初始化函数
     */
    //inputBallJoint(void);
};


/**
 * @brief 模型所有输入信息类
 */
class InputAllDate
{
public:
    map<int, InputElement > InputAllElement;///<每个pair中的key存储单元编号，value存储该单元的所有信息
    map<int, InputMaterial> InputAllMaterial;///<每个pair中的key存储材料编号，value存储该材料的所有信息
    multimap<int, InputConstraint> InputAllConstraint;///<每个pair中的key存储约束节点编号，value存储该节点的所有约束信息
    map<int, InputContact> InputAllContact;///<每个pair中的key存储接触对编号，value存储该接触对的所有信息
    map<int, InputRigidWallContact> InputAllRigidContact;///<每个pair中的key存储接触对编号，value存储该接触对的所有信息
    map<int, InputNode> InputAllNode;///<每个pair中的key  存储节点编号，value存储该节点的所有信息
    map<int, inputRigidBody>inputAllRigidBody;///<key代表对象编号，value代表key对象拥有的属性
    map<int, inputColumnHinge>inputAllColumnHinge;///<key代表对象编号，value代表key对象拥有的属性
    map<int, inputBallJoint>inputAllBallJoint;///<key代表对象编号，value代表key对象拥有的属性
    map<int, InputFEMtoMBContact>InputAllFEMtoMBContact;///<每个pair中的key存储接触对编号，value存储该接触对的所有信息
    unsigned int ConnectNode;///<和刚体模型所绑定的节点的编号
    double AF;///<瑞利阻尼系数
    double BT;///<瑞利阻尼系数

/**
 * @brief 模型所有输入信息类的初始化函数
 */
    InputAllDate(void);
};
