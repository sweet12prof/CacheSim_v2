#include "../HeaderFiles/CacheAnalyzer.h"

Analyzer::Analyzer(const int& associativityIn, const int& blockSizeIn, const int& cacheSizeIn, const int& wordSizeIn, const int& clockSpeedIn, const int& missPenaltyIn)
	:Cache(associativityIn, blockSizeIn, cacheSizeIn, wordSizeIn),
	clockSpeed{clockSpeedIn},
	missPenalty{missPenaltyIn},
	load_Count{0},
	load_HitCount{0},
	load_missCount{0},
	load_hitRate{0},
	load_missRate{0},
	store_Count{0},
	store_hitCount{0},
	store_missCount{0},
	store_missRate{0},
	execution_time_Cycles{0},
	instructionCount{0}

{
	Analyzer::setMissPenalty();
	Analyzer::setClockSpeed();
}


// void Analyzer::setMissPenalty() {
// 	switch(Analyzer::)
// }