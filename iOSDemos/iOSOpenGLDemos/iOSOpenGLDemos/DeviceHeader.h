//
//  DeviceHeader.h
//  iChat
//
//  Created by Gome on 2018/9/26.
//  Copyright © 2018年 mx. All rights reserved.
//

#ifndef DeviceHeader_h
#define DeviceHeader_h

static BOOL isEmpty(id thing) {
    return thing == nil
    || [thing isKindOfClass:[NSNull class]]
    || ([thing respondsToSelector:@selector(length)]
        && [(NSData *)thing length] == 0)
    || ([thing respondsToSelector:@selector(count)]
        && [(NSArray *)thing count] == 0);
}

//判断是否是ipad
#define isPad ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad)
//判断iPhone4系列
#define kiPhone4 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 960), [[UIScreen mainScreen] currentMode].size) && !isPad : NO)
//判断iPhone5系列
#define kiPhone5 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 1136), [[UIScreen mainScreen] currentMode].size) && !isPad : NO)
//判断iPhone6系列
#define kiPhone6 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(750, 1334), [[UIScreen mainScreen] currentMode].size) && !isPad : NO)
//判断iphone6+系列
#define kiPhone6Plus ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1242, 2208), [[UIScreen mainScreen] currentMode].size) && !isPad : NO)
//判断iPhoneX
#define IS_IPHONE_X ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1125, 2436), [[UIScreen mainScreen] currentMode].size) && !isPad : NO)
//判断iPHoneXr
#define IS_IPHONE_Xr ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(828, 1792), [[UIScreen mainScreen] currentMode].size) && !isPad : NO)

//判断iPhoneXs
#define IS_IPHONE_Xs ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1125, 2436), [[UIScreen mainScreen] currentMode].size) && !isPad : NO)
//判断iPhoneXs Max
#define IS_IPHONE_Xs_Max ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1242, 2688), [[UIScreen mainScreen] currentMode].size) && !isPad : NO)

//iPhoneX系列  iPhoneXS Max，iPhoneXS，iPhoneXR，iPhoneX 的宽高比近似  用于解决Xr判断不出来的问题。
//XSM SCREEN_HEIGHTL = 896.000000,SCREEN_WIDTHL = 414.000000 2.1642512077
//XS  SCREEN_HEIGHTL = 812.000000,SCREEN_WIDTHL = 375.000000  2.1653333333
//XR  SCREEN_HEIGHTL = 896.000000,SCREEN_WIDTHL = 414.000000  2.1642512077
#define KIsiPhoneX ((int)(([UIScreen mainScreen].bounds.size.height/[UIScreen mainScreen].bounds.size.width)*100) == 216)?YES:NO

#define IS_iPhoneX_SERIES ((IS_IPHONE_X==YES || IS_IPHONE_Xr ==YES || IS_IPHONE_Xs== YES || IS_IPHONE_Xs_Max== YES || KIsiPhoneX == YES) ? YES : NO)


//iPhoneX系列
#define Height_StatusBar ((IS_IPHONE_X==YES || IS_IPHONE_Xr ==YES || IS_IPHONE_Xs== YES || IS_IPHONE_Xs_Max== YES || KIsiPhoneX == YES) ? 44.0 : 20.0)
#define Height_NavStatusBar ((IS_IPHONE_X==YES || IS_IPHONE_Xr ==YES || IS_IPHONE_Xs== YES || IS_IPHONE_Xs_Max== YES || KIsiPhoneX == YES) ? 88.0 : 64.0)
#define Height_NavBar 44.0
#define Height_TabBar ((IS_IPHONE_X==YES || IS_IPHONE_Xr ==YES || IS_IPHONE_Xs== YES || IS_IPHONE_Xs_Max== YES || KIsiPhoneX == YES) ? 83.0 : 49.0)

#define UIScreenScale [UIScreen mainScreen].scale

// 屏幕尺寸
#define SCREEN_Width [UIScreen mainScreen].bounds.size.width
#define SCREEN_Height [UIScreen mainScreen].bounds.size.height

#define WSelf(weakSelf)  __weak __typeof(&*self)weakSelf = self;

//数组是否为空
#define IsArrEmpty(_ref)    (((_ref) == nil) || ([(_ref) isEqual:[NSNull null]]) ||([(_ref) count] == 0))
//字典是否为空
#define IsDicEmpty(_ref)    (((_ref) == nil) || ([(_ref) isEqual:[NSNull null]]) ||([(_ref) count] == 0))


#define GMK_Str_Class(str) [str isKindOfClass:[NSString class]]
#define GMK_Str_Is_Valid(str) ((str) && (GMK_Str_Class(str)) && ([str length] > 0))

#define MXNavBarH (([UIScreen mainScreen].bounds.size.height == 812.0 ? 44 : 20) + 44)
#endif /* DeviceHeader_h */
