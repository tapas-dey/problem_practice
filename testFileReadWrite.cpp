#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

string fileName = "testFile"; 

struct DummyData{
    int zoneID;
    double temp;
    double power;
};

int main() {
    //Write text file
    //ofstream oFile(fileName);
    //int age = 20;
    //oFile << "The person is " << age << " years old";
    //oFile << age;
    //oFile.close();
    //ifstream iFile(fileName);
    // while (iFile.good() && !iFile.eof())
    // {
    //     //int ageRead = 0;
    //     //iFile >> ageRead;
    //     //std::cout << "\nThe person is "<< ageRead << "years old"<< "\n";
    //     string textRead;
    //     iFile >> textRead;
    //     std::cout <<"\n" << textRead << "\n";
    // }
    // iFile.close();
    //Read write struct data
    // ofstream oFile(fileName);
    // DummyData dataToWrite{5, 2.3, 4.6};
    // oFile.write((const char*)(&dataToWrite), sizeof(dataToWrite));
    // oFile.close();
    // ifstream iFile(fileName);
    // DummyData dataToRead;
    // iFile.read((char*)(&dataToRead), sizeof(dataToRead));
    // iFile.close();
    // std::cout << dataToRead.zoneID << " " << dataToRead.temp << " "
    // << dataToRead.power << "\n";
    string path = "20 The person is 20 years old";
    stringstream ss(path);
    string token;
    ss >> token;
    cout <<"\n" << token << endl;
    // // //ss << path;
    // string token;
    //  std::cout << "\n";
    //  while(getline(ss, token))
    //  {
    //      std::cout << token << endl;
    //  }
    // string path = "The person is 20 years old";
    // stringstream ss(path);
    // // //ss << path;
    // string token;
    //  std::cout << "\n";
    //  while(getline(ss, token))
    //  {
    //      std::cout << token << endl;
    //  }     
    // ofstream outFile(fileName);
    // outFile << 2 << " " << 3 << " " << 4 << " "<< endl;
    // outFile.close();
    // ifstream inFile(fileName);
    // cout << endl;
    // while (inFile.good() && !inFile.eof()) 
    // {
    // int intRead = 0;
    // inFile >> intRead ;
    // std::cout << intRead << " ";
    // }      
    // inFile.close();

    //Get size of the file 
    // ifstream iFile(fileName);
    // if (iFile.is_open())
    // {
    //     iFile.seekg(0, iFile.end);
    //     int length = iFile.tellg();
    //     iFile.seekg(0, iFile.beg);
    //     char * buffer = new char [length];

    //     iFile.read(buffer, length);

    //     iFile.close();

    //     std::cout.write(buffer, length);

    //     delete[] buffer;

    // }

//   FILE * pFile;
//   long lSize;
//   char * buffer;
//   size_t result;
//   DummyData dataToWrite{5, 2.3, 4.6};
//   pFile = fopen ( fileName.c_str() , "wb" );
//   fwrite((char*)&dataToWrite, sizeof(dataToWrite), 1, pFile);
//   fclose(pFile);
//   pFile = fopen ( fileName.c_str() , "rb" );
//   if (pFile==NULL) {exit (1);}
//   DummyData dataToRead;
//   fread((char*)&dataToRead, sizeof(dataToRead), 1, pFile);
//   fclose(pFile);
//   std::cout << dataToRead.zoneID << " " << dataToRead.temp << " "
//     << dataToRead.power << "\n";




  return 0;
}