#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

string fileName = "dataFile"; 

struct SourceData{
    int zoneID;
    double temp[3];
    double power[3];
};

void WriteSourceDataToFile(vector<SourceData>& sources)
{
    ofstream outFile(fileName, ios::binary);
    if (!outFile)
    {
        return;
    }
    for (auto& source : sources)
    {
        outFile.write(reinterpret_cast<const char*>(&source), sizeof(source));
    }
    outFile.close();
}

void ReadSourceDataFromFile(vector<SourceData>& sources)
{
    ifstream inFile(fileName, ios::binary);
    if (!inFile)
    {
        return;
    }
    SourceData srcData;
    while(inFile.read(reinterpret_cast<char*>(&srcData), sizeof(srcData)))
    {
        sources.emplace_back(srcData);
    }
    inFile.close();
}

void ReadSourceDataByIndex(int index, SourceData& srcData)
{
    ifstream inFile(fileName, ios::binary);
    if (!inFile)
    {
        return;
    }
    inFile.seekg(index * sizeof(SourceData), std::ios::beg);
    inFile.read(reinterpret_cast<char*>(&srcData), sizeof(srcData));
    inFile.close();
}

double InterpolatePowerForTemperature(int temperature, SourceData& srcData)
{
    size_t ii = 0;
    for (; ii < 3; ++ii)
    {
        if (ii < 2 && (srcData.temp[ii] < temperature && srcData.temp[ii + 1] >  temperature))
        {
            break;
        }
    }
    double x1 = srcData.temp[ii];
    double x2 = srcData.temp[ii + 1];
    double y1 = srcData.power[ii];
    double y2 = srcData.power[ii + 1];

    return y1 + (y2 - y1) * (temperature - x1) / (x2 - x1);
}

int main() {

    SourceData srcData1{20, {20,25,30}, {0.2, 0.3, 0.5}};
    SourceData srcData2{30, {20,30,35}, {0.25, 0.4, 0.7}};
    SourceData srcData3{40, {20,45,50}, {0.22, 0.5, 0.8}};

    //Write source data to a file in binary format
    vector<SourceData> writeSources{srcData1, srcData2, srcData3};
    WriteSourceDataToFile(writeSources);

    //Read source data to from a file in binary format
    vector<SourceData> readSources;
    ReadSourceDataFromFile(readSources);
    for (auto& source : readSources)
    {
        cout    << "Zone ID : " << source.zoneID << endl
                << "Temperatures: " << source.temp[0] << " " << source.temp[1] << " " << source.temp[2] << endl
                << "Powers: " << source.power[0] << " " << source.power[1] << " " << source.power[2] << endl;
    }
    //Read only a particular source data from a file using an index
    SourceData readSrcData_2;
    ReadSourceDataByIndex(1, readSrcData_2);
    cout    << "Zone ID : " << readSrcData_2.zoneID << endl
                << "Temperatures: " << readSrcData_2.temp[0] << " " << readSrcData_2.temp[1] << " " << readSrcData_2.temp[2] << endl
                << "Powers: " << readSrcData_2.power[0] << " " << readSrcData_2.power[1] << " " << readSrcData_2.power[2] << endl;

    cout << "Interpolate power value: " << InterpolatePowerForTemperature(32, readSrcData_2) << endl;
};

