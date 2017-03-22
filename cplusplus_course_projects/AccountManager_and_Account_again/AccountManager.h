#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "Account.h"
#include <iostream>
using std::string;

class AccountManager {
	public:
		AccountManager();
		~AccountManager();
		void open(const string& name, double balance);
		// ��������Ϊ�˻������˻����
		// if the name is not existed, please output "no such account"
		void close(const string& name);
		// ͨ���˻������ر��˻�
		int getAccountNumber();   // ��ȡ��ǰ�Ѿ�������˻�����
	private:
		Account *head_;
};

#endif
