#include <iostream>
#include <iomanip>
#include <time.h>

namespace CentAI_N {

/*Configuration should be dynamic, defines might not be used in future versions*/
#define POP_SIZE 20
#define NR_OF_GENES_PER_IND 10
#define RANDOM_MUTATION_MIN -0.1
#define RANDOM_MUTATION_MAX 0.1
#define SHOW_INDIVIDUAL_SCORE 0
#define SHOW_POPULATION_SCORE 0

	float randfloat(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}

	struct Generable {
		virtual void gen() = 0;
	};

	struct Showable {
		virtual void show() = 0;
	};

	struct Ind : Generable, Showable {
		float m_w[NR_OF_GENES_PER_IND];
		float m_score = 0.f;

		void gen() {
			for (int i = 0; i < NR_OF_GENES_PER_IND; i++) {
				m_w[i] = randfloat(-1.f, 1.f);
			}
		}

		void show() {
			std::cout << "[" << m_score << "] ";

			for (int i = 0; i < NR_OF_GENES_PER_IND; i++) {
				std::cout << m_w[i] << " ";
			}
			std::cout << std::endl;
		}

		Ind() = default;

		Ind& operator =(const Ind& a) {
			memcpy(m_w, a.m_w, sizeof(a.m_w));
			m_score = a.m_score;
			return *this;
		}
	};

	struct Pop : Generable, Showable {
		Ind m_inds[POP_SIZE];
		float m_avgScore = 0.f;

		void gen() {
			for (int i = 0; i < POP_SIZE; i++) {
				m_inds[i].gen();
			}
		}

		void calcAvgScore() {
			float totScore = 0.f;

			for (Ind &i : m_inds) {
				totScore += i.m_score;
			}

			m_avgScore = totScore / POP_SIZE;
		}

		void show() {
			calcAvgScore();

			std::cout << "Population avg score: " << m_avgScore << std::endl;

			for (int i = 0; i < POP_SIZE; i++) {
				std::cout << "" << i << ": ";
				m_inds[i].show();
			}
		}

		Pop() = default;

		Pop& operator =(const Pop& a)
		{
			memcpy(m_inds, a.m_inds, sizeof(a.m_inds));
			m_avgScore = a.m_avgScore;
			return *this;
		}
	};

	void crossover(Ind &newInd, Ind &a, Ind &b) {
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
	}

	/*Interface that shall be inherited by target application*/
	struct CAI_Interface {
		virtual float run(Ind &curind) = 0;
	};

	class CentAI {
	private:
		Pop m_pop;
		Pop m_bestPop;
		Ind m_bestInd;
		int32_t m_nrOfRuns;

		CAI_Interface * m_control;
	public:
		CentAI() : m_nrOfRuns(1){
			m_pop.gen();
		};
		~CentAI() {
			delete m_control;
		};

		void setNrOfRuns(int32_t nrOfRuns) {
			m_nrOfRuns = nrOfRuns;
		}

		void bind(CAI_Interface * control) {
			m_control = control;
		}

		void buildNewPop() {
			for (Ind &i : m_pop.m_inds) {
				m_pop.m_inds[0] = m_bestInd;

				int firstParentIndex = rand() % POP_SIZE;
				int secondParentIndex = rand() % POP_SIZE;

				while (secondParentIndex != firstParentIndex && POP_SIZE > 1) {
					secondParentIndex = rand() % POP_SIZE;
				}

				crossover(i, m_pop.m_inds[firstParentIndex], m_pop.m_inds[secondParentIndex]);
			}
		}

		void start() {
			for (int nrruns = 0; nrruns < m_nrOfRuns; nrruns++) {
				this->run();
			}

			show();
		}

		void run() {
			for (Ind &i : m_pop.m_inds) {
				i.m_score = m_control->run(i);
				if (i.m_score > m_bestInd.m_score)
					m_bestInd = i;
			}

			m_pop.calcAvgScore();

			if (m_pop.m_avgScore > m_bestPop.m_avgScore) {
				m_bestPop = m_pop;
			}

			if (SHOW_POPULATION_SCORE) {
				std::cout << "Population avg score: " << m_pop.m_avgScore << std::endl;
			}

			if (SHOW_INDIVIDUAL_SCORE) {
				for (Ind &i : m_pop.m_inds) {
					std::cout << "Individual score: " << i.m_score << std::endl;
				}
			}

			buildNewPop();
		}

		void show() {
			m_pop.show();
		}
	};
};