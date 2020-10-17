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

//Cache someCache(1, 16, 16, 4);
//Analyzer someCache(8, 32, 64, 4, 2, 40);
Analyzer someCache(1, 16, 16, 4, 2, 30);
int main(int argc, char * argv[]) {
 //int main() {
	std::string filepath = argv[1];
	FileHelper readFile(filepath);

	while(readFile.getCurrentPos() != -1){
		for(auto item : readFile.readChunk()){
			someCache.Cache_Access(item.first, item.second.first, item.second.second);
		}	
	}
		someCache.printResults();	
}


template <typename T>
void printCacheField(std::vector <T> cacheField) {
	for (int i{ 0 }; i < someCache.getCacheIndex(); i++) {
		for (int j{ i }; j < someCache.getFlattenedIndex(); j += someCache.getCacheIndex())
			std::cout << cacheField.at(j) << " ";
		std::cout << std::endl;
	}
}