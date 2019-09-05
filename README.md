# SimulatorLocation
模拟定位，修改手机定位，钉钉打卡（iOS、安卓）




> 一、iOS（mac、数据线一根、苹果手机、xcode）：
> 
> > 连接真机运行代码，此举将修改手机定位，直接拔线可保留该定位，使用其他带有地图定位软件均显示此定位，可重启手机恢复定位（此定位保留时间不固定，使用其他定位软件可能导致此定位失效，如不常用其它定位软件，亲测可保留一周+）。
> 
> 二、安卓（任意系统电脑一台、模拟器）；


## 一、iOS（mac、数据线一根、iphone、xcode）：
github地址：[https://github.com/xiaopangzai/SimulatorLocation](https://github.com/xiaopangzai/SimulatorLocation)



**1、新建一项目，新建gpx文件，修改其中经纬度，经纬度可使用高德开放平台、百度拾取坐标：**



拾取坐标（***经验证百度比较精准，可自行对比参考***）：
百度：[http://api.map.baidu.com/lbsapi/getpoint/index.html](http://api.map.baidu.com/lbsapi/getpoint/index.html)
高德开放平台：[https://lbs.amap.com/console/show/picker](https://lbs.amap.com/console/show/picker)


![在这里插入图片描述](https://img-blog.csdnimg.cn/20190905142424493.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3Bhbmc3ODc1NTk2MTM=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190905142431881.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3Bhbmc3ODc1NTk2MTM=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190905143926372.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3Bhbmc3ODc1NTk2MTM=,size_16,color_FFFFFF,t_70)


**2、ViewController.m导入定位相关代码，以打印相关定位信息，验证是否准确：**

```
#import "ViewController.h"
#import "SSYLocationChanged.h"

@interface ViewController ()<CLLocationManagerDelegate>

@property (nonatomic, strong)CLLocationManager *locationManager;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    _locationManager =[[CLLocationManager alloc]init];
    _locationManager.delegate =self;
    //设置定位经准
    _locationManager.desiredAccuracy =kCLLocationAccuracyNearestTenMeters;
    [_locationManager requestWhenInUseAuthorization];//否则，ios10不弹定位框
    _locationManager.distanceFilter =10.0f;
    //开始定位
    [_locationManager startUpdatingLocation];
    
    // Do any additional setup after loading the view.
}

//定位代理经纬度回调
-(void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations{
    CLLocation *newLocation =locations[0];
    CLLocationCoordinate2D oCoordinate =newLocation.coordinate;
    [_locationManager stopUpdatingLocation];
    
    NSLog(@"经度------%f\n------纬度%f",oCoordinate.longitude,oCoordinate.latitude);
    //创建地理位置解码编码器对象
    CLGeocoder *geoCoder =[[CLGeocoder alloc]init];
    [geoCoder reverseGeocodeLocation:newLocation completionHandler:^(NSArray<CLPlacemark *> * _Nullable placemarks, NSError * _Nullable error) {
        for (CLPlacemark *place in placemarks) {
            NSLog(@"城市-----%@",place.locality);
        }
    }];
}


- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error{
    if ([error code] == kCLErrorDenied){
        //访问被拒绝
        NSLog(@"访问被拒绝");
    }
    if ([error code] == kCLErrorLocationUnknown) {
        //无法获取位置信息
        NSLog(@"无法获取位置信息");
    }
}


@end
```


**3、因上一步骤涉及定位，遂需设置info.plist相关权限：**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190905145436368.png)


**4、模拟器定位选择所创建的Location文件：**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190905150451384.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3Bhbmc3ODc1NTk2MTM=,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190905150517978.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3Bhbmc3ODc1NTk2MTM=,size_16,color_FFFFFF,t_70)


**5、连接真机运行即可，此举将修改手机定位，直接拔线可保留该定位，使用其他带有地图定位软件均显示此定位，可重启手机恢复定位（此定位保留时间不固定，使用其他定位软件可能导致此定位失效，如不常用其它定位软件，亲测可保留一周+）；**

