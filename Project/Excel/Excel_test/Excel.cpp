#include "Excel.h"

unsigned int CExcel::GetMaxRow() { return m_unRow; };
unsigned int CExcel::GetMaxColumn() { return m_unColumn; };

std::vector<std::vector<std::string>> CExcel::GetExcel() { return m_vvsExcel; };