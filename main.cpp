#include <iostream>
#include "./HeaderFiles/CacheConfig.hpp"
#include <iomanip>

template <typename T>
void printCacheField(std::vector <T>);

Cache someCache(8, 16, 128, 4);
int main() {
	std::cout << "Hello World" << std::endl;
	
	
	
	//for(auto item : )

	std::pair <int, int>  accessPair{ 123, 0 };


	accessPair.second = someCache.getassociativity() > 1 ?  someCache.normalizeAddress(512) : accessPair.second;
	//std::cout << "second in pair is " << accessPair.second;
	//std::cout << std::endl << std::boolalpha << someCache.isHitAccess(accessPair.first, accessPair.second).first << std::endl;
	std::cout << std::endl << std::boolalpha << someCache.CacheRead(accessPair.first, accessPair.second).first;
	std::vector <int> TagField = someCache.getLRUField();
	printCacheField(TagField);
	std::vector <bool> boolField = someCache.getValidField();
	printCacheField(boolField);
}


template <typename T>
void printCacheField(std::vector <T> cacheField)  {
	for (int i{ 0 }; i < someCache.getCacheIndex(); i++) {
		for (int j{ i }; j <someCache.getFlattenedIndex(); j += someCache.getCacheIndex())
			std::cout << cacheField.at(j) << " ";
		std::cout << std::endl;
	}
}