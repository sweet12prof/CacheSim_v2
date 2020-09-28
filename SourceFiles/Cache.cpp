#include "CacheConfig.hpp"
#include <iostream>

//--------------Constructors


Cache::~Cache(){}

Cache::Cache(const int& associativityInput, const int& blockSizeInput, const int& CacheSizeInput, const int & wordSizeInput) 
	: blockSize{blockSizeInput}, 
	associativity{associativityInput}, 
	cacheSize{CacheSizeInput},
	wordSize{wordSizeInput}
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

	Cache::tagField.at(1024) = 123;
	Cache::validField.at(1024) = true;
	

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
void Cache::resizeField(std::vector<T> &field) {
	field.resize(this->FlattenedIndex);
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
			this->LRUField.at((i * cacheIndex) + j) = i;
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

//-----------------------------------//
//----Cache Operations---------------//
//-----------------------------------//

int Cache::normalizeAddress(const int& address) {
	return (address % this->cacheIndex);
}


std::pair <bool, std::pair <bool, int> > Cache::isHitAccess(const int& Tag, const int& searchAddress) {
	 
	std::cout << "search address is : " << searchAddress << std::endl;

	if (searchAddress >= Cache::FlattenedIndex)
		return { false, {false, -1} };

	else if ((this->tagField.at(searchAddress) == Tag) && (this->validField.at(searchAddress) == true))
		return { true, {this->isDirtyField.at(searchAddress), searchAddress} };

	else {
		if(Cache::associativity > 1)
			return Cache::isHitAccess(Tag, (searchAddress + this->cacheIndex));
		else 
			return { false, {false, -1} };
	}
		
		
}
