#include <iostream>
#include <stdexcept>

#include "Queue.hpp"

int main() {

	Queue<int> q{5};

	q.push(6);
	q.push(9);
	q.push(12);
	q.push(15);
	q.push(18);
	std::cout << q;

	try {
		q.push(100);
	} catch(const std::out_of_range& e) {
		std::cout << "100 nije dodano jer je maximum kapacitet dostignut.\n";
	}

	std::cout << "\nUklanjanje elemenata: \n";
	std::cout << "El 1: " << q.pop() << std::endl;
	std::cout << "El 2: " << q.pop() << std::endl;
	
	std::cout << "Trenutni elementi Reda: " << q;
	q.push(21);
	q.push(24);
	std::cout << "--Push 21 i 24--\n";
	std::cout << "Trenutni elementi Reda: " << q;

	Queue<int> q_cpy{q};
	std::cout << "\nCopy queue\n";
	std::cout << q_cpy;

	std::cout << "Uklanjanje 12, 15, 18:\n";
	std::cout << "Prvi: " << q_cpy.pop() << std::endl;
	std::cout << "Drugi: " << q_cpy.pop() << std::endl;
	std::cout << "Treci: " << q_cpy.pop() << std::endl;
	q_cpy.push(1);
	q_cpy.push(2);
	q_cpy.push(3);

	std::cout << "\nQueue nakon dodavanja 1, 2 i 3\n";
	std::cout << q_cpy;

	std::cout << "Top element: " << q_cpy.top() << std::endl;

	Queue<int> q2{50};
	for (int i = 1; i <= 20; i++) {
		q2.push(i*5);
	}

	std::cout << "\nQueue2\n";
	std::cout << q2;

	std::cout << "Queue = Queue2\n";
	q = q2;
	std::cout << q;

	std::cout << "Queue pop() & push(1)\n";
	q.pop();
	q.push(1);
	q.push(2);
	q.push(3);
	std::cout << q;

	q_cpy = Queue<int>{20};
	std::cout << q_cpy;




	return 0;
}
