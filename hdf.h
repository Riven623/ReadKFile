
#pragma once
#include "IClude.h"
#include "H5Cpp.h"
using namespace H5;


int hdfReadAnimation(const std::string& H5fileToOpen,const int &MATrows, const int & MATcols)
{
	//���ļ�
	H5File file(H5fileToOpen, H5F_ACC_RDONLY);
	Matrix<double, Dynamic, Dynamic> data_outMAT;
	//��ʼ������
	data_outMAT.setZero(MATrows, MATcols);
	for (int j = 0; j < MATcols; j++)
	{	
		//�����ݼ�
		DataSet dataset = file.openGroup("Animation").openDataSet(QString::number(j).toStdString());
		//��ȡ���ݼ���Ϣ
		DataSpace dataspace = dataset.getSpace();
		//��ȡ���ݼ�ά��
		 int rank = dataspace.getSimpleExtentNdims();
		//��ȡ���ݼ�ά�ȴ�С
		hsize_t *dims_out=new hsize_t[rank];
		int ndims = dataspace.getSimpleExtentDims(dims_out, NULL);
		//��ȡ���ݼ�
		double* data_out = new double[dims_out[0]];
		dataset.read(data_out, PredType::NATIVE_DOUBLE);
		for (int i = 0; i < MATrows; i++)
		{
			data_outMAT(i, j) = data_out[i];
		}
		delete[]data_out;
	}
	//д��txt
	ofstream data_outFILE;
	data_outFILE.open("H5AnimationdataFILE.txt");
	data_outFILE << data_outMAT;
	data_outFILE.close();
	//�ر��ļ�
	file.close();

	return 1;
}

int hdfReadCurve(const std::string& H5fileToOpen, const int& MATrows, const int& MATcols)
{
	//���ļ�
	H5File file(H5fileToOpen, H5F_ACC_RDONLY);
	Matrix<double, Dynamic, Dynamic> data_outMAT;
	//��ʼ������
	data_outMAT.setZero(MATrows, MATcols);
	for (int j = 0; j < MATcols; j++)
	{
		//�����ݼ�
		DataSet dataset = file.openGroup("Curve").openDataSet(QString::number(j).toStdString());
		//��ȡ���ݼ���Ϣ
		DataSpace dataspace = dataset.getSpace();
		//��ȡ���ݼ�ά��
		int rank = dataspace.getSimpleExtentNdims();
		//��ȡ���ݼ�ά�ȴ�С
		hsize_t* dims_out = new hsize_t[rank];
		int ndims = dataspace.getSimpleExtentDims(dims_out, NULL);
		//��ȡ���ݼ�
		double* data_out = new double[dims_out[0]];
		dataset.read(data_out, PredType::NATIVE_DOUBLE);
		for (int i = 0; i < dims_out[0]; i++)
		{
			data_outMAT(i, j) = data_out[i];
		}
		delete[]data_out;
	}
	//д��txt
	ofstream data_outFILE;
	data_outFILE.open("H5CurvedataFILE.txt");
	data_outFILE << data_outMAT;
	data_outFILE.close();
	//�ر��ļ�
	file.close();

	return 1;
}





