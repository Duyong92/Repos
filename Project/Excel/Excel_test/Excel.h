#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// CSV.cpp
class CExcel {
private:
	unsigned int m_unRow;
	unsigned int m_unColumn;
	std::vector<std::string> m_vsCell;
	std::vector<std::vector<std::string>> m_vvsExcel;
public:
	CExcel() : m_unRow(0), m_unColumn(0) {};

	void SetCSV(std::string _path);
	void SetCSV_utf8(std::string _path);

	unsigned int GetMaxRow();
	unsigned int GetMaxColumn();

	std::vector<std::vector<std::string>> GetExcel();
};


