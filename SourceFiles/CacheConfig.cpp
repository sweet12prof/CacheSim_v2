#include   "../HeaderFiles/CacheConfig.hpp"


//--------------Constructors


Cache::~Cache() {}

Cache::Cache(const int& associativityInput, const int& blockSizeInput, const int& CacheSizeInput, const int& wordSizeInput)
	: blockSize{ blockSizeInput },
	associativity{ associativityInput },
	cacheSize{ CacheSizeInput },
	wordSize{ wordSizeInput },
	someCount{0}
{
	Cache::setNumOfBlocks();
	Cache::setCacheIndex();
	Cache::setFlattenedIndex();

	Cache::resizeField(this->tagField);
	Cache::resizeField(this->validField);
	Cache::resizeField(this->isDirtyField);
	Cache::resizeField(this->LRUField);

	Cache::initialiseBoolFields(validField);
	Cache::initialiseBoolFields(isDirtyField);
	Cache::intialiseLRUField(this->LRUField);

	std::cout << "Cache Index is: " << this->cacheIndex << std::endl;
	std::cout << "Flattened index is : " << this->FlattenedIndex << std::endl;

	// Cache::tagField.at(1023) = 123;
	// Cache::validField.at(1023) = true;


}


//-------------------------------------------------------------------------

//--------------------------------------------------//
//----------Set Cache Properties--------------------//
//----------------------------------------------------
void Cache::setNumOfBlocks() {
	this->numOfBlocks = this->blockSize / this->wordSize;
}

void Cache::setCacheIndex() {
	this->cacheIndex = (this->cacheSize * 1024) / (this->associativity * this->blockSize);
}

void Cache::setFlattenedIndex() {
	this->FlattenedIndex = (this->cacheSize * 1024) / (this->blockSize);
}

template <typename T>
void Cache::resizeField(std::vector<T>& field) {
	field.resize(this->FlattenedIndex);
}

void Cache::resizeDataField(std::vector <int>& dataField) {
	dataField.resize(this->FlattenedIndex * this->numOfBlocks);
}

//--------------------------------------------------//
//----------Set Cache Fields--------------------//
//----------------------------------------------------
void Cache::initialiseBoolFields(std::vector <bool>& boolField) {
	std::fill(boolField.begin(), boolField.end(), 0);
}


void Cache::intialiseLRUField(std::vector <int>& LRUField) {
	for (int i = 0; i < Cache::associativity; i++) {
		for (int j = 0; j < Cache::cacheIndex; j++)
			this->LRUField.at((i * cacheIndex) + j) = (Cache::associativity) - (i + 1);
	}
}


//------------------------------------------------------------------//
//----------Print and Accessors For Cache Fields--------------------//
//------------------------------------------------------------------//
template <typename T>
void Cache::printCacheField(std::vector <T> cacheField) const {
	for (int i{ 0 }; i < Cache::cacheIndex; i++) {
		for (int j{ i }; j < Cache::FlattenedIndex; j += Cache::cacheIndex)
			std::cout << cacheField.at(j) << " ";
		std::cout << std::endl;
	}
}


std::vector<int> Cache::getTagField() const {
	return this->tagField;
}

std::vector<int> Cache::getLRUField() const {
	return this->LRUField;
}

std::vector<bool> Cache::getIsDirtyField() const {
	return this->isDirtyField;
}

std::vector<bool> Cache::getValidField() const {
	return this->validField;
}

int Cache::getFlattenedIndex() const {
	return this->FlattenedIndex;
}

int Cache::getCacheIndex()const {
	return this->cacheIndex;
}


int Cache::getassociativity() const {
	return this->associativity;
}


int Cache::getBlockSize() const {
	return this->blockSize;
}

int Cache::getCacheSize() const {
	return this->cacheSize;
}


int Cache::getNumberOfBlocks() const{
	return this->numOfBlocks;
}

//-----------------------------//
// Cache_Operations ----------//
//----------------------------//

int Cache::blockToEvict(const int & searchAddress){
	int loc = Cache::LRUField.at(searchAddress + ( (Cache::associativity - 1) * Cache::cacheIndex) );
	//int loc2 = LRUField.at( (loc * Cache::cacheIndex) + searchAddress);
	return loc;
}

int Cache::normalizeAddress(const int & indexInput){
	return (Cache::getassociativity() > 1) ? (indexInput % Cache::getCacheIndex()) : indexInput;
} 

