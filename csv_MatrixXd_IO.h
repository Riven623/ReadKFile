#pragma once

#include <iostream>
#include <Eigen>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
using namespace Eigen;
namespace LinearMSTMMSolver
{
	template <class Derived>
	void saveData(std::string filename, const Eigen::MatrixBase<Derived>& matrix) {  //dynamic, doubles
		const static Eigen::IOFormat CSVFormat(Eigen::FullPrecision, Eigen::DontAlignCols, ",", "\n");

		std::ofstream file(filename);

		if (file.is_open()) {
			//simple as cout or as cin, an overloaded operator!
			file << matrix.format(CSVFormat);
			file.close();
		}
	}
	//double 矩阵函数
	Eigen::MatrixXd openData(const std::string& fileToOpen) {
		// read line by line, store each line into a cpp vector!
		// map vector object to eigen: Map(cpp_array) to Matrix

		std::vector<double> matrixEntries;
		// in this object we store the data from the matrix
		std::ifstream matrixDataFile(fileToOpen);
		std::string matrixRowString;
		std::string matrixEntry;
		size_t matrixRowNumber = 0;

		while (getline(matrixDataFile, matrixRowString)) {
			std::stringstream matrixRowStringStream(matrixRowString);

			while (matrixRowStringStream >> matrixEntry){
				matrixEntries.push_back(stod(matrixEntry));  // convert the string to double and fill in the array cpp vector
			}
			matrixRowNumber++;  //update ther col numbers   
		}

		// here the matrixEntries.data() is the pointer to the first memory location at which entries of the vector matrixEntries are stored;
		if (matrixRowNumber != 0)
		{
			return Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / matrixRowNumber);

		};

	}

	//int 矩阵函数
	Eigen::Matrix<int, Dynamic, Dynamic> openDataInt(const std::string& fileToOpen) {
		// read line by line, store each line into a cpp vector!
		// map vector object to eigen: Map(cpp_array) to Matrix

		std::vector<int> matrixEntries;
		// in this object we store the data from the matrix
		std::ifstream matrixDataFile(fileToOpen);
		std::string matrixRowString;
		std::string matrixEntry;
		size_t matrixRowNumber = 0;

		while (getline(matrixDataFile, matrixRowString)) {
			std::stringstream matrixRowStringStream(matrixRowString);

			while (matrixRowStringStream >> matrixEntry) {
				matrixEntries.push_back(stoi(matrixEntry));  // convert the string to double and fill in the array cpp vector
			}
			matrixRowNumber++;  //update ther col numbers   
		}

		// here the matrixEntries.data() is the pointer to the first memory location at which entries of the vector matrixEntries are stored;
		if (matrixRowNumber != 0)
		{
			return Eigen::Map<Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / matrixRowNumber);
		};
	}


}