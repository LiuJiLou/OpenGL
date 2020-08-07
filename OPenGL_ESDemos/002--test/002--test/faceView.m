//
//  faceView.m
//  002--test
//
//  Created by liujilou on 2020/8/6.
//  Copyright © 2020 liujilou. All rights reserved.
//

#import "faceView.h"

@implementation faceView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self createUI];
    }
    return self;
}

-(void)createUI
{
    self.label = [[UILabel alloc] initWithFrame:self.bounds];
    self.label.font = [UIFont systemFontOfSize:100];
    self.label.textAlignment = NSTextAlignmentCenter;
    [self addSubview:self.label];
}

-(void)setText:(NSString *)text backgroundColor:(UIColor *)color
{
    self.backgroundColor = color;
//    self.label.frame = self.bounds;
    self.label.text = text;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
