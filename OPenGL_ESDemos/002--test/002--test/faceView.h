//
//  faceView.h
//  002--test
//
//  Created by liujilou on 2020/8/6.
//  Copyright © 2020 liujilou. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface faceView : UIView

@property (nonatomic, strong) UILabel * label;


-(void)setText:(NSString *)text backgroundColor:(UIColor *)color;

@end

NS_ASSUME_NONNULL_END
