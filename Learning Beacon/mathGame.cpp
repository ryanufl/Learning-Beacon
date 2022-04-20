#include "mathGame.h"
/*Math::Math(int first, int second) {
	first = rand() % 10;
	this->second = second;
}*/
int Math::add() {
	int first = rand() % 10;
	int second = rand() % 10;
	cout << "Add " << first << " + " << second << endl;
	return first + second;
}
int Math::subtract() {
	int first = rand() % 20 + 10;
	int second = rand() % 10;
	cout << "Subtract " << first << " - " << second << endl;
	return first - second;
}
int Math::divide() {
	int first = rand() % 20 + 1;
	int i;
	vector<int> factor;
	for (i = 1; i <= num; i++) {
		if (num % i == 0)
			factor.push_back(i);
	}
	std::random_shuffle(factors.begin(), factors.end());

	int second = factor.begin();
	cout << "Divide " << first << " / " << second << endl;
	return first / second;
}
int Math::multiply() {
	int first = rand() % 10;
	int second = rand() % 10;
	cout << "Multiply " << first << " x " << second << endl;
	return first * second;
}
