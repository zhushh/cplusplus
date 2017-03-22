#ifndef FUERDAI_H
#define FUERDAI_H

#include "Account.h"
#include <iostream>
using std::string;

class FuErDai:public Account {
	public:
		// �������ֱ�Ϊ�����������������֡������Ʋ�
		FuErDai(const string& name, const string& dadName, double balance);
		string getName() const;   //  ��ȡ����������
		double getBalance() const;   // ��ȡ�������Ʋ�
		void setName(string name);   // �޸ĸ���������
		void setBalance(double balance);   // �޸ĸ������Ʋ�
	private:
		string name_; 
};

#endif

