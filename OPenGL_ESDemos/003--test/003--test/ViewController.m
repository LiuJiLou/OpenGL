//
//  ViewController.m
//  003--test
//
//  Created by liujilou on 2020/7/27.
//  Copyright © 2020 liujilou. All rights reserved.
//

#import "ViewController.h"
#import "LJLView1.h"

@interface ViewController ()

@property (nonatomic, strong) LJLView1 * myView;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.myView = [[LJLView1 alloc] initWithFrame:self.view.bounds];
    self.myView.processingType =
    ProcessingType_one;
//    ProcessingType_two;
//    ProcessingType_three;
//    ProcessingType_four;
//    ProcessingType_five;
    
    [self.view addSubview:self.myView];
    
}

@end
