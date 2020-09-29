#pragma once
#include "CacheConfig.hpp"
class Analyzer : public Cache {
	private:
		//Cache Access Parameters
			

		//global Analysis Parameters
			int execution_time_Cycles;
			int clockSpeed;
			int instructionCount;
			int global_HitRate;
			int global_missRate;
			int missPenalty;

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

	public:
		//Cache Access
			void Cache_Access(const bool&, const int&, const int&);
			std::pair <int, int> tag_index_gen(const int&);

		//Constructor adn Destructor  --asso, block, cSize, wordSize, clockSpeed, miss Penalty
			Analyzer(const int&, const int&, const int&, const int&, const int&, const int&);

		//Miss Penalty and ClockSpeed Tunin
			void setMissPenalty();
			void setClockSpeed();


};