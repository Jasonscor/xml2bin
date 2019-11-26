#include "xml_data.h"
#include <iostream>
using namespace std;

XMLData::XMLData():_decl(NULL),_root(NULL),_xmlPath(NULL)
{

}


XMLData::XMLData(const char* xmlPath):_decl(NULL),_root(NULL),_xmlPath(xmlPath)
{

}


XMLData::~XMLData()
{

}


const char* XMLData::getXMLPath()
{
    return _xmlPath;
}


void XMLData::setXMlPath(const char* xmlPath)
{
    this->_xmlPath = xmlPath;
}


/**
 * @brief assertXMLPath
 * @param const char* xmlPath
 * @author weixun
 * @date 2019.10.27
 * @return  1 fail
 *          0 succeed
 */
int XMLData::assertXMLPath(const char* xmlPath)
{
    return (NULL == xmlPath) ? 1 : 0;
}


/**
 * @brief createXML
 * @param const char* xmlPath
 * @author weixun
 * @date 2019.10.27
 * @return 返回说明
 *    -1  fail
 *     0  success
 */
int XMLData::createXML(const char* xmlPath)
{
    XMLElement* _rsd;

    if(assertXMLPath(xmlPath))
    {
        cout << "[XMLData::createXML]->[assertXMLPath] failed!" << endl;
        return -1;
    }

    _doc.LoadFile(xmlPath);

    // add xml declaration
    _decl = _doc.NewDeclaration();
    _doc.InsertFirstChild(_decl);

    // add root element
    _root = _doc.NewElement("Segmentation");
    _doc.InsertEndChild(_root);

    // add rsd name element
    _rsd = _doc.NewElement("name");
    _rsd->SetText("RSD");

    _root->InsertEndChild(_rsd);

    cout << "createXML Succeed!" << endl;

    return _doc.SaveFile(xmlPath);
}


/**
 * @brief insertTrackXML
 * @param  const char* xmlPath
 *         vector<POSInfo>* tracklist
 * @author weixun
 * @date 2019.10.27
 * @return 返回说明
 *    -1  fail
 *     0  success
 */
int XMLData::insertTrackXML(const char* xmlPath, vector<POSInfo>* tracklist)
{
    string track_buf;
    char tmp_str[512] = {0};
    XMLElement* Placemark = NULL;
    XMLElement* name = NULL;
    XMLElement* LineString = NULL;
    XMLElement* pose = NULL;
    XMLText* pose_data = NULL;

    if(assertXMLPath(xmlPath))
    {
        cout << "[XMLData::insertTrackXML]->[assertXMLPath] failed!" << endl;
        return -1;
    }

    _doc.LoadFile(xmlPath);

    if(_root)
    {
        Placemark = _doc.NewElement("Placemark");
        name = _doc.NewElement("name");
        LineString = _doc.NewElement("LineString");
        pose = _doc.NewElement("POSE_t_x_y_z_yaw_speed");

        if(tracklist)
        {
            for(int i = 0; i < (*tracklist).size(); i++)
            {
                sprintf(tmp_str, "%.8lf,%.8lf,%.8lf,%.8lf,%.8lf,%.8lf", (*tracklist).at(i).Time, (*tracklist).at(i).x, (*tracklist).at(i).y, (*tracklist).at(i).z, (*tracklist).at(i).yaw, (*tracklist).at(i).Speed);

                track_buf += tmp_str;
                track_buf += " ";
            }

            pose_data = _doc.NewText(track_buf.c_str());
            pose->InsertEndChild(pose_data);
        }

        name->SetText("Track");
        Placemark->InsertEndChild(name);
        LineString->InsertEndChild(pose);
        Placemark->InsertEndChild(LineString);

        _root->InsertEndChild(Placemark);
        cout << "insertTrackXML Succeed!" << endl;
    }

    return _doc.SaveFile(xmlPath);
}


/**
 * @brief insertLaneXML
 * @param  const char* xmlPath
 *         vector<Point3D>* lanelist
 *         const char* lane_type
 * @author weixun
 * @date 2019.10.27
 * @return 返回说明
 *    -1  fail
 *     0  success
 */
