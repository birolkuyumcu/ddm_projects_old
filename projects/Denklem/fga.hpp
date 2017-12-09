// FGA - Fast Genetic Algorithm
// by Alessandro Presta
// This source code is protected by the GNU Lesser General Public License
// (see license.txt)

#ifndef FGA_HPP_
#define FGA_HPP_

#include <cstdlib>
#include <cstring>
#include <pthread.h>

using namespace std;

namespace fga {

	enum {
		CROSSOVER_1POINT,
		CROSSOVER_2POINT,
		CROSSOVER_UNIFORM,
		CROSSOVER_CUSTOM
	};

	enum {
		SELECT_WEIGHTED,
		SELECT_UNIFORM
	};

	enum {
		MUTATE_DEFAULT,
		MUTATE_CUSTOM
	};

	enum {
		RANDOM_DEFAULT,
		RANDOM_CUSTOM
	};

	template <class GeneType>
	class Population {
		private:
			int n;
			GeneType **chromosome;
			int length;
			float *score;
			float total_score;
			int best;
			GeneType *all_time_best;
			float all_time_best_score;
			int generations;
			float crossover_rate, mutation_rate;
			int crossover_type, select_type, mutate_type, random_type;
			float (*fitness)(GeneType *);
			GeneType (*mutate_gene)(GeneType);
			GeneType (*random_gene)();
			void (*crossover_custom)(GeneType *, GeneType *);
			void (*mutate_custom)(GeneType *);
			void (*random_custom)(GeneType *);
		public:
			Population(int nc, int clength, float (*f)(GeneType *), GeneType (*mgene)(GeneType), GeneType (*rgene)(), void (*ccustom)(GeneType *, GeneType *), void (*mcustom)(GeneType *), void (*rcustom)(GeneType *));
			~Population();
			void set_crossover_rate(float crate);
			void set_mutation_rate(float mrate);
			void set_crossover_type(int ctype);
			void set_select_type(int stype);
			GeneType *get_best();
			float get_best_score();
			GeneType *get_all_time_best();
			float get_all_time_best_score();
			int get_generations();
			bool run(float min_converge_value, int max_generations);
			void cycle();
			GeneType *select();
			GeneType *select_uniform();
			void crossover(GeneType *c1, GeneType *c2);
			void crossover_2point(GeneType *c1, GeneType *c2);
			void crossover_uniform(GeneType *c1, GeneType *c2);
			void mutate(GeneType *c);
	};

	template <class GeneType>
	class PopulationMT {
		private:
			int nthreads;
			int length;
			Population<GeneType> **tribe;
			pthread_t *thread;
			GeneType *best, *all_time_best;
			float all_time_best_score;
			int best_tribe;
		public:
			PopulationMT(int nt, int nc, int clength, float (*f)(GeneType *), GeneType (*mgene)(GeneType), GeneType (*rgene)(), void (*ccustom)(GeneType *, GeneType *), void (*mcustom)(GeneType *), void (*rcustom)(GeneType *));
			~PopulationMT();
			void set_crossover_rate(float crate);
			void set_mutation_rate(float mrate);
			void set_crossover_type(int ctype);
			void set_select_type(int stype);
			GeneType *get_best();
			float get_best_score();
			GeneType *get_all_time_best();
			float get_all_time_best_score();
			int get_generations();
			bool run(float min_converge_value, int max_generations);
			void cycle();
			static void *thread_wrapper(void *t);
	};

	template <class GeneType>
	Population<GeneType>::Population(int nc, int clength, float (*f)(GeneType *), GeneType (*mgene)(GeneType), GeneType (*rgene)(), void (*ccustom)(GeneType *, GeneType *), void (*mcustom)(GeneType *), void (*rcustom)(GeneType *))
	{
		n = nc;
		length = clength;
		fitness = f;
		mutate_gene = mgene;
		random_gene = rgene;
		crossover_custom = ccustom;
		mutate_custom = mcustom;
		random_custom = rcustom;
		crossover_rate = 0.7;
		mutation_rate = 0.001;
		crossover_type = CROSSOVER_1POINT;
		select_type = SELECT_WEIGHTED;
		mutate_type = MUTATE_DEFAULT;
		random_type = RANDOM_DEFAULT;
		if (crossover_custom != NULL)
			crossover_type = CROSSOVER_CUSTOM;
		if (mutate_custom != NULL)
			mutate_type = MUTATE_CUSTOM;
		if (random_custom != NULL)
			random_type = RANDOM_CUSTOM;
		chromosome = new GeneType*[n];
		score = new float[n];
		all_time_best = new GeneType[length];
		total_score = 0;
		best = 0;
		generations = 0;
		for (int i = 0; i < n; ++i) {
			chromosome[i] = new GeneType[length];
			if (random_type == RANDOM_DEFAULT) {
				for (int j = 0; j < length; ++j)
					chromosome[i][j] = random_gene();
			}
			else
				random_custom(chromosome[i]);
			score[i] = fitness(chromosome[i]);
			if (score[i] > score[best])
				best = i;
		}
		memcpy(all_time_best, chromosome[best], length * sizeof(GeneType));
		all_time_best_score = score[best];
	}

