#include <iostream>
#include <vector>
#include <time.h>

#define POP_SIZE 2
#define NR_OF_GENES_PER_IND 10
#define RANDOM_MUTATION_MIN -0.01
#define RANDOM_MUTATION_MAX 0.01

float randfloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

struct generable {
	virtual void gen() = 0;
};

struct showable {
	virtual void show() = 0;
};

struct ind : generable, showable {
	static ind bestInd;
	float m_w[NR_OF_GENES_PER_IND];
	float m_score = 0;

	void gen() {
		for (int i = 0; i < NR_OF_GENES_PER_IND; i++) {
			m_w[i] = randfloat(-1.f, 1.f);
		}
	}

	void show() {
		for (int i = 0; i < NR_OF_GENES_PER_IND; i++) {
			std::cout << m_w[i] << " ";
		}
		std::cout << std::endl;
	}

	ind() = default;

	ind& operator =(const ind& a){
		memcpy(m_w, a.m_w, sizeof(a.m_w));
		m_score = a.m_score;
		return *this;
	}
};

struct pop : generable, showable {
	static pop bestPop;

	ind m_inds[POP_SIZE];
	float m_avgScore;

	void gen() {
		for (int i = 0; i < POP_SIZE; i++) {
			m_inds[i].gen();
		}
	}

	void show() {
		std::cout << "Population" << std::endl;
		for (int i = 0; i < POP_SIZE; i++) {
			std::cout << " " << i << ": ";
			m_inds[i].show();
		}
	}

	pop() = default;

	pop& operator =(const pop& a)
	{
		memcpy(m_inds, a.m_inds, sizeof(a.m_inds));
		m_avgScore = a.m_avgScore;
		return *this;
	}
};

ind crossover(ind &a, ind &b) {
	ind newInd;
	float r;

	for (int i = 0; i < NR_OF_GENES_PER_IND; i++) {
		r = randfloat(RANDOM_MUTATION_MIN, RANDOM_MUTATION_MAX);
		if (rand() % 2) {
			newInd.m_w[i] = a.m_w[i] + r;
		}
		else {
			newInd.m_w[i] = b.m_w[i] + r;
		}
	}

	return newInd;
}

int main() {
	srand(time(NULL));

	pop curPop;

	curPop.gen();
	curPop.show();

	int a; std::cin >> a;
	return 0;
}