int XMLData::insertLaneXML(const char* xmlPath, vector<Point3D>* lanelist, const char* lane_type)
{
    string lane_buf;
    char tmp_str[128] = {0};
    XMLElement* Placemark = NULL;
    XMLElement* name = NULL;
    XMLElement* LineString = NULL;
    XMLElement* lane = NULL;
    XMLText* lane_data = NULL;

    if(assertXMLPath(xmlPath))
    {
        cout << "[XMLData::insertTrackXML]->[assertXMLPath] failed!" << endl;
        return -1;
    }

    _doc.LoadFile(xmlPath);

    if(_root)
    {
        Placemark = _doc.NewElement("Placemark");
        name = _doc.NewElement("name");
        LineString = _doc.NewElement("LineString");
        lane = _doc.NewElement("coordinates");

        if(lanelist)
        {
            for(int i = 0; i < (*lanelist).size(); i++)
            {
                sprintf(tmp_str, "%.8lf,%.8lf,%.4lf", (*lanelist).at(i).x, (*lanelist).at(i).y, (*lanelist).at(i).z);
                lane_buf += tmp_str;
                lane_buf += " ";
            }

            lane_data = _doc.NewText(lane_buf.c_str());
            lane->InsertEndChild(lane_data);
        }

        name->SetText(lane_type);
        Placemark->InsertEndChild(name);
        LineString->InsertEndChild(lane);
        Placemark->InsertEndChild(LineString);

        _root->InsertEndChild(Placemark);
        cout << "insertLaneXML Succeed!" << endl;
    }

    return _doc.SaveFile(xmlPath);
}


/**
 * @brief Round 
 * @param  double value
 *         int n
 * @author weixun
 * @date 2019.10.27
 * @return double
 * @remark 调用这个函数将value精确到小数点后n位
 */
double XMLData::Round(double value, int n)
{
    return round(value * pow(10, n)) / pow(10, n);
}


/**
 * @brief writeToBinFromStream
 * @param  void* buf
 *         const char* filename
 *         size_t size
 * @author weixun
 * @date 2019.10.27
 * @return void
 */
void XMLData::writeToBinFromStream(void* buf, const char* filename, size_t size)
{
    FILE *f = NULL;
    errno_t err;
    err = fopen_s(&f, filename, "abw+");
    if(!err)
    {
        fwrite(buf, 1, size, f);
        fclose(f);
    }
}


/**
 * @brief write64ToBinFromStream
 * @param  void* buf
 *         const char* filename
 *         size_t size
 * @author weixun
 * @date 2019.10.27
 * @return void
 */
void XMLData::write64ToBinFromStream(int64_t* buf, const char* filename, size_t size)
{
    writeToBinFromStream((int64_t*)buf, filename, size);
}


/**
 * @brief write32ToBinFromStream
 * @param  void* buf
 *         const char* filename
 *         size_t size
 * @author weixun
 * @date 2019.10.27
 * @return void
 */
void XMLData::write32ToBinFromStream(int32_t* buf, const char* filename, size_t size)
{
    writeToBinFromStream((int32_t*)buf, filename, size);
}


/**
 * @brief write16ToBinFromStream
 * @param  void* buf
 *         const char* filename
 *         size_t size
 * @author weixun
 * @date 2019.10.27
 * @return void
 */
void XMLData::write16ToBinFromStream(int16_t* buf, const char* filename, size_t size)
{
    writeToBinFromStream((int16_t*)buf, filename, size);
}


/**
 * @brief genTS (get unix timestamp)
 * @param  void
 * @author weixun
 * @date 2019.10.27
 * @return string (timestamp string)
 */
string XMLData::genTS()
{
    char ts[32] = {0};
    string filename = "lane_";
    time_t t = time(NULL);
    _i64toa(t, ts, 10);
    filename += ts;
    filename += ".dat";
    return filename;
}


/**
 * @brief writeLane2Bin
 * @param  const char* filename
 *         list<Point3D>* lanelist
 * @author weixun
 * @date 2019.10.27
 * @return void
 */
