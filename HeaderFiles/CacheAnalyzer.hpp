#pragma once
#include "CacheConfig.hpp"
#include <bitset>
#include <cmath>
#include <sstream>
#include <iomanip>

class Analyzer : public Cache {
	private:
		//Cache Access Parameters
			

		//global Analysis Parameters
			int execution_time_Cycles;
			int clockSpeed;
			unsigned int instructionCount;
			int global_HitRate;
			int global_missRate;
			int missPenalty;
			int evictCount;
			int memFechCount;

			//int addressWidth;

		//Load Analysis Parameters
			int load_Count;
			int load_HitCount;
			int load_missCount;
			int load_hitRate;
			int load_missRate;

		//Store Analysis Paramters
			int store_Count;
			int store_hitCount;
			int store_missCount;
			int store_hitRate;
			int store_missRate;

			int Evict_Count;

	public:
		//Cache Access
			void Cache_Access(const bool&, const std::string &, const int&);
			std::pair <int, int> tag_index_gen(const unsigned int&);

		//Constructor adn Destructor  --asso, block, cSize, wordSize, clockSpeed, miss Penalty
			Analyzer(const int&, const int&, const int&, const int&, const int&, const int&);

		//Miss Penalty and ClockSpeed Tunin
			void setMissPenalty();
			void setClockSpeed();
		
		//
			void printResults();


};