#ifndef GUANERDAI_H
#define GUANERDAI_H

#include "Account.h"
#include <iostream>
using std::string;

class GuanErDai:private Account {
	public:
		GuanErDai();
		// �����ֱ�Ϊ�ٶ��������������֡������Ʋ�
		GuanErDai(const string& name, const string& dadName, double balance);
		string getName() const;   // ��ȡ�ٶ�������
		double getBalance() const;   // ��ȡ�ٶ����Ʋ�
		void setName(string name);   // �޸Ĺٶ�������
		void setBalance(double balance);   // �޸Ĺٶ����Ʋ�
	private:
		string name_; 
};

#endif