void XMLData::writeLane2Bin(const char* filename, list<Point3D>* lanelist)
{
    auto i = 0;
    Point3D_64 firstPt;
    Point3D_16 nextPt;
    size_t lanelist_size = (*lanelist).size();
    Point3D_16* remain_pts = new Point3D_16[lanelist_size - 1];
    auto lane_pt = (*lanelist).begin();
    firstPt.x = (int64_t)(((*lane_pt).x)*LON_LAT_FACTOR);
    firstPt.y = (int64_t)(((*lane_pt).y)*LON_LAT_FACTOR);
    firstPt.z = (int64_t)(((*lane_pt).z)*ALT_FACTOR);

    // if filename exists then remove
    // do not append at the end
    if(filename)
    {
        remove(filename);
    }
    // write first point to binary file
    write64ToBinFromStream((int64_t*)&firstPt, filename, sizeof(firstPt));

    lane_pt++;
    for(; lane_pt != (*lanelist).end(); lane_pt++)
    {
        nextPt.x = (int16_t)((int64_t)(((*lane_pt).x)*LON_LAT_FACTOR) - firstPt.x);
        nextPt.y = (int16_t)((int64_t)(((*lane_pt).y)*LON_LAT_FACTOR) - firstPt.y);
        nextPt.z = (int16_t)((int64_t)(((*lane_pt).z)*ALT_FACTOR) - firstPt.z);
        remain_pts[i] = nextPt;
        ++i;
    }

    // write remain points to binary file in append method
    write16ToBinFromStream((int16_t*)remain_pts, filename, sizeof(Point3D_16)*(lanelist_size - 1));

    if(NULL != remain_pts)
    {
        delete remain_pts;
        remain_pts = NULL;
    }
}


/**
 * @brief writeTrack2Bin
 * @param  const char* filename
 *         list<POSInfo>* tracklist
 * @author weixun
 * @date 2019.10.27
 * @return void
 */
void XMLData::writeTrack2Bin(const char* filename, list<POSInfo>* tracklist)
{
    auto i = 0;
    Track_64 firstTrack;
    Track_32 nextTrack;
    size_t tracklist_size = (*tracklist).size();
    auto cur_track = (*tracklist).begin();
    Track_32* remain_track = new Track_32[tracklist_size - 1];

    // if filename exists then remove
    if(filename)
    {
        remove(filename);
    }

    firstTrack.time_stamp = (int64_t)(((*cur_track).Time)*LON_LAT_FACTOR);
    firstTrack.longitude = (int64_t)(((*cur_track).x)*LON_LAT_FACTOR);
    firstTrack.latitude = (int64_t)(((*cur_track).y)*LON_LAT_FACTOR);
    firstTrack.altitude = (int64_t)(((*cur_track).z)*LON_LAT_FACTOR);
    firstTrack.yaw = (int64_t)(((*cur_track).yaw)*LON_LAT_FACTOR);
    firstTrack.speed = (int64_t)(((*cur_track).Speed)*LON_LAT_FACTOR);

    // write first track info to bin file
    write64ToBinFromStream((int64_t*)&firstTrack, filename, sizeof(firstTrack));

    cur_track++;

    for(; cur_track != (*tracklist).end(); cur_track++)
    {
        nextTrack.time_stamp = (int32_t)((int64_t)(((*cur_track).Time)*LON_LAT_FACTOR) - firstTrack.time_stamp);
        nextTrack.longitude = (int32_t)((int64_t)(((*cur_track).x)*LON_LAT_FACTOR) - firstTrack.longitude);
        nextTrack.latitude = (int32_t)((int64_t)(((*cur_track).y)*LON_LAT_FACTOR) - firstTrack.latitude);
        nextTrack.altitude = (int32_t)((int64_t)(((*cur_track).z)*LON_LAT_FACTOR) - firstTrack.altitude);
        nextTrack.yaw = (int32_t)((int64_t)(((*cur_track).yaw)*LON_LAT_FACTOR) - firstTrack.yaw);
        nextTrack.speed = (int32_t)((int64_t)(((*cur_track).Speed)*LON_LAT_FACTOR) - firstTrack.speed);
        remain_track[i] = nextTrack;
        ++i;
    }

    // write remain track info to binary file in append method
    write32ToBinFromStream((int32_t*)remain_track, filename, sizeof(Track_32)*(tracklist_size - 1));

    if(remain_track)
    {
        delete remain_track;
        remain_track = NULL;
    }
}


