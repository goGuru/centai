#include <iostream>
#include "centai.hpp"

using namespace CentAI_N;

class TestClass : CAI_Interface{
public:
	TestClass() {

	}

	float CAI_Interface::run(Ind &curind) {
		float score = 0.f;

		for (float gene : curind.m_w) {
			score += gene;
		}

		return score;
	}
};

int main() {
	srand(time(NULL));

	TestClass testObject;

	CentAI cai;
	cai.setNrOfRuns(100);

	cai.bind((CAI_Interface *)&testObject);
	cai.start();

	int a; std::cin >> a;
	return 0;
}