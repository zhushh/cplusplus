#include "FuErDai.h"
#include "Account.h"
#include <iostream>
using std::string;

// �������ֱ�Ϊ�����������������֡������Ʋ�
FuErDai::FuErDai(const string& name, const string& dadName, double balance)
:Account(dadName, balance) {
	name_ = name;   // ��ʼ������������ 
}
//  ��ȡ����������
string FuErDai::getName() const {
	return name_;   // ���ظ��������� 
}
// ��ȡ�������Ʋ�
double FuErDai::getBalance() const {
	return Account::getBalance();   // ���ظ������ĲƲ� 
}
// �޸ĸ���������
void FuErDai::setName(string name) {
	name_ = name;
}
// �޸ĸ������Ʋ�
void FuErDai::setBalance(double balance) {
	Account::setBalance(balance);
}

