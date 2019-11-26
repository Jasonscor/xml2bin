#ifndef XML_DATA_H
#define XML_DATA_H

#include <list>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "tinyxml2.h"
#include "data_struct.h"
using namespace std;
using namespace tinyxml2;


#define LON_LAT_FACTOR  (100000000)
#define ALT_FACTOR      (10000)
#define round(x) (x - floor(x) >= 0.5 ? floor(x) + 1 : floor(x)) //四舍五入宏定义

class XMLData
{
public:
    XMLData();
    XMLData(const char* xmlPath);
    virtual ~XMLData();

    const char* getXMLPath();
    void setXMlPath(const char* xmlPath);
    int assertXMLPath(const char* xmlPath);
    int createXML(const char* xmlPath);
    int insertTrackXML(const char* xmlPath, vector<POSInfo>* track_list);
    int insertLaneXML(const char* xmlPath, vector<Point3D>* lane_list, const char* lane_type);

public:
    string genTS();
    void writeLane2Bin(const char* filename, list<Point3D>* lane_list);
    void writeTrack2Bin(const char* filename, list<POSInfo>* track_list);

protected:
    double Round(double value, int n);
    void write64ToBinFromStream(int64_t* buf, const char* filename, size_t size);
    void write32ToBinFromStream(int32_t* buf, const char* filename, size_t size);
    void write16ToBinFromStream(int16_t* buf, const char* filename, size_t size);
    void writeToBinFromStream(void* buf, const char* filename, size_t size);

private:
    XMLDocument     _doc;
    XMLDeclaration* _decl;
    XMLElement*     _root;
    const char*     _xmlPath;
};

#endif // XML_DATA_H
