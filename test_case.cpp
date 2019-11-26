#include "test_case.h"
#include "xml_data.h"

TestCase::TestCase(){}

TestCase::~TestCase(){}

void TestCase::test_lane_01()
{
    XMLData xml_data;
    Point3D pt_arr[50];
    Point3D pt_arr_2[178];
    list<Point3D> qlist_pt;
    list<Point3D> qlist_pt_2;
    double delta_x = 0.00001;
    double delta_y = 0.00001;
    double delta_z = 0.001;
    for(int j = 0; j < 50; j++)
    {
        pt_arr[j].x = 114.40360895 - delta_x*j;
        pt_arr[j].y = 30.47558123 - delta_y*j;
        pt_arr[j].z = 31.5880 - delta_z*j;
        qlist_pt.push_back(pt_arr[j]);
    }

    for(int k = 0; k < 178; k++)
    {
        pt_arr_2[k].x = 114.40360895 + delta_x*k;
        pt_arr_2[k].y = 30.47558123 + delta_y*k;
        pt_arr_2[k].z = 31.5880 + delta_z*k;
        qlist_pt_2.push_back(pt_arr_2[k]);
    }

    xml_data.writeLane2Bin(xml_data.genTS().c_str(), &qlist_pt);
    //xml_data.writeLane2Bin("2222.dat", &qlist_pt_2);
}


void TestCase::test_lane_02(int n)
{
    XMLData xml_data;
    Point3D pt_arr[50];
    Point3D pt_arr_2[178];
    list<Point3D> qlist_pt;
    list<Point3D> qlist_pt_2;
    double delta_x = 0.00001;
    double delta_y = 0.00001;
    double delta_z = 0.001;
    for(int j = 0; j < 50; j++)
    {
        pt_arr[j].x = 114.40360895 - delta_x*j;
        pt_arr[j].y = 30.47558123 - delta_y*j;
        pt_arr[j].z = 31.5880 - delta_z*j;
        qlist_pt.push_back(pt_arr[j]);
    }

    for(int k = 0; k < 178; k++)
    {
        pt_arr_2[k].x = 114.40360895 + delta_x*k;
        pt_arr_2[k].y = 30.47558123 + delta_y*k;
        pt_arr_2[k].z = 31.5880 + delta_z*k;
        qlist_pt_2.push_back(pt_arr_2[k]);
    }

    if(n == 1)
    {
        xml_data.writeLane2Bin(xml_data.genTS().c_str(), &qlist_pt);
    }
    else if(n == 2)
    {
        xml_data.writeLane2Bin("2222.dat", &qlist_pt_2);
    }
    else
    {
        ;
    }
}
