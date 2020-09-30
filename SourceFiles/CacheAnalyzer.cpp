#include "../HeaderFiles/CacheAnalyzer.hpp"

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
	instructionCount{0},
	evictCount{0}, 
	memFechCount{0}

{
	Analyzer::setMissPenalty();
	Analyzer::setClockSpeed();
}


void Analyzer::setMissPenalty() {
	switch(Analyzer::getBlockSize())
	{
		case 32 :
			this->missPenalty += 2;
		break;
		case 64 :
			this->missPenalty += 6;
		break;
		default :
			this->missPenalty = missPenalty;
	}
}


void Analyzer::setClockSpeed(){
	switch(Analyzer::getassociativity()){
		case 2 : 
			this->clockSpeed *= 1.05;
		break;

		case 4 :
			this->clockSpeed *= 1.07;
		break;

		case 8 :
			this->clockSpeed *= 1.10;
		break;

		default:
			this->clockSpeed = this->clockSpeed;
	}

	switch(Analyzer::getCacheSize()){
		case 32 :
			this->clockSpeed *= 1.05;
		break;

		case 128 :
			this->clockSpeed *= 1.15;
		break;

		default:
			this->clockSpeed = this->clockSpeed;
	}
}


std::pair <int, int> Analyzer::tag_index_gen(const unsigned int & address){
	std::bitset <32> Adddr(address);
	
	Adddr = Adddr >> 2;
	//std::cout << Adddr.to_string(); 
	double blockOffsetBits_db = std::log2( (double) Analyzer::getNumberOfBlocks() );
	int blockOffsetBits {static_cast<int>(blockOffsetBits_db)};
	Adddr =  Adddr >> blockOffsetBits;
	

	double indexBits_db = std::log2((double) Analyzer::getCacheIndex());
	int indexBits {static_cast<int>(indexBits_db)};
	
	int TagBits{32 - indexBits};

	 std::bitset <32> Tag_BitSet;
	 std::bitset<32>  index_BitSet;
	 

	 Tag_BitSet = Adddr >> indexBits;
	 
	 index_BitSet =  Adddr << TagBits;
	 index_BitSet = index_BitSet >>  TagBits;
	
	return{Tag_BitSet.to_ulong(), index_BitSet.to_ulong()};
}


 void Analyzer::Cache_Access(const bool & isWrite, const std::string & hexAddress, const int & priorInstructionCount){
	 this->instructionCount =  this->instructionCount  + priorInstructionCount; // Increment by current instruction and prior Instruction
	 ++this->execution_time_Cycles; // Increment by default 1 Cycle 

	 std::stringstream hexinMem;
	 hexinMem << std::hex << hexAddress;
	 unsigned int hexAddress_int;
	 hexinMem >> hexAddress_int;

	 std::pair <int, int> accessParams = Analyzer::tag_index_gen(hexAddress_int);  // Generate Tag and Address based on address supplied
	//accessParams.second = accessParams.second & Analyzer::getCacheIndex();
	 if(isWrite) // Cache Access is a Store/Write
	 	{
			++this->store_Count; // Increment StoreCount
			std::pair <bool, bool> storeResult = Analyzer::CacheWrite(accessParams.first, accessParams.second); // Proceed to Write

			if(storeResult.first)// Write Hit
					{
						++this->store_hitCount;
						
					} // Increment Store Hit Count
			else{	// Write Miss
					++this->store_missCount; // Increment Store miss
					this->execution_time_Cycles += missPenalty; // Increment execution time by miss Penalty
					
				if(storeResult.second == true) //Block to replcae is dirty
					{
						//std::cout << "Heere1";
						this->evictCount+=1;//Increment evict Count
						this->execution_time_Cycles+=2; // Increment Execution time by extra time to evict block
					}
				// else 
				// 	++memFechCount;
				
			}
		} 
	else {//Load Access
		
			++this->load_Count; // Increment Loac Count
			std::pair <bool, bool> loadResult = Analyzer::CacheRead(accessParams.first, accessParams.second );// Proceed to Load

			if(loadResult.first) // Load/Read Hit
				++this->load_HitCount; // Increment lOAD hIT Count
			else { // Load/Read mISS
				++this->load_missCount; // iNCREMENT Load miss Count
				this->execution_time_Cycles += missPenalty; // Increment Execution time by miss Penalty

				if(loadResult.second == true) // bLOck to replace after Load Miss Is Dirty
					{
						//std::cout << "Heere2";
						this->evictCount+=1; // Increment Evict Count
						this->execution_time_Cycles+=2; // Increment Execution time by extra cycles to evict block
					}
				// else 
				// ++memFechCount;
			}
	}
 }

 void Analyzer::printResults(){
	 std::cout << std::left << std::setw(25) << "Load Count" 	 << std::setw(3) << this->load_Count << std::endl;
	 std::cout << std::left << std::setw(25) << "Load Hit Count"  << std::setw(3) << this->load_HitCount << std::endl;
	 std::cout << std::left << std::setw(25) << "Load Miss Count" << std::setw(3) << this->load_missCount << std::endl << std::endl;
	 std::cout << std::left << std::setw(25) << "Store Count is"	 << std::setw(3) << this->store_Count << std::endl;
	 std::cout << std::left << std::setw(25) << "Store Hit Count" << std::setw(3) << this->store_hitCount << std::endl;
	 std::cout << std::left << std::setw(25) << "Store Miss Count"<< std::setw(3) << this->store_missCount << std::endl << std::endl;
	 std::cout << std::left << std::setw(25) << "Memory Access"  << std::setw(3) << this->load_Count + this->store_Count << std::endl;
	 std::cout << std::left << std::setw(25) << "Instruction"   << std::setw(3) << this->instructionCount << std::endl;
	 std::cout << std::left << std::setw(25) << "Execution Time in Cycles " << std::setw(3)   << this->execution_time_Cycles << std::endl;
	 std::cout << std::left << std::setw(25) << "Evict Count " << std::setw(3)   << this->evictCount << std::endl;
	  std::cout << std::left << std::setw(25) << "Some Count is " << std::setw(3)   << Analyzer::getSomeCount() << std::endl;
	 
 }