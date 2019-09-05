//
//  SSYLocationChanged.h
//  Ssyer
//
//  Created by yidao on 2018/4/10.
//  Copyright © 2018年 YiDao. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>

@interface SSYLocationChanged : NSObject

//判断是否已经超出中国范围
+(BOOL)isLocationOutOfChina:(CLLocationCoordinate2D)location;
//将WGS-84(地球坐标)转为GCJ-02(火星坐标)
+(CLLocationCoordinate2D)transformFromWGSToGCJ:(CLLocationCoordinate2D)wgsLoc;

// WGS-84(地球坐标) 坐标转换成 BD-09（百度坐标）
+ (CLLocationCoordinate2D)WorldGS2BaiduGS:(CLLocationCoordinate2D)coordinate;

//经纬度（地理坐标WGS-84）转墨卡托（投影坐标）
+(CGPoint )lonLat2Mercator:(CGPoint)lonLat;

//墨卡托（投影坐标）转经纬度（地理坐标WGS-84)
+(CGPoint )Mercator2lonLat:(CGPoint)mercator;

@end