std::pair < bool, std::pair <bool, int >> Cache::isHitAccess(const int & Tag, const int & searchAddress){
	
	if(searchAddress >= this->cacheIndex * this->associativity){
		int loc = Cache::blockToEvict(searchAddress % Cache::cacheIndex);
		bool val = Cache::isDirtyField.at( ((loc * Cache::cacheIndex)) + (searchAddress % Cache::cacheIndex));
		return {false, {val, -1 } };
	}
		
		

	else if( (Cache::tagField.at(searchAddress) == Tag) &&  (Cache::validField.at(searchAddress) == true))
		return {true, {Cache::isDirtyField.at(searchAddress), searchAddress}};
	

	else {
		if(Cache::associativity == 1)
			return {false, {Cache::isDirtyField.at(searchAddress), -1 }};
		else 
			return Cache::isHitAccess(Tag, (searchAddress + Cache::cacheIndex));
	}
}


std::pair <bool, bool> Cache::CacheRead(const int & Tag, const int & address){
	int searchAddress = Cache::normalizeAddress(address);
	std::pair <bool, std::pair <bool, int >> accessResult = Cache::isHitAccess(Tag, searchAddress);

	bool first {accessResult.first};
	bool second {accessResult.second.first};

	if(accessResult.first == true){
		searchAddress = Cache::normalizeAddress(address);
		Cache::LRUupdate(searchAddress, accessResult.second.second/Cache::cacheIndex);
	
	}
		
	else {
			searchAddress = Cache::normalizeAddress(address);
			int loc = Cache::LRUupdate(searchAddress, -1);
			int address_toEdit = (loc * Cache::cacheIndex) + searchAddress;
			Cache::isDirtyField.at(address_toEdit) = false;
			Cache::tagField.at(address_toEdit) = Tag;
			Cache::validField.at(address_toEdit) = true;
			
	}
	return {first, second};
}


std::pair <bool, bool> Cache::CacheWrite(const int & Tag, const int & address){
	int searchAddress = Cache::normalizeAddress(address);
	std::pair <bool, std::pair <bool, int> > accessResult = Cache::isHitAccess(Tag, searchAddress);
	bool first{accessResult.first};
	bool second{accessResult.second.first};

	if(accessResult.first == true)
		{
			searchAddress = Cache::normalizeAddress(address);
			if(Cache::isDirtyField.at(accessResult.second.second) == false){
				Cache::isDirtyField.at(accessResult.second.second) = true;			
			}	
				Cache::LRUupdate(searchAddress, accessResult.second.second/Cache::cacheIndex);

		}
	else {
			searchAddress = Cache::normalizeAddress(address);
			int loc = Cache::LRUupdate(searchAddress, -1);
			int address_toEdit = (loc * Cache::cacheIndex) + searchAddress;

			Cache::isDirtyField.at(address_toEdit) = true;
			Cache::validField.at(address_toEdit) = true;
			Cache::tagField.at(address_toEdit) = Tag;
	}
	return {first, second};
}	


int Cache::LRUupdate(const int & searchAddress, const int indexMultiple){
	std::vector <int> LRUIndex;
	std::vector <int> resultLRU;
	for(int i{searchAddress}; i < Cache::FlattenedIndex; i+=Cache::cacheIndex)
		LRUIndex.push_back(Cache::LRUField.at(i));
	
	if(indexMultiple == -1)
		{
			resultLRU.push_back(LRUIndex.back());
			// resultLRU.insert(LRUIndex.begin(), (LRUIndex.end() - 1), resultLRU.begin() + 1);
			for(int i{0}; i <LRUIndex.size() - 1; i++)
				resultLRU.push_back(LRUIndex.at(i));
		}	
	else {
			auto p = std::find(LRUIndex.begin(), LRUIndex.end(), indexMultiple);
			int pIndex = std::distance(LRUIndex.begin(), p);

			if(pIndex < 1)
				{
					//resultLRU.push_back(LRUIndex.back());
					//resultLRU.assign(LRUIndex.begin(), LRUIndex.end());
					 for(int i{0}; i <LRUIndex.size(); i++)
					 	resultLRU.push_back(LRUIndex.at(i));
				}
			
			else 
				{
					resultLRU.push_back(LRUIndex.at(pIndex));
					for(int i{0}; i < pIndex; i++)
						resultLRU.push_back(LRUIndex.at(i));
					
					for(int i {pIndex + 1}; i < LRUIndex.size(); i++)
						resultLRU.push_back(LRUIndex.at(i));
				}
		
	}
		int j{0};
			for(int i{searchAddress}; i < Cache::FlattenedIndex; i+=Cache::cacheIndex)
				{
					Cache::LRUField.at(i) =  resultLRU.at(j);
					j++;
				}	

	return resultLRU.at(0);
}











































































































































































































