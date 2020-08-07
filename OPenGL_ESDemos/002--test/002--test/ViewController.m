//
//  ViewController.m
//  002--test
//
//  Created by liujilou on 2020/7/27.
//  Copyright © 2020 liujilou. All rights reserved.
//

#import "ViewController.h"
#import "LJLView.h"
#import <GLKit/GLKit.h>
#import "LJLViewController.h"

typedef struct {
    GLKVector3 positionCoord;   //顶点坐标
    GLKVector2 textureCoord;    //纹理坐标
    GLKVector3  normal;         //法线
} LJLVertex;

//顶点数(正方体有6个面需要12个三角形组成，不使用重复顶点的话需要36个)
static NSInteger const kCoordCount = 36;

@interface ViewController ()<GLKViewDelegate>
//demo1
@property (nonatomic, strong) LJLView * myView;


//demo2
@property (nonatomic, strong) GLKView * glkView;
@property (nonatomic, strong) GLKBaseEffect * baseEffect;
@property (nonatomic, assign) LJLVertex * vertices;

@property (nonatomic, strong) CADisplayLink * displayLink;
@property (nonatomic, assign) NSInteger angle;
@property (nonatomic, assign) GLuint vertexBuffer;


//demo3

@end


@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

//    [self testDemo1];
//    [self testDemo2];
    [self testDemo3];
}

-(void)testDemo1
{
//    这样写的话新版不调用view的layoutSubviews
//    self.myView = (LJLView *)self.view;
    
//
    self.myView = [[LJLView alloc] initWithFrame:self.view.frame];
    [self.view addSubview:self.myView];
}

//用一张图片组成一个立方体
-(void)testDemo2
{
    //    1、View 背景
    self.view.backgroundColor = [UIColor blackColor];

    //2、OpenGL ES 相关初始化
    [self commonInit];
    
//    3、添加CADisplayLink
    [self addCADisplayLink];
}

- (void)dealloc
{
    if ([EAGLContext currentContext] == self.glkView.context) {
        [EAGLContext setCurrentContext:nil];
    }
    if (_vertices) {
        free(_vertices);
        _vertices = nil;
    }
    
    if (_vertexBuffer) {
        glDeleteBuffers(1, &_vertexBuffer);
        _vertexBuffer = 0;
    }
    
//    displayLink 失效
    [self.displayLink invalidate];
}

//CADisplayLink
-(void)addCADisplayLink
{
//    CADisplayLink 类似定时器，提供一个周期性调用，属于QuartzCore.framework中
//    具体可以参考博客  https://www.cnblogs.com/panyangjun/p/4421904.html
//    iOS设备的屏幕刷新频率(FPS)是60Hz，因此CADisplayLink的selector 默认调用周期是每秒60次，这个周期可以通过frameInterval属性设置， CADisplayLink的selector每秒调用次数=60/ frameInterval。比如当 frameInterval设为2，每秒调用就变成30次。因此， CADisplayLink 周期的设置方式略显不便。
    self.angle = 0;
    self.displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update)];
    self.displayLink.frameInterval = 60;
    [self.displayLink addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSRunLoopCommonModes];
}

-(void)commonInit
{
//    1、创建context
    EAGLContext *context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
//    设置当前context
    [EAGLContext setCurrentContext:context];
    
//    2、创建GLKview 并设置代理
    CGRect frame = CGRectMake(0, 100, self.view.frame.size.width, self.view.frame.size.width);
    self.glkView = [[GLKView alloc] initWithFrame:frame context:context];
    self.glkView.backgroundColor = [UIColor clearColor];
    self.glkView.delegate = self;
    
//    3、使用深度缓存
    self.glkView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
//    默认是（0，1），这里用于翻转 Z 轴，使正方形朝屏幕外
    glDepthRangef(1, 0);
    
//    4、将GLKView 添加self.view 上
    [self.view addSubview:self.glkView];
    
//    5、获取纹理图片
    NSString * imagePath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"testImage.png"];
    UIImage * image = [UIImage imageWithContentsOfFile:imagePath];
    
//    6、设置纹理参数
    NSDictionary * options = @{GLKTextureLoaderOriginBottomLeft : @(YES)};
    GLKTextureInfo * textureInfo = [GLKTextureLoader textureWithCGImage:[image CGImage] options:options error:NULL];
    
