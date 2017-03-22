#include "GayFoolShy.h"
#include "FuErDai.h"
#include "GuanErDai.h"
#include <iostream>
using std::string;

// �������ֱ�Ϊ�߸�˧���֡����׵����֡����׵��Ʋ������ɵ����֡����ɵ��Ʋ�
GayFoolShy::GayFoolShy(const string& name, const string& fName, double fBalance,
		            const string& gName, double gBalance)
:FuErDai(name, fName, fBalance), GuanErDai(name, gName, gBalance) {
	GayFoolShy::name_ = name;
}
// ��ȡ�߸�˧����
string GayFoolShy::getName() const {
	return GayFoolShy::name_;
}
// ��ȡ�߸�˧�Ʋ�
double GayFoolShy::getBalance() const {
	return FuErDai::getBalance() + GuanErDai::getBalance();
}

