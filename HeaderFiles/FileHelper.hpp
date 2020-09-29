#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iomanip>


class FileHelper{
    private :
        std::string filepath;
        int currentPosition;
        std::ifstream inputFile;
        int Count;
    
    public :
        int getCurrentPos() const;
        void setCurrentPos();
        void getlinesCounted() const; 
        FileHelper(const std::string &);
        std::vector <std::pair < bool, std::pair < std::string, int> >> readChunk();

        void closeFile();
};