#include <iostream>
//#include "./HeaderFiles/CacheConfig.hpp"
#include "./HeaderFiles/CacheAnalyzer.hpp"
#include "./HeaderFiles/FileHelper.hpp"
#include <iomanip>
#include <sstream>
#include <bitset>
#include <iterator>

template <typename T>
void printCacheField(std::vector <T>);

//Cache someCache(8, 16, 16, 4);
Analyzer someCache(8, 32, 64, 4, 2, 42);
int main(int argc,  char * argv[]) {
	// std::cout << "Hello World" << std::endl;
	// //for(auto item : )
	// std::pair <int, int>  accessPair{ 123, 0 };


	// accessPair.second = someCache.getassociativity() > 1 ? someCache.normalizeAddress(accessPair.second) : accessPair.second;
	// //std::cout << "second in pair is " << accessPair.second;
	// //std::cout << std::endl << std::boolalpha << someCache.isHitAccess(accessPair.first, accessPair.second).first << std::endl;
	// std::cout << std::endl << std::boolalpha << someCache.CacheRead(accessPair.first, accessPair.second).first << std::endl;
	// someCache.CacheRead(accessPair.first + 2, 0);
	// std::cout << std::endl << std::boolalpha << someCache.CacheRead(accessPair.first, accessPair.second).first << std::endl;
	// someCache.CacheRead(accessPair.first + 3, 0);
	// someCache.CacheRead(accessPair.first + 2, 0);

	// std::cout << std::endl << std::endl << std::endl << std::endl;
	
	// someCache.CacheWrite(accessPair.first, 2);
	// someCache.CacheWrite(accessPair.first + 3, 2);
	// someCache.CacheRead(accessPair.first - 1, 2);
	// someCache.CacheRead(accessPair.first, 2);
	// someCache.CacheWrite(accessPair.first, 2);
	// someCache.CacheWrite(accessPair.first + 3, 2);


	

	// std::string hexNumber = "ffffffff";
	// std::stringstream input;
	// input << std::hex << hexNumber;
	// unsigned int numInDecimal;
	// input >> numInDecimal;

	// std::cout << numInDecimal;
	// auto p = someCache.tag_index_gen(numInDecimal);
	// std::cout << "Tag is " << p.first << std::endl << "Index is " << p.second;

	// std::pair < bool, std::pair < std::string, int> > accessParam {false, {"3019b6c8", 2}};

	// someCache.Cache_Access(accessParam.first, accessParam.second.first, accessParam.second.second);

	// someCache.printResults();
	// std::cout << std::endl << std::endl << std::endl << std::endl;

	// std::cout << std::endl << std::endl << std::endl << std::endl;
	// std::vector <int> TagField = someCache.getTagField();
	// printCacheField(TagField);
	// std::cout << std::endl << std::endl << std::endl << std::endl;
	// std::vector <int> LRUField = someCache.getLRUField();
	// printCacheField(LRUField);
	// std::cout << std::endl << std::endl << std::endl << std::endl;
	// std::vector <bool> boolField = someCache.getValidField();
	// printCacheField(boolField);


	std::string filepath = argv[1];
	FileHelper readFile(filepath);

	while(readFile.getCurrentPos() >= -1){
		for(auto item : readFile.readChunk()){
			someCache.Cache_Access(item.first, item.second.first, item.second.second);
			if(readFile.getCurrentPos() == -1)
				readFile.setCurrentPos();
		}
		
	}

		someCache.printResults();
		readFile.getlinesCounted();

	// std::cout << std::endl << std::endl << std::endl << std::endl;
	// std::vector <bool> dirtyField = someCache.getIsDirtyField();
	// printCacheField(dirtyField);
}

	
	
	
	
	
	
	// std::string hexNum {"110000000011100010000011011000"};
	// std::bitset <32> hexNum_BitSet(hexNum);
	// int someNum = hexNum_BitSet.to_ulong();

	//  auto p = someCache.tag_index_gen(someNum);
	
	// std::cout << "Tag is " << p.first << std::endl << "Index is " << p.second;

	// //std::cout << "Hex num in decimal is: " << ;



template <typename T>
void printCacheField(std::vector <T> cacheField) {
	for (int i{ 0 }; i < someCache.getCacheIndex(); i++) {
		for (int j{ i }; j < someCache.getFlattenedIndex(); j += someCache.getCacheIndex())
			std::cout << cacheField.at(j) << " ";
		std::cout << std::endl;
	}
}