//-----------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------Cache Operations----------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------//

// 	//-----Normalises address to reular index
// 	int Cache::normalizeAddress(const int& address) {
// 		return (address % this->cacheIndex);
// 	}

// 	//-----Determine if an access is a hit or not, returns whether it is a hit, whether the field is dirty 
// 	//-----And also the flattened address if found
// 	std::pair <bool, std::pair <bool, int> > Cache::isHitAccess(const int& Tag, const int& searchAddress) {

// 		//std::cout << "search address is : " << searchAddress << std::endl;

// 		if (searchAddress >= Cache::FlattenedIndex)
// 			return { false, {this->isDirtyField.at(Cache::blockToEvict(searchAddress % Cache::cacheIndex)), -1} };

// 		else if ((this->tagField.at(searchAddress) == Tag) && (this->validField.at(searchAddress) == true))
// 			return { true, {this->isDirtyField.at(searchAddress), searchAddress} };

// 		else {
// 			if (Cache::associativity > 1)
// 				return Cache::isHitAccess(Tag, (searchAddress + this->cacheIndex));
// 			else
// 				return { false, {this->isDirtyField.at(searchAddress), -1} };
// 		}


// 	}

// 	//--------Initialises a Cache READ` operation---------------------------//
// 	//--------returns as a result whether or not the operation was a hit----//
// 	//-------also returns if the operation rquired a dirty evict------------//
// 	std::pair <bool, bool> Cache::CacheRead(const int& Tag, const int& address) {
// 		int searchAddress = Cache::getassociativity() > 1 ? Cache::normalizeAddress(address) : address;

// 		std::pair <bool, std::pair <bool, int> >  accessResult = Cache::isHitAccess(Tag, searchAddress);
// 		std::pair <bool, bool> returnPair{ accessResult.first, accessResult.second.first };
// 		bool first = accessResult.first;
// 		bool second = accessResult.second.first;

// 		if (accessResult.first == false) { // Read Miss
// 			if (accessResult.second.first == true) { //
// 				int loc = Cache::LRUupdate(searchAddress, -1);
// 				Cache::isDirtyField.at((searchAddress + ( loc *  Cache::cacheIndex)) ) = false;
// 				Cache::validField.at(searchAddress + ( loc *  Cache::cacheIndex)) = true;
// 				Cache::tagField.at(searchAddress + ( loc *  Cache::cacheIndex)) = Tag;
// 				this->someCount++;
// 			}
// 			else {
// 				int loc = Cache::LRUupdate(searchAddress, -1);
// 				Cache::isDirtyField.at(searchAddress + ( loc *  Cache::cacheIndex)) = false;
// 				Cache::validField.at(searchAddress + ( loc *  Cache::cacheIndex)) = true;
// 				Cache::tagField.at(searchAddress + ( loc * Cache::cacheIndex)) = Tag;
// 			}
// 		}

// 		else {
// 			int loc = Cache::LRUupdate(searchAddress, (accessResult.second.second / this->cacheIndex) );
// 			//Cache::mainMemoryFetch(Tag, searchAddress, loc);
// 		}

// 		return {first, second};

// 	}


// 	int Cache::blockToEvict(const int& address) {
// 		//return ((cacheIndex * LRUField.at((Cache::cacheIndex * associativity - 1))) + address);
// 		int loc = Cache::LRUField.at( (Cache::cacheIndex * (associativity - 1)) + address);
// 		return (Cache::cacheIndex * loc) + address;
// 	}

// 	//-------------------------------------------------------------------------------//
// 	//---------------Function to Evict dirty block and update LRU information--------//
// 	//-------------------------------------------------------------------------------//