//    7、使用baseEffect
    self.baseEffect = [[GLKBaseEffect alloc] init];
    self.baseEffect.texture2d0.name = textureInfo.name;
    self.baseEffect.texture2d0.target = textureInfo.target;
//    开启关照效果
    self.baseEffect.light0.enabled = YES;
//    漫反射颜色
    self.baseEffect.light0.diffuseColor = GLKVector4Make(1, 1, 1, 1);
//    光照位置
    self.baseEffect.light0.position = GLKVector4Make(-0.5, -0.5, 5, 1);
    
    /*
     解释一下：
     这里我们不复用顶点，使用每 3 个点画一个三角形的方式，需要12个三角形，则需要 36 个顶点，一下的数据用来绘制以（0，0，0）为中心，边长为 1 的立方体
     */
    
//    8、开辟顶点数据空间（数据结构SenceVertex 大小 * 顶点个数kCoordCount）
    self.vertices = malloc(sizeof(LJLVertex) * kCoordCount);
    
    // 前面
    self.vertices[0] = (LJLVertex){{-0.5, 0.5, 0.5}, {0, 1}, {0, 0, 1}};
    self.vertices[1] = (LJLVertex){{-0.5, -0.5, 0.5}, {0, 0}, {0, 0, 1}};
    self.vertices[2] = (LJLVertex){{0.5, 0.5, 0.5}, {1, 1}, {0, 0, 1}};
    self.vertices[3] = (LJLVertex){{-0.5, -0.5, 0.5}, {0, 0}, {0, 0, 1}};
    self.vertices[4] = (LJLVertex){{0.5, 0.5, 0.5}, {1, 1}, {0, 0, 1}};
    self.vertices[5] = (LJLVertex){{0.5, -0.5, 0.5}, {1, 0}, {0, 0, 1}};
    
    // 上面
    self.vertices[6] = (LJLVertex){{0.5, 0.5, 0.5}, {1, 1}, {0, 1, 0}};
    self.vertices[7] = (LJLVertex){{-0.5, 0.5, 0.5}, {0, 1}, {0, 1, 0}};
    self.vertices[8] = (LJLVertex){{0.5, 0.5, -0.5}, {1, 0}, {0, 1, 0}};
    self.vertices[9] = (LJLVertex){{-0.5, 0.5, 0.5}, {0, 1}, {0, 1, 0}};
    self.vertices[10] = (LJLVertex){{0.5, 0.5, -0.5}, {1, 0}, {0, 1, 0}};
    self.vertices[11] = (LJLVertex){{-0.5, 0.5, -0.5}, {0, 0}, {0, 1, 0}};
    
    // 下面
    self.vertices[12] = (LJLVertex){{0.5, -0.5, 0.5}, {1, 1}, {0, -1, 0}};
    self.vertices[13] = (LJLVertex){{-0.5, -0.5, 0.5}, {0, 1}, {0, -1, 0}};
    self.vertices[14] = (LJLVertex){{0.5, -0.5, -0.5}, {1, 0}, {0, -1, 0}};
    self.vertices[15] = (LJLVertex){{-0.5, -0.5, 0.5}, {0, 1}, {0, -1, 0}};
    self.vertices[16] = (LJLVertex){{0.5, -0.5, -0.5}, {1, 0}, {0, -1, 0}};
    self.vertices[17] = (LJLVertex){{-0.5, -0.5, -0.5}, {0, 0}, {0, -1, 0}};
    
    // 左面
    self.vertices[18] = (LJLVertex){{-0.5, 0.5, 0.5}, {1, 1}, {-1, 0, 0}};
    self.vertices[19] = (LJLVertex){{-0.5, -0.5, 0.5}, {0, 1}, {-1, 0, 0}};
    self.vertices[20] = (LJLVertex){{-0.5, 0.5, -0.5}, {1, 0}, {-1, 0, 0}};
    self.vertices[21] = (LJLVertex){{-0.5, -0.5, 0.5}, {0, 1}, {-1, 0, 0}};
    self.vertices[22] = (LJLVertex){{-0.5, 0.5, -0.5}, {1, 0}, {-1, 0, 0}};
    self.vertices[23] = (LJLVertex){{-0.5, -0.5, -0.5}, {0, 0}, {-1, 0, 0}};
    
    // 右面
    self.vertices[24] = (LJLVertex){{0.5, 0.5, 0.5}, {1, 1}, {1, 0, 0}};
    self.vertices[25] = (LJLVertex){{0.5, -0.5, 0.5}, {0, 1}, {1, 0, 0}};
    self.vertices[26] = (LJLVertex){{0.5, 0.5, -0.5}, {1, 0}, {1, 0, 0}};
    self.vertices[27] = (LJLVertex){{0.5, -0.5, 0.5}, {0, 1}, {1, 0, 0}};
    self.vertices[28] = (LJLVertex){{0.5, 0.5, -0.5}, {1, 0}, {1, 0, 0}};
    self.vertices[29] = (LJLVertex){{0.5, -0.5, -0.5}, {0, 0}, {1, 0, 0}};
    
    // 后面
    self.vertices[30] = (LJLVertex){{-0.5, 0.5, -0.5}, {0, 1}, {0, 0, -1}};
    self.vertices[31] = (LJLVertex){{-0.5, -0.5, -0.5}, {0, 0}, {0, 0, -1}};
    self.vertices[32] = (LJLVertex){{0.5, 0.5, -0.5}, {1, 1}, {0, 0, -1}};
    self.vertices[33] = (LJLVertex){{-0.5, -0.5, -0.5}, {0, 0}, {0, 0, -1}};
    self.vertices[34] = (LJLVertex){{0.5, 0.5, -0.5}, {1, 1}, {0, 0, -1}};
    self.vertices[35] = (LJLVertex){{0.5, -0.5, -0.5}, {1, 0}, {0, 0, -1}};
    
