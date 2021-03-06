//
//  main.cpp
//  3.donuts
//
//  Created by liujilou on 2020/7/19.
//  Copyright © 2020 liujilou. All rights reserved.
//

#include <stdio.h>
//演示了OpenGL背面剔除，深度测试，和多边形模式
#include "GLTools.h"
#include "GLMatrixStack.h"
#include "GLFrame.h"
#include "GLFrustum.h"
#include "GLGeometryTransform.h"

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

//设置角色帧，作为相机
GLFrame             viewFrame;
//使用 GLFrustum 类来设置透视投影
GLFrustum           viewFrustum;
GLTriangleBatch     torusBatch;
GLMatrixStack       modelViewMatix;
GLMatrixStack       projectionMatix;
GLGeometryTransform transformPipeline;
GLShaderManager     shaderManager;

GLFrame             cameraFrame;
//标记：背面剔除、深度测试
int iCull = 0;
int iDepth = 0;

void RenderScene()
{
//    1、清除窗口和深度缓冲区
//    如果不清理会有残留数据（如图1）
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
//    开启表面剔除
//    glEnable(GL_CULL_FACE);
    
//    开启深度测试
    glEnable(GL_DEPTH_TEST);
    
//    2、把摄像机矩阵压入模型矩阵中
    modelViewMatix.PushMatrix(viewFrame);
    
//    modelViewMatix.PushMatrix();
//    M3DMatrix44f mCamera;
//    cameraFrame.GetCameraMatrix(mCamera);
//
//    modelViewMatix.MultMatrix(mCamera);
//
//    M3DMatrix44f mObjectFrame;
//    viewFrame.GetMatrix(mObjectFrame);
//    modelViewMatix.MultMatrix(mObjectFrame);
    
//    3、设置绘图颜色
    GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
    
//    4、
//    使用平面着色器
//    参数1：平面着色器
//    参数2：模型视图矩阵
//    参数3：颜色
//    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vRed);
    
//    使用默光源着色器
//    通过光源、阴影效果体现立体效果
//    参数1：GLT_SHADER_DEFAULT_LIGHT 默认光源着色器
//    参数2：模型视图矩阵
//    参数3：投影矩阵
//    参数4：基本颜色值
    shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vRed);
    
//    5、绘制
    torusBatch.Draw();
    
//    6、出栈 绘制完成恢复
    modelViewMatix.PopMatrix();
    
//    7、交换缓冲区
    glutSwapBuffers();

}


void SetupRC()
{
//    1、用当前颜色清除背景颜色，如果不清除的话在动的时候会有残影
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    
//    2、初始化着色器管理器
    shaderManager.InitializeStockShaders();
    
//    3、将相机向后移动10个单元：肉眼到物体之间的距离
    viewFrame.MoveForward(10.0f);
//    viewFrame.MoveForward(-10.0f);//设置成负值就看不到圆环了示意
//    圆环  相机  我们的方向，圆环在我们相机看的后面是看不到的
    
//    4、创建一个甜甜圈（圆环）
    //void gltMakeTorus(GLTriangleBatch& torusBatch, GLfloat majorRadius, GLfloat minorRadius, GLint numMajor, GLint numMinor);
//    参数1：GLTriangleBatch 容器帮助类
//    参数2：外边缘半径
//    参数3：内边缘半径
//    参数4、5：主半径从半径的细分单元数量
    gltMakeTorus(torusBatch, 1.0f, 0.3f, 52, 26);
    
//    5、点的大小（方便点填充时，肉眼观察）
    glPointSize(4.0f);
}


//键位设置，通过不同的键位对其进行设置
//控制 Camera 的移动，从而改变视口
void SpecialKeys(int key, int x, int y)
{
//    1、判断方向键
    if(key == GLUT_KEY_UP)
//        2、根据方向调整观察者位置
        viewFrame.RotateWorld(m3dDegToRad(-5.0), 1.0f, 0.0f, 0.0f);
    if(key == GLUT_KEY_DOWN)
        viewFrame.RotateWorld(m3dDegToRad(5.0), 1.0f, 0.0f, 0.0f);
    if(key == GLUT_KEY_LEFT)
        viewFrame.RotateWorld(m3dDegToRad(-5.0), 0.0f, 1.0f, 0.0f);
    if(key == GLUT_KEY_RIGHT)
        viewFrame.RotateWorld(m3dDegToRad(5.0), 0.0f, 1.0f, 0.0f);
    
//    3、重新刷新
    glutPostRedisplay();
}


//窗口改变
void ChangeSize(int w, int h)
{
//    1、防止h变为0
    if(h == 0)
        h = 1;
    
//    2、设置视口尺寸
    glViewport(0, 0, w, h);
    
//    3、setPerspective 函数的参数是一个从顶点方向看去的视场角度（用角度值表示）
//    设置透视模式，初始化其透视矩阵
    viewFrustum.SetPerspective(35.f, float(w)/float(h), 1.0f, 100.0f);
    
//4、把透视矩阵加载到透视矩阵堆栈中
    projectionMatix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    
//    5、初始化渲染管道
    transformPipeline.SetMatrixStacks(modelViewMatix, projectionMatix);
}

int main(int argc, char * argv[])
{
    gltSetWorkingDirectory(argv[0]);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Geometry Test Program");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    
    SetupRC();
    
    glutMainLoop();
    return 0;
}
