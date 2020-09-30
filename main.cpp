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
//Analyzer someCache(8, 32, 64, 4, 2, 42);
Analyzer someCache(1, 16, 16, 4, 2, 42);
int main(int argc, char * argv[]) {

	std::string filepath = argv[1];
	FileHelper readFile(filepath);

	
	// std::vector <bool> dirtyField = someCache.getIsDirtyField();
	// printCacheField(dirtyField);
	// std::cout << std::endl << std::endl << std::endl << std::endl;

	// someCache.Cache_Access(true, "00000010", 0);
	// std::cout << std::endl << std::endl << std::endl << std::endl;
	// std::vector <bool> dirtyField1 = someCache.getIsDirtyField();
	// printCacheField(dirtyField1);
	
	// someCache.Cache_Access(true, "00000010", 0);
	// std::cout << std::endl << std::endl << std::endl << std::endl;
	// std::vector <bool> dirtyField2 = someCache.getIsDirtyField();
	// printCacheField(dirtyField2);
	
	// // std::cout << std::endl << std::endl << std::endl << std::endl;
	// // std::vector <int> LRUField1 = someCache.getLRUField();
	// // printCacheField(LRUField1);

	// someCache.Cache_Access(false,"00010010", 0);
	// std::cout << std::endl << std::endl << std::endl << std::endl;
	// std::vector <bool> dirtyField3 = someCache.getIsDirtyField();
	// printCacheField(dirtyField3);

	// std::cout << std::endl << std::endl << std::endl << std::endl;
	// std::vector <int> LRUField = someCache.getLRUField();
	// printCacheField(LRUField);
	
	// someCache.Cache_Access(true, "00010010", 0);
	// // someCache.Cache_Access(true, "00010010", 0);
	// std::cout << std::endl << std::endl << std::endl << std::endl;
	// std::vector <bool> dirtyField4 = someCache.getIsDirtyField();
	// printCacheField(dirtyField4);
	
	// someCache.Cache_Access(false,"10000010", 0);
	// std::cout << std::endl << std::endl << std::endl << std::endl;
	// std::vector <bool> dirtyField5 = someCache.getIsDirtyField();
	// printCacheField(dirtyField5);
	
	// someCache.Cache_Access(true, "10000010", 0);
	// std::cout << std::endl << std::endl << std::endl << std::endl;
	// std::vector <bool> dirtyField6 = someCache.getIsDirtyField();
	// printCacheField(dirtyField6);

	// someCache.Cache_Access(true, "10000010", 0);
	// someCache.Cache_Access(true, "10000010", 0);
	// someCache.Cache_Access(true, "01000010", 0);
	// someCache.Cache_Access(true, "01000010", 0);
	// someCache.Cache_Access(true, "01000010", 0);
	// someCache.Cache_Access(true, "01000010", 0);
	// someCache.Cache_Access(true, "01100010", 0);
	// someCache.Cache_Access(true, "01100010", 0);
	// someCache.Cache_Access(true, "01100111", 0);
	// someCache.Cache_Access(true, "11100010", 0);
	// someCache.Cache_Access(true, "10000010", 0);
	// someCache.Cache_Access(true, "10000010", 0);
	// someCache.Cache_Access(true, "10000010", 0);
	// someCache.Cache_Access(true, "10000010", 0);
	// someCache.Cache_Access(true, "10000010", 0);
	// someCache.Cache_Access(true, "10000010", 0);
	// someCache.Cache_Access(true, "10000010", 0);


	//someCache.printResults();

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
	// std::vector <int> TagField = someCache.getTagField();
	// printCacheField(TagField);
	// std::cout << std::endl << std::endl << std::endl << std::endl;
	// std::vector <int> LRUField = someCache.getLRUField();
	// printCacheField(LRUField);
	// std::cout << std::endl << std::endl << std::endl << std::endl;
	// std::vector <bool> boolField = someCache.getValidField();
	// printCacheField(boolField);

	// std::cout << std::endl << std::endl << std::endl << std::endl;
	// std::vector <bool> dirtyField = someCache.getIsDirtyField();
	// printCacheField(dirtyField);

	//for(auto item : )
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