//    开辟顶点缓存区
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    GLsizeiptr bufferSizeBytes = sizeof(LJLVertex) * kCoordCount;
    glBufferData(GL_ARRAY_BUFFER, bufferSizeBytes, self.vertices, GL_STATIC_DRAW);
    
//    顶点数据
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(LJLVertex), NULL + offsetof(LJLVertex, positionCoord));
    
//    纹理数据
    glEnableVertexAttribArray(GLKVertexAttribTexCoord0);
    glVertexAttribPointer(GLKVertexAttribTexCoord0, 2, GL_FLOAT, GL_FALSE, sizeof(LJLVertex), NULL + offsetof(LJLVertex, textureCoord));
    
//    法线数据
    glEnableVertexAttribArray(GLKVertexAttribNormal);
    glVertexAttribPointer(GLKVertexAttribNormal, 3, GL_FLOAT, GL_FALSE, sizeof(LJLVertex), NULL + offsetof(LJLVertex, normal));
}

#pragma mark - GLKViewDelegate
-(void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
//    1、开启深度测试
    glEnable(GL_DEPTH_TEST);
//    2、清除颜色缓存区&深度缓存区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    3、准备绘制
    [self.baseEffect prepareToDraw];
//    4、绘图
    glDrawArrays(GL_TRIANGLES, 0, kCoordCount);
}


#pragma mark - updata
-(void)update
{
//    1、计算旋转度数
    self.angle = (self.angle + 5) % 360;
//    2、修改 self.baseEffect.transform.modelviewMatrix
    self.baseEffect.transform.modelviewMatrix = GLKMatrix4MakeRotation(GLKMathDegreesToRadians(self.angle), 0.3, 1, 0.7);
//    3、重新渲染
    [self.glkView display];
}




-(void)testDemo3
{
    UIView * view = [[UIView alloc] initWithFrame:self.view.frame];
    view.backgroundColor = [UIColor whiteColor];
    [self.view addSubview:view];
    
    UIButton * button = [[UIButton alloc] initWithFrame:CGRectMake(50, 50, self.view.frame.size.width-100, 50)];
    button.backgroundColor = [UIColor orangeColor];
    [button setTitle:@"数字立方体" forState:(UIControlStateNormal)];
    [button addTarget:self action:@selector(didClickButton) forControlEvents:(UIControlEventTouchUpInside)];
    [view addSubview:button];
}

-(void)didClickButton
{
    LJLViewController * vc = [[LJLViewController alloc] init];
    [self presentViewController:vc animated:YES completion:nil];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