	template <class GeneType>
	Population<GeneType>::~Population()
	{
		for (int i = 0; i < length; ++i)
			delete[] chromosome[i];
		delete[] chromosome;
		delete[] score;
		delete[] all_time_best;
	}

	template <class GeneType>
	void Population<GeneType>::set_crossover_rate(float crate)
	{
		crossover_rate = crate;
	}

	template <class GeneType>
	void Population<GeneType>::set_mutation_rate(float mrate)
	{
		mutation_rate = mrate;
	}

	template <class GeneType>
	void Population<GeneType>::set_crossover_type(int ctype)
	{
		crossover_type = ctype;
	}

	template <class GeneType>
	void Population<GeneType>::set_select_type(int stype)
	{
		select_type = stype;
	}

	template <class GeneType>
	GeneType *Population<GeneType>::get_best()
	{
		return chromosome[best];
	}

	template <class GeneType>
	float Population<GeneType>::get_best_score()
	{
		return score[best];
	}

	template <class GeneType>
	GeneType *Population<GeneType>::get_all_time_best()
	{
		return all_time_best;
	}

	template <class GeneType>
	float Population<GeneType>::get_all_time_best_score()
	{
		return all_time_best_score;
	}

	template <class GeneType>
	int Population<GeneType>::get_generations()
	{
		return generations;
	}

	template <class GeneType>
	bool Population<GeneType>::run(float min_converge_value, int max_generations)
	{
		for (int i = 0; i < max_generations; ++i) {
			if (get_best_score() >= min_converge_value)
				return true;
			cycle();
		}
		return false;
	}

	template <class GeneType>
	void Population<GeneType>::cycle()
	{
		GeneType **new_chromosome = new GeneType*[n];
		for (int i = 0; i < n; ++i)
			new_chromosome[i] = new GeneType[length];
		float *new_score = new float[n];
		float new_total_score = 0;
		int new_best = 0;
		for (int i = 0; i < (n / 2) * 2; i += 2) {
			GeneType *parent0 = select();
			GeneType *parent1 = select();
			GeneType *child0 = new_chromosome[i];
			GeneType *child1 = new_chromosome[i + 1];
			memcpy(child0, parent0, length * sizeof(GeneType));
			memcpy(child1, parent1, length * sizeof(GeneType));
			crossover(child0, child1);
			mutate(child0);
			mutate(child1);
			new_score[i] = fitness(child0);
			new_score[i + 1] = fitness(child1);
			new_total_score += new_score[i] + new_score[i + 1];
			if (new_score[i] > new_score[new_best])
				new_best = i;
			if (new_score[i + 1] > new_score[new_best])
				new_best = i + 1;
		}
		for (int i = 0; i < n; ++i)
			delete[] chromosome[i];
		delete[] chromosome;
		delete[] score;
		chromosome = new_chromosome;
		score = new_score;
		total_score = new_total_score;
		best = new_best;
		++generations;
		if (all_time_best_score < score[best]) {
			memcpy(all_time_best, chromosome[best], length * sizeof(GeneType));
			all_time_best_score = score[best];
		}
	}

	template <class GeneType>
	inline GeneType *Population<GeneType>::select()
	{
		switch (select_type) {
			case SELECT_UNIFORM:
				return select_uniform();
			default:
				float choice = (float)rand() / RAND_MAX * total_score;
				float position = 0;
				for (int i = 0; i < n; ++i)
					if (position + score[i] >= choice)
						return chromosome[i];
					else
						position += score[i];
		}
		return NULL;
	}

	template <class GeneType>
	inline GeneType *Population<GeneType>::select_uniform()
	{
		return chromosome[rand() % n];
	}

	template <class GeneType>
	inline void Population<GeneType>::crossover(GeneType *c1, GeneType *c2)
	{
		if (((float)rand() / RAND_MAX) <= crossover_rate) {
			switch (crossover_type) {
				case CROSSOVER_2POINT:
					crossover_2point(c1, c2);
					break;
				case CROSSOVER_UNIFORM:
					crossover_uniform(c1, c2);
					break;
				case CROSSOVER_CUSTOM:
					crossover_custom(c1, c2);
					break;
				default:
					int cut = rand() % length;
					GeneType tmp;
					for (int i = cut; i < length; ++i) {
						tmp = c1[i];
						c1[i] = c2[i];
						c2[i] = tmp;
					}
			}
		}
	}

	template <class GeneType>
	inline void Population<GeneType>::crossover_2point(GeneType *c1, GeneType *c2)
	{
		int cut = rand() % length;
		GeneType tmp;
		for (int i = 0; i < cut; ++i) {
			tmp = c1[i];
			c1[i] = c2[i];
			c2[i] = tmp;
		}
		cut += rand() % (length - cut);
		for (int i = cut; i < length; ++i) {
			tmp = c1[i];
			c1[i] = c2[i];
			c2[i] = tmp;
		}
	}

