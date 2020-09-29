#include <iostream>
#include "./HeaderFiles/CacheConfig.hpp"
#include <iomanip>

template <typename T>
void printCacheField(std::vector <T>);

Cache someCache(8, 16, 16, 4);
int main() {
	std::cout << "Hello World" << std::endl;
	//for(auto item : )
	std::pair <int, int>  accessPair{ 123, 0 };


	accessPair.second = someCache.getassociativity() > 1 ? someCache.normalizeAddress(accessPair.second) : accessPair.second;
	//std::cout << "second in pair is " << accessPair.second;
	//std::cout << std::endl << std::boolalpha << someCache.isHitAccess(accessPair.first, accessPair.second).first << std::endl;
	std::cout << std::endl << std::boolalpha << someCache.CacheRead(accessPair.first, accessPair.second).first << std::endl;
	someCache.CacheRead(accessPair.first + 2, 0);
	std::cout << std::endl << std::boolalpha << someCache.CacheRead(accessPair.first, accessPair.second).first << std::endl;
	someCache.CacheRead(accessPair.first + 3, 0);
	someCache.CacheRead(accessPair.first + 2, 0);

	std::cout << std::endl << std::endl << std::endl << std::endl;
	
	someCache.CacheWrite(accessPair.first, 2);
	someCache.CacheWrite(accessPair.first + 3, 2);
	someCache.CacheRead(accessPair.first - 1, 2);
	someCache.CacheRead(accessPair.first, 2);
	someCache.CacheWrite(accessPair.first, 2);
	someCache.CacheWrite(accessPair.first + 3, 2);


	std::cout << std::endl << std::endl << std::endl << std::endl;
	std::vector <int> TagField = someCache.getTagField();
	printCacheField(TagField);
	std::cout << std::endl << std::endl << std::endl << std::endl;
	std::vector <int> LRUField = someCache.getLRUField();
	printCacheField(LRUField);
	std::cout << std::endl << std::endl << std::endl << std::endl;
	std::vector <bool> boolField = someCache.getValidField();
	printCacheField(boolField);
	std::cout << std::endl << std::endl << std::endl << std::endl;
	std::vector <bool> dirtyField = someCache.getIsDirtyField();
	printCacheField(dirtyField);
}


template <typename T>
void printCacheField(std::vector <T> cacheField) {
	for (int i{ 0 }; i < someCache.getCacheIndex(); i++) {
		for (int j{ i }; j < someCache.getFlattenedIndex(); j += someCache.getCacheIndex())
			std::cout << cacheField.at(j) << " ";
		std::cout << std::endl;
	}
}