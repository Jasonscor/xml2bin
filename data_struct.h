#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

typedef struct POSInfo
{
    int POS_Status;     // -1表示惯性状态, 54表示单点, 55表示浮点解RTK状态, 56表示固定解RTK状态
    double Speed_x;     // 东向速度 m/s
    double Speed_y;     // 北向速度 m/s
    double Speed_z;     // 天向速度 m/s
    double Speed;       // 速度

    double x;           // 纬度 latitude
    double y;           // 经度 longitude
    double z;           // 高程

    double x_proj;      // 投影坐标 m, UTM大地坐标系
    double y_proj;      // 投影坐标 m, UTM大地坐标系

    double roll;        // 横滚角
    double pitch;       // 俯仰角
    double yaw;         // 航向角

    double Time;        // 时间戳
}POSInfo;

typedef struct Point3D
{
    double x;       // 经度 longitude
    double y;       // 纬度 latitude
    double z;       // 高程 altitude

    Point3D()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }
}Point3D;

typedef struct Point3D_64
{
    int64_t x;
    int64_t y;
    int64_t z;

    Point3D_64()
    {
        x = 0;
        y = 0;
        z = 0;
    }
}Point3D_64;

typedef struct Point3D_16
{
    int16_t x;
    int16_t y;
    int16_t z;

    Point3D_16()
    {
        x = 0;
        y = 0;
        z = 0;
    }
}Point3D_16;

typedef struct Track_32
{
    int32_t time_stamp;     // unix时间戳
    int32_t longitude;      // 经度
    int32_t latitude;       // 纬度
    int32_t altitude;       // 高程
    int32_t yaw;            // 航向
    int32_t speed;          // 速度
}Track_16;

typedef struct Track_64
{
    int64_t time_stamp;
    int64_t longitude;
    int64_t latitude;
    int64_t altitude;
    int64_t yaw;
    int64_t speed;
}Track_64;

#endif // DATA_STRUCT_H