	template <class GeneType>
	inline void Population<GeneType>::crossover_uniform(GeneType *c1, GeneType *c2)
	{
		GeneType tmp;
		for (int i = 0; i < length; ++i)
			if (rand() <= RAND_MAX / 2) {
				tmp = c1[i];
				c1[i] = c2[i];
				c2[i] = tmp;
			}
	}

	template <class GeneType>
	inline void Population<GeneType>::mutate(GeneType *c)
	{
		if (mutate_type == MUTATE_CUSTOM) {
			if ((float)rand() / RAND_MAX <= mutation_rate)
				mutate_custom(c);
			return;
		}
		for (int i = 0; i < length; ++i)
			if ((float)rand() / RAND_MAX <= mutation_rate)
				c[i] = mutate_gene(c[i]);
	}

	template <class GeneType>
	PopulationMT<GeneType>::PopulationMT(int nt, int nc, int clength, float (*f)(GeneType *), GeneType (*mgene)(GeneType), GeneType (*rgene)(), void (*ccustom)(GeneType *, GeneType *), void (*mcustom)(GeneType *), void (*rcustom)(GeneType *))
	{
		nthreads = nt;
		length = clength;
		tribe = new Population<GeneType>*[nthreads];
		thread = new pthread_t[nthreads];
		for (int i = 0; i < nthreads; ++i)
			tribe[i] = new Population<GeneType>(nc, clength, f, mgene, rgene, ccustom, mcustom, rcustom);
			best_tribe = 0;
			best = tribe[best_tribe]->get_best();
		for (int i = 0; i < nthreads; ++i)
			if (tribe[i]->get_best_score() > get_best_score()) {
				best_tribe = i;
				best = tribe[best_tribe]->get_best();
			}
		all_time_best = new GeneType[length];
		memcpy(all_time_best, tribe[best_tribe]->get_best(), length * sizeof(GeneType));
		all_time_best_score = tribe[best_tribe]->get_best_score();
	}

	template <class GeneType>
	PopulationMT<GeneType>::~PopulationMT()
	{
		for (int i = 0; i < nthreads; ++i)
			delete tribe[i];
		delete[] tribe;
		delete[] thread;
		delete[] all_time_best;
	}

	template <class GeneType>
	void PopulationMT<GeneType>::set_crossover_rate(float crate)
	{
		for (int i = 0; i < nthreads; ++i)
			tribe[i]->set_crossover_rate(crate);
	}

	template <class GeneType>
	void PopulationMT<GeneType>::set_mutation_rate(float mrate)
	{
		for (int i = 0; i < nthreads; ++i)
			tribe[i]->set_mutation_rate(mrate);
	}

	template <class GeneType>
	void PopulationMT<GeneType>::set_crossover_type(int ctype)
	{
		for (int i = 0; i < nthreads; ++i)
			tribe[i]->set_crossover_type(ctype);
	}

	template <class GeneType>
	void PopulationMT<GeneType>::set_select_type(int stype)
	{
		for (int i = 0; i < nthreads; ++i)
			tribe[i]->set_select_type(stype);
	}

	template <class GeneType>
	GeneType *PopulationMT<GeneType>::get_best()
	{
		return best;
	}

	template <class GeneType>
	float PopulationMT<GeneType>::get_best_score()
	{
		return tribe[best_tribe]->get_best_score();
	}

	template <class GeneType>
	GeneType *PopulationMT<GeneType>::get_all_time_best()
	{
		return all_time_best;
	}

	template <class GeneType>
	float PopulationMT<GeneType>::get_all_time_best_score()
	{
		return all_time_best_score;
	}

	template <class GeneType>
	int PopulationMT<GeneType>::get_generations()
	{
		return tribe[0]->get_generations();
	}

	template <class GeneType>
	bool PopulationMT<GeneType>::run(float min_converge_value, int max_generations)
	{
		for (int i = 0; i < max_generations; ++i) {
			if (get_best_score() >= min_converge_value)
				return true;
			cycle();
		}
		return false;
	}

	template <class GeneType>
	void PopulationMT<GeneType>::cycle()
	{
		for (int i = 0; i < nthreads; ++i)
			pthread_create(&(thread[i]), NULL, thread_wrapper, (void *)&(*(tribe[i])));
		for (int i = 0; i < nthreads; ++i)
			pthread_join(thread[i], NULL);
		best_tribe = 0;
		best = tribe[best_tribe]->get_best();
		for (int i = 0; i < nthreads; ++i)
			if (tribe[i]->get_best_score() > get_best_score()) {
				best_tribe = i;
				best = tribe[i]->get_best();
			}
		if (all_time_best_score < tribe[best_tribe]->get_best_score()) {
			memcpy(all_time_best, tribe[best_tribe]->get_best(), length * sizeof(GeneType));
			all_time_best_score = tribe[best_tribe]->get_best_score();
		}
	}

	template <class GeneType>
	void *PopulationMT<GeneType>::thread_wrapper(void *t)
	{
		((Population<GeneType> *)t)->cycle();
		return NULL;
	}

};

#endif // FGA_HPP_
