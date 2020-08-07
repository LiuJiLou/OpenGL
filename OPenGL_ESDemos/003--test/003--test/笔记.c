//
//  笔记.c
//  003--test
//
//  Created by liujilou on 2020/7/27.
//  Copyright © 2020 liujilou. All rights reserved.
//

#include <stdio.h>

/*
 3种数据修饰类型
 uniform， attribute， fragment 变量
 
 uniform -> 传递到vertex，fragment 变量
 gluniform...
 
 vertex， fragment -> 常量
 uniform -> 客户端 -> 顶点 / 片元着色器
 在顶点 / 片元着色器 进行一样的声明 -> 都传进去。
 用途：视图矩阵，投影矩阵，投影视图矩阵
 
 uniform mat4 viewProMatrix
 glUniform...
 
 attribute: 特点 -> 客户端 -> 顶点着色器 / 顶点着色器
 用修饰什么数据: 顶点，纹理坐标，颜色，法线 -> 坐标颜色有关
 glVertex...
 
 纹理坐标 -> 二维
 
 用的最多的数据类型
 attribute vec4 position;
 attribute vec4 color;
 attribute vec2 textCoord;
 
 
 顶点着色器的功能就是计算顶点
 gl_Position = position;
 
 片元着色器
 精度，写一下默认实现一个精度
 
 纹素
 
 texture2D（纹理，纹理坐标）  返回一个颜色值
 
 
 
 
 */
