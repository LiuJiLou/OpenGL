//
//  ViewController.m
//  iOSOpenGLDemos
//
//  Created by liujilou on 2020/7/9.
//  Copyright © 2020 liujilou. All rights reserved.
//

#import "ViewController.h"
#import "DeviceHeader.h"
#import "OffscreenRenderingVC.h"

@interface ViewController ()<UITableViewDelegate,UITableViewDataSource>

@property(nonatomic, strong) UITableView * tableView;
@property(nonatomic, strong) NSArray * dataArr;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.dataArr = @[@{@"title":@"离屏渲染",@"code":@"1"},
                     ];
    
    [self.view addSubview:self.tableView];
}

- (UITableView *)tableView
{
    if (_tableView == nil) {
        _tableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 0, SCREEN_Width, SCREEN_Height) style:(UITableViewStylePlain)];
        _tableView.dataSource = self;
        _tableView.delegate = self;
    }
    return _tableView;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.dataArr.count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 50;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString * classificationCell = @"classificationCell";
    UITableViewCell * cell = [tableView dequeueReusableCellWithIdentifier:classificationCell];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:(UITableViewCellStyleDefault) reuseIdentifier:classificationCell];
    }
    NSDictionary * dic = (self.dataArr.count>indexPath.row)?self.dataArr[indexPath.row]:nil;
    cell.textLabel.text = dic[@"title"];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSDictionary * dic = (self.dataArr.count>indexPath.row)?self.dataArr[indexPath.row]:nil;
    int code = [dic[@"code"] intValue];

    UIViewController * vc = nil;
    if (code == 1) {
        vc = [[OffscreenRenderingVC alloc] init];
    }
    
    if (vc != nil) {
        [self.navigationController pushViewController:vc animated:YES];
//        [self presentViewController:vc animated:YES completion:^{}];
    }
}

@end
