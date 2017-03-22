#include "AccountManager.h"
#include "Account.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
// constructor && initialize
AccountManager::AccountManager() {
	head_ = NULL;
}
// destructor
AccountManager::~AccountManager() {
	Account* temp;
	while (head_ != NULL) {
		temp = head_;
		head_ = head_->getNext();
		delete temp;
	}
}
// ��������Ϊ�˻������˻����
void AccountManager::open(const string& name, double balance) {
	if (head_ == NULL) {
		head_ = new Account;
		head_->setName(name);
		head_->setBalance(balance);
	} else {
		Account* temp;
		temp = new Account;
		temp->setName(name);
		temp->setBalance(balance);
		temp->setNext(head_);
		head_ = temp;
	}
}
// ͨ���˻������ر��˻�
// if the name is not existed, please output "no such account"
void AccountManager::close(const string& name) {
	Account *temp, *p;
	temp = head_;
	if (temp->getName() == name) {
		head_ = head_->getNext();
		delete temp;
		return;
	}
	while (temp->getNext() != NULL) {
		if (temp->getNext()->getName() == name) {
			p = temp->getNext();
			temp->setNext(temp->getNext()->getNext());
			delete p;
			return;
		} else {
			temp = temp->getNext();
		}
	}
	cout << "no such account" << endl;
}
// ��ȡ��ǰ�Ѿ�������˻�����
int AccountManager::getAccountNumber() {
	Account* temp;
	int count = 0;
	temp = head_;
	while (temp != NULL) {
		temp = temp->getNext();
		count++;
	}
	return count;
}

