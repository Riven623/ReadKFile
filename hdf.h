
#pragma once
#include "IClude.h"
#include "H5Cpp.h"
using namespace H5;


int hdfReadAnimation(const std::string& H5fileToOpen,const int &MATrows, const int & MATcols)
{
	//打开文件
	H5File file(H5fileToOpen, H5F_ACC_RDONLY);
	Matrix<double, Dynamic, Dynamic> data_outMAT;
	//初始化矩阵
	data_outMAT.setZero(MATrows, MATcols);
	for (int j = 0; j < MATcols; j++)
	{	
		//打开数据集
		DataSet dataset = file.openGroup("Animation").openDataSet(QString::number(j).toStdString());
		//读取数据集信息
		DataSpace dataspace = dataset.getSpace();
		//获取数据集维度
		 int rank = dataspace.getSimpleExtentNdims();
		//获取数据集维度大小
		hsize_t *dims_out=new hsize_t[rank];
		int ndims = dataspace.getSimpleExtentDims(dims_out, NULL);
		//读取数据集
		double* data_out = new double[dims_out[0]];
		dataset.read(data_out, PredType::NATIVE_DOUBLE);
		for (int i = 0; i < MATrows; i++)
		{
			data_outMAT(i, j) = data_out[i];
		}
		delete[]data_out;
	}
	//写入txt
	ofstream data_outFILE;
	data_outFILE.open("H5AnimationdataFILE.txt");
	data_outFILE << data_outMAT;
	data_outFILE.close();
	//关闭文件
	file.close();

	return 1;
}

int hdfReadCurve(const std::string& H5fileToOpen, const int& MATrows, const int& MATcols)
{
	//打开文件
	H5File file(H5fileToOpen, H5F_ACC_RDONLY);
	Matrix<double, Dynamic, Dynamic> data_outMAT;
	//初始化矩阵
	data_outMAT.setZero(MATrows, MATcols);
	for (int j = 0; j < MATcols; j++)
	{
		//打开数据集
		DataSet dataset = file.openGroup("Curve").openDataSet(QString::number(j).toStdString());
		//读取数据集信息
		DataSpace dataspace = dataset.getSpace();
		//获取数据集维度
		int rank = dataspace.getSimpleExtentNdims();
		//获取数据集维度大小
		hsize_t* dims_out = new hsize_t[rank];
		int ndims = dataspace.getSimpleExtentDims(dims_out, NULL);
		//读取数据集
		double* data_out = new double[dims_out[0]];
		dataset.read(data_out, PredType::NATIVE_DOUBLE);
		for (int i = 0; i < dims_out[0]; i++)
		{
			data_outMAT(i, j) = data_out[i];
		}
		delete[]data_out;
	}
	//写入txt
	ofstream data_outFILE;
	data_outFILE.open("H5CurvedataFILE.txt");
	data_outFILE << data_outMAT;
	data_outFILE.close();
	//关闭文件
	file.close();

	return 1;
}





