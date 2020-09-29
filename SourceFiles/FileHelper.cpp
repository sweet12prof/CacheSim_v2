#include "../HeaderFiles/FileHelper.hpp"



FileHelper::FileHelper(const std::string & path)
    :filepath{path},
    currentPosition{0},
    Count{0}
{
    inputFile.open(this->filepath, std::ios::in);
    if(!inputFile)
        {
            std::cerr << "Unable to open File, Check path" << std::endl;
            exit(EXIT_FAILURE);
        }
    else 
        inputFile.close();
}


std::vector <std::pair < bool, std::pair < std::string, int> >> FileHelper::readChunk(){
    std::vector <std::pair < bool, std::pair < std::string, int> >> result;
    int LineCount{0};

    inputFile.open(this->filepath, std::ios::in);
    inputFile.seekg(this->currentPosition);

    std::string currentLine;

    int isWrite_Int;
    bool isWrite;
    std::string hexAddress;
    int priorInstr;
    std::string someStr;


    while( std::getline(inputFile, currentLine) ){
        std::stringstream outputString;
        outputString << currentLine;

        outputString >> someStr >> isWrite_Int >> hexAddress >> priorInstr;
        isWrite = static_cast<bool>(isWrite_Int);

        result.push_back( {isWrite, {hexAddress, priorInstr} });

        LineCount++;
        this->Count++;

        if(LineCount == 3000)
            break;
        
    }
       
        this->currentPosition = inputFile.tellg();
        FileHelper::closeFile();

    return result;
}


 int FileHelper::getCurrentPos() const{
     return this->currentPosition;
 }

 void FileHelper::getlinesCounted() const{
    std::cout << std::left << std::setw(25) << "Lines Counted " << std::setw(3)   << this->Count << std::endl;
 } 

 void FileHelper::setCurrentPos(){
     this->currentPosition = -2;
 }

 void FileHelper::closeFile(){
     this->inputFile.close();
 }