// 	int Cache::LRUupdate(const int& searchAddress1, const int  IndexMultiple) {
// 		std::vector <int> lruBitsAtIndex;
// 		std::vector <int> resultLRU;
// 		int loc;
// 		int searchAddress = searchAddress1 % Cache::cacheIndex;
// 		for (int i{ searchAddress }; i < Cache::LRUField.size(); i += Cache::cacheIndex)
// 			lruBitsAtIndex.push_back(Cache::LRUField.at(i));
	
// 		if (IndexMultiple == -1)
// 		{
// 			resultLRU.push_back(lruBitsAtIndex.back());
// 			//resultLRU.assign(lruBitsAtIndex.begin(), lruBitsAtIndex.end() - 1);
// 			for (int i{ 1 }; i < lruBitsAtIndex.size(); i++)
// 				resultLRU.push_back( lruBitsAtIndex.at(i - 1) );
// 		}
// 		else {
// 			auto p = std::find(lruBitsAtIndex.begin(), lruBitsAtIndex.end(), IndexMultiple);
// 			loc = std::distance(lruBitsAtIndex.begin(), p);

// 			if(loc < 1)
// 				resultLRU.assign(lruBitsAtIndex.begin(), lruBitsAtIndex.end());
// 			else {
// 				resultLRU.push_back(lruBitsAtIndex.at(loc));
// 				for (int i{ 0 }; i < loc; i++)
// 					resultLRU.push_back(lruBitsAtIndex.at(i));
// 				for (int i{ loc + 1 }; i < lruBitsAtIndex.size(); i++)
// 					resultLRU.push_back(lruBitsAtIndex.at(i));
// 			}
		
// 		}
// 		int j{ 0 };
// 		for (int i{ searchAddress }; i < Cache::LRUField.size(); i += Cache::cacheIndex)
// 		{
// 			LRUField.at(i) = resultLRU.at(j);
// 			j++;
// 		}

// 		// for (auto item : resultLRU)
// 		// 	std::cout << item << " ";
// 		// std::cout << std::endl;


// 		return resultLRU.front();
// 	}

// 	//------------------------Function to Read Missed Block from Memory---------------------//
// 	//------------------------sets Valid and Tag fields in the process----------------------//
// 	//--------------------------------------------------------------------------------------//

// 	void Cache::mainMemoryFetch(const int& Tag, const int& searchAddress, const int& loc) {
// 		int address{ searchAddress + (Cache::cacheIndex * loc) };
// 		Cache::validField.at(address) = true;
// 		Cache::tagField.at(address) = Tag;
// 	}


// 	//----------------------Function to Write to Cache--------------------------------------//
// 	std::pair <bool, bool>  Cache::CacheWrite(const int& Tag, const int& address) {
// 		int searchAddress = Cache::getassociativity() > 1 ? Cache::normalizeAddress(address) : address;
// 		std::pair <bool, std::pair <bool, int> >  accessResult = Cache::isHitAccess(Tag, searchAddress);
// 		std::pair <bool, bool> returnPair{ accessResult.first, accessResult.second.first };

// 		bool first = accessResult.first;
// 		bool second = accessResult.second.first;


// 		if (accessResult.first == true) // WriteHit
// 		{
// 			Cache::validField.at(accessResult.second.second) = true;
// 			Cache::isDirtyField.at(accessResult.second.second) = true;
// 			Cache::LRUupdate(searchAddress, (accessResult.second.second / Cache::cacheIndex));
			
			
// 		}
// 		else {
// 			if (accessResult.second.first == true) {
// 				int loc = Cache::LRUupdate(searchAddress, -1);
// 				Cache::isDirtyField.at((searchAddress + ( loc *  Cache::cacheIndex)) ) = false;
// 				Cache::validField.at(searchAddress + ( loc *  Cache::cacheIndex)) = true;
// 				Cache::tagField.at(searchAddress + ( loc *  Cache::cacheIndex)) = Tag;
// 				someCount++;
// 			}
// 			else {
// 				int loc = Cache::LRUupdate(searchAddress, -1);
// 				Cache::isDirtyField.at((searchAddress + ( loc *  Cache::cacheIndex)) ) = false;
// 				Cache::validField.at(searchAddress + ( loc *  Cache::cacheIndex)) = true;
// 				Cache::tagField.at(searchAddress + ( loc *  Cache::cacheIndex)) = Tag;
// 			}
// 		}


// 		return {first, second};
// }


// int Cache::getSomeCount() const{
// 	return this->someCount;
// }