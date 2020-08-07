//
//  LJLViewController.m
//  002--test
//
//  Created by liujilou on 2020/8/6.
//  Copyright © 2020 liujilou. All rights reserved.
//

#import "LJLViewController.h"
#import "faceView.h"

@interface LJLViewController ()

@property (nonatomic, strong) UIView * containerView;

@property (nonatomic, strong) NSArray *faces;
@property (nonatomic, strong) CADisplayLink * displayLink;
@property (nonatomic, assign) NSInteger angle;

@end

@implementation LJLViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
//    添加面
    [self addCFaces];
    
//    添加CADisplay
    [self addCADisplayLink];
}

-(void)addCADisplayLink
{
    self.angle = 0;
    self.displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update)];
    [self.displayLink addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSRunLoopCommonModes];
}

-(void)addCFaces
{
    faceView * view0 = [self getFaceViewText:@"0"];
    faceView * view1 = [self getFaceViewText:@"1"];
    faceView * view2 = [self getFaceViewText:@"2"];
    faceView * view3 = [self getFaceViewText:@"3"];
    faceView * view4 = [self getFaceViewText:@"4"];
    faceView * view5 = [self getFaceViewText:@"5"];
    
    self.faces = @[view0,view1,view2,view3,view4,view5];
    
//    父View 的layer图层
    CATransform3D perspective = CATransform3DIdentity;
    perspective.m34 = -1.0 / 500.0;
    perspective = CATransform3DRotate(perspective, -M_PI_4, 1, 0, 0);
    perspective = CATransform3DRotate(perspective, -M_PI_4, 0, 1, 0);
    self.containerView.layer.sublayerTransform = perspective;
    
//    add cube face 1
    CATransform3D transform = CATransform3DMakeTranslation(0, 0, 100);
    [self addFace:0 withTransform:transform];
    
//    add cube face 2
    transform = CATransform3DMakeTranslation(100, 0, 0);
    transform = CATransform3DRotate(transform, M_PI_2, 0, 1, 0);
    [self addFace:1 withTransform:transform];
    
    //    add cube face 3
    transform = CATransform3DMakeTranslation(0, -100, 0);
    transform = CATransform3DRotate(transform, M_PI_2, 1, 0, 0);
    [self addFace:2 withTransform:transform];
    
    //    add cube face 4
    transform = CATransform3DMakeTranslation(0, 100, 0);
    transform = CATransform3DRotate(transform, -M_PI_2, 1, 0, 0);
    [self addFace:3 withTransform:transform];
    
    //    add cube face 5
    transform = CATransform3DMakeTranslation(-100, 0, 0);
    transform = CATransform3DRotate(transform, -M_PI_2, 0, 1, 0);
    [self addFace:4 withTransform:transform];
    
    //    add cube face 6
    transform = CATransform3DMakeTranslation(0, 0, -100);
    transform = CATransform3DRotate(transform, M_PI, 0, 1, 0);
    [self addFace:5 withTransform:transform];
}

-(void)addFace:(NSInteger)index withTransform:(CATransform3D)transfrom
{
//    获取face 视图并将其添加到容器中
    UIView *face = self.faces[index];
    [self.containerView addSubview:face];
    
//    将face 视图放在容器的中心
    CGSize containerSize = self.containerView.bounds.size;
    face.center = CGPointMake(containerSize.width / 2.0, containerSize.height / 2.0);
    
//    添加transform
    face.layer.transform = transfrom;
}

-(void)update{
//    1、计算旋转度数
    self.angle = (self.angle + 5) % 360;
    float deg = self.angle * (M_PI / 180);
    CATransform3D temp = CATransform3DIdentity;
    temp = CATransform3DRotate(temp, deg, 0.3, 1, 0.7);
    self.containerView.layer.sublayerTransform = temp;
}

- (UIView *)containerView
{
    if (!_containerView) {
        _containerView = [[UIView alloc] initWithFrame:self.view.bounds];
        _containerView.backgroundColor = [UIColor blackColor];
        [self.view addSubview:_containerView];
    }
    return _containerView;
}

-(faceView *)getFaceViewText:(NSString *)text
{
    CGFloat r = (arc4random() % 255)/255.f;
    CGFloat g = (arc4random() % 255)/255.f;
    CGFloat b = (arc4random() % 255)/255.f;
    
    faceView * view = [[faceView alloc] initWithFrame:CGRectMake(0, 0, 200, 200)];
    UIColor * color = [UIColor colorWithRed:r green:g blue:b alpha:1.0f];
    [view setText:text backgroundColor:color];
    return view;
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
