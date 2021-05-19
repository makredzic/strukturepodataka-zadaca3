#pragma once
#include <ctime>
#include <iostream>
#include <queue>


class BankAccount {
	private:
		struct Transaction {
			double amount;
			time_t createdAt;

			Transaction(double newAmount = 0) : amount{newAmount}, createdAt{time(0)} {}
			void print() const {
				std::cout << "Amount: " << amount << std::endl;
				std::cout << "Created at: " << ctime(&createdAt) << std::endl;
			}
		};

// samo promijenim Queue<Transaction> ispod u neki drugi tip
// da promijenim kontejner u cijelom programu
		typedef std::queue<Transaction> TransactionQueue; 

		double balance_{0.0};
		TransactionQueue pending_transactions_; 

	public:
		BankAccount() = default;
		BankAccount(const BankAccount&) = delete;
		BankAccount(BankAccount&&) = delete;


		void addTransaction(double);
		void discardTransaction();

		void applyTransaction();
		void pendingTransaction() const;

		bool hasPending() const {return !pending_transactions_.empty();}

		double getBalance() const {return balance_;}
};

inline void BankAccount::addTransaction(double newAmount) {
	pending_transactions_.push(Transaction{newAmount});
}

inline void BankAccount::discardTransaction() {
	pending_transactions_.pop();
}

void BankAccount::pendingTransaction() const {
	std::cout << "\n---Latest pending transaction---\n";
	pending_transactions_.front().print();
}

void BankAccount::applyTransaction() {
	balance_ += pending_transactions_.front().amount;
	pending_transactions_.pop();
}

