#include "GuanErDai.h"
#include "Account.h"
#include <iostream>
using std::string;

GuanErDai::GuanErDai() {}
// �����ֱ�Ϊ�ٶ��������������֡������Ʋ�
GuanErDai::GuanErDai(const string& name, const string& dadName, double balance)
:Account(dadName, balance) {
	GuanErDai::name_ = name;
}
// ��ȡ�ٶ�������
string GuanErDai::getName() const {
	return GuanErDai::name_;
}
// ��ȡ�ٶ����Ʋ�
double GuanErDai::getBalance() const {
	return Account::getBalance();
}
// �޸Ĺٶ�������
void GuanErDai::setName(string name) {
	GuanErDai::name_ = name;
}
// �޸Ĺٶ����Ʋ�
void GuanErDai::setBalance(double balance) {
	Account::setBalance(balance);
}

