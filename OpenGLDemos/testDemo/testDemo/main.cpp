//
//  main.cpp
//  testDemo
//
//  Created by liujilou on 2020/7/3.
//  Copyright © 2020 liujilou. All rights reserved.
//

#include <stdio.h>
#include "GLTools.h"
#include <glut/glut.h>

GLBatch triangleBatch;
GLShaderManager shaderManager;
GLfloat stepSize;
GLfloat blockSize;

//窗口大小改变时接收新的宽度和高度，其中0，0 代表窗口中视图左下角坐标，w h 代表像素
void ChangeSize(int w, int h){
    glViewport(0, 0, w, h);
}

//为程序作一次性的设置
void SetupRC(){
//    设置背景颜色
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

//    初始化着色器管理器
    shaderManager.InitializeStockShaders();

//    设置三角形，其中数据vVert包含所有3个顶点的X，y 笛卡尔坐标对
    GLfloat vVerts[] = {
        -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };

//    批次处理
    triangleBatch.Begin(GL_TRIANGLES, 3);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
}

//开始渲染
void RenderScene(void)
{
//    清除一个或一组特定的缓冲区
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    
//    设置一组浮点数来表示红色
    GLfloat VRed[] = {1.0f,0.0f,0.0f,1.0f};
    
//传递到存储着色器，即GLT_SHADER_IDENTITY着色器，这个着色器只是使用指定颜色以默认笛卡尔坐标第在屏幕上渲染几何图形
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, VRed);
    
//    提交着色器
    triangleBatch.Draw();
    
//    将在后台缓冲器进行渲染，然后在结束时交换到前台
    glutSwapBuffers();
}

// ------------------------- 正方形 ------------------------
//void SetupRC(){
//    glClearColor(0.98, 0.7, 0.4, 1.0);
//    shaderManager.InitializeStockShaders();
//    triangleBatch.Begin(GL_TRIANGLE_FAN, 4);
////    设置，其中数据vVert包含所有3个顶点的X，y 笛卡尔坐标对
//    GLfloat vVerts[] = {
//        -blockSize, -blockSize, 0.0f,
//        blockSize,  -blockSize, 0.0f,
//        blockSize,  blockSize,  0.0f,
//        -blockSize, blockSize,  0.0f,
//    };
//    triangleBatch.CopyVertexData3f(vVerts);
//    triangleBatch.End();
//}
//
////移动顶点 -> 修改每一个顶点相对位置
////不需要 -> 记录移动步长，碰撞检测
//void SpecialKey(int key, int  x, int y){
////    移动步长
//    GLfloat stepSize = 0.025f;
//
//    if(key == GLUT_KEY_UP){
//        blockX -= stepSize;
//    }
//    if(key == GLUT_KEY_DOWN){
//        blockX -= stepSize;
//    }
//    if(key == GLUT_KEY_LEFT){
//        blockX -= stepSize;
//    }
//    if(key == GLUT_KEY_RIGHT){
//        blockX -= stepSize;
//    }
//
//}
//
//void RenderScene(void)
//{
////    绘制
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//    GLfloat vRed[] = {1.0f,0.0f,0.0f,0.0f};
//
////    1、矩阵
//    M3DMatrix44f mTransfromMatrix;
//
////    平移矩阵 -> 3D 数学课会讲 矩阵 向量 -> 3D
//    m3dTranslationMatrix44(mTransfromMatrix, xPos, yPos, 0.0f);
//
////    平面着色器（固定着色器）
//    shaderManager.UseStockShader(GLT_STOCK_FlAT, mTransfromMatrix, vRed);
//
//    triangleBatch.Draw();
//
//}

int main(int argc, char * argv[])
{
//    设置当前工作目录，针对MAC OS X
    gltSetWorkingDirectory(argv[0]);
    
//    初始化GLUT 库
    glutInit(&argc, argv);
    
//    初始化双缓冲窗口，其中标志 GLUT_DOUBLE、GLUT_RGBA、GLUT_DEPTH、GLUT_STENCIL分别指双缓冲窗口、RGB颜色模式、深度测试、模板缓冲区
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triangle");
    
//    注册回调函数
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    
//    驱动程序的初始化中没有出现任何问题。
    GLenum err = glewInit();
    
    if(GLEW_OK != err){
        fprintf(stderr, "glew error:%s\n", glewGetErrorString(err));
        return 1;
    }
    
//    调用SetupRC
    SetupRC();
    glutMainLoop();
    return 0;
}
