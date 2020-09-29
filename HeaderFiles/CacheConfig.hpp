#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

class Cache {
private:
	//Cache_Specifications
	int associativity;
	int cacheSize;
	int blockSize;
	int wordSize;
	//Fields
	std::vector<int> tagField;
	std::vector<bool> validField;
	std::vector<bool> isDirtyField;
	std::vector<int> LRUField;
	std::vector<int> dataField;
	// Properties
	int cacheIndex;
	int numOfBlocks;
	int FlattenedIndex;
public:
	Cache() = default;
	Cache(const int&, const int&, const int&, const int&);
	~Cache();

	// Set cacheProperties
	void setCacheIndex();
	void setNumOfBlocks();
	void setFlattenedIndex();
	template <typename T>
	void resizeField(std::vector <T>&);
	void resizeDataField(std::vector <int>&);

	//Initialise fields that need initial Contents
	void initialiseBoolFields(std::vector <bool>&);
	void intialiseLRUField(std::vector <int>&);

	//PrintCacheField
	template <typename T>
	void printCacheField(std::vector <T>) const;

	//Accessor For Fieldand properties
	std::vector<int> getTagField() const;
	std::vector<int> getLRUField() const;
	std::vector<bool> getValidField() const;
	std::vector<bool> getIsDirtyField() const;
	int getCacheIndex() const;
	int getFlattenedIndex() const;
	int getassociativity() const;

	//CacheOperations
	int  normalizeAddress(const int&);
	std::pair <bool, std::pair <bool, int> > isHitAccess(const int&, const int&);
	std::pair <bool, bool> CacheRead(const int&, const int&);
	std::pair <bool, bool>  CacheWrite(const int&, const int&);


	void CacheWriteback(const int&);
	void mainMemoryFetch(const int&, const int&, const int&);

	int  blockToEvict(const int&);
	


	int LRUupdate(const int&, const int);

};



