//
//  OffscreenRenderingVC.m
//  iOSOpenGLDemos
//
//  Created by liujilou on 2020/7/9.
//  Copyright © 2020 liujilou. All rights reserved.
//

#import "OffscreenRenderingVC.h"
#import "DeviceHeader.h"

@interface OffscreenRenderingVC ()

@end

@implementation OffscreenRenderingVC

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    CGFloat w = SCREEN_Width/4.0f;
    CGFloat h = (SCREEN_Height-Height_NavStatusBar)/6.0f;
    CGFloat spacingH = h/2.f;
    CGFloat spacingW = w/2.f;
    CGFloat top = Height_NavStatusBar+spacingH;
    CGFloat left1 = spacingW;
    CGFloat left2 = spacingW+SCREEN_Width/2.f;
    
    UIImageView * imageView1 = [[UIImageView alloc] initWithFrame:CGRectMake(left1, top, w, h)];
    imageView1.image = [UIImage imageNamed:@"file_rar"];
    imageView1.layer.cornerRadius = 10;
    imageView1.backgroundColor = [UIColor grayColor];
    imageView1.contentMode = UIViewContentModeScaleAspectFit;
    [self.view addSubview:imageView1];
    
    
    UIImageView * imageView2 = [[UIImageView alloc] initWithFrame:CGRectMake(left2, top, w, h)];
    imageView2.image = [UIImage imageNamed:@"file_rar"];
    imageView2.layer.cornerRadius = 10;
    imageView2.backgroundColor = [UIColor grayColor];
    imageView2.contentMode = UIViewContentModeScaleAspectFit;
    imageView2.layer.masksToBounds = YES;
    [self.view addSubview:imageView2];
    
    
    CGFloat top1 = top + h + spacingH*2;
    
    //1.按钮存在背景图片
    UIButton *btn1 = [UIButton buttonWithType:UIButtonTypeCustom];
    btn1.frame = CGRectMake(left1, top1, w, h);
    btn1.layer.cornerRadius = 50;
    [self.view addSubview:btn1];
    
    [btn1 setImage:[UIImage imageNamed:@"file_rar"] forState:UIControlStateNormal];
    btn1.clipsToBounds = YES;
    
    //2.按钮不存在背景图片
    UIButton *btn2 = [UIButton buttonWithType:UIButtonTypeCustom];
    btn2.frame = CGRectMake(left2, top1, w, h);
    btn2.layer.cornerRadius = 50;
    btn2.backgroundColor = [UIColor blueColor];
    [self.view addSubview:btn2];
    btn2.clipsToBounds = YES;
    
    
    CGFloat top2 = top1 + h + spacingH*2;
    
    //3.UIImageView 设置了图片+背景色;
    UIImageView *img1 = [[UIImageView alloc]init];
    img1.frame = CGRectMake(left1, top2, w, h);
    img1.backgroundColor = [UIColor blueColor];
    [self.view addSubview:img1];
    img1.layer.cornerRadius = 50;
    img1.layer.masksToBounds = YES;
    img1.image = [UIImage imageNamed:@"file_rar"];
    
    //4.UIImageView 只设置了图片,无背景色;
    UIImageView *img2 = [[UIImageView alloc]init];
    img2.frame = CGRectMake(left2, top2, w, h);
    [self.view addSubview:img2];
    img2.layer.cornerRadius = 50;
    img2.layer.masksToBounds = YES;
    img2.image = [UIImage imageNamed:@"file_rar"];
    
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end

