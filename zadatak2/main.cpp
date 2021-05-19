#include <iostream>
#include "bankaccount.hpp"

static int print_menu() {
	std::cout << std::endl;
	std::cout << std::string(50, '*') << std::endl;

	std::cout << "Actions\n";
	std::cout << "\t1. New Transaction\n\t2. Apply Transaction\n\t3. Pending transaction\n\t4. Discard pending transaction\n\t5. Balance\n\t6. Exit\n";

	std::cout << "Your choice? ";
	int in;
	std::cin >> in;
	return in;
}

namespace transactions {
	BankAccount account;

	void add(double amount) {
		account.addTransaction(amount);
	}

	void apply() {
		if (account.hasPending()) {
			account.applyTransaction();	
			std::cout << "Transaction applied.\n";
		}
		else 
			std::cout << "There are no pending transactions to apply.\n";
	}

	void pending() {
		if (account.hasPending()) 
			account.pendingTransaction();
		else 
			std::cout << "There are no pending transactions to print.\n";
	}
	

	void discard() {
		if (account.hasPending()) {
			account.discardTransaction();
			std::cout << "Transaction discarded.\n";
		}
		else 
			std::cout << "There are no pending transactions to discard.\n";
	}

	void balance() {
		std::cout << "Your current balance is: " << account.getBalance() << std::endl;
	}

}

int main() {

	int choice = print_menu();

	while (choice != 6) {

		switch(choice) {
			case 1:
				double amount;
				std::cout << "Type the amount for the new transaction: ";
				std::cin >> amount;
				transactions::add(amount);
				break;
			case 2:
				transactions::apply();
				break;
			case 3:
				transactions::pending();
				break;
			case 4:
				transactions::discard();
				break;
			case 5:
				transactions::balance();
				break;
		}
		choice = print_menu();
	}
	
	std::cout << "\nShutting down.\n";
	return 0;
}
