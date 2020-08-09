//
//  LJLView1.h
//  003--test
//
//  Created by liujilou on 2020/8/8.
//  Copyright © 2020 liujilou. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, ProcessingType){
    ProcessingType_one = 1,
    ProcessingType_two = 2,
    ProcessingType_three = 3,
    ProcessingType_four = 4,
    ProcessingType_five = 5,
};


@interface LJLView1 : UIView

@property (nonatomic, assign) ProcessingType processingType;

@end

NS_ASSUME_NONNULL_END
