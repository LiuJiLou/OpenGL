//
//  main.cpp
//  2、金字塔
//
//  Created by liujilou on 2020/7/12.
//  Copyright © 2020 liujilou. All rights reserved.
//

#include <stdio.h>
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

//着色器管理类
GLShaderManager     shaderManager;
//模型视图矩阵堆栈
GLMatrixStack       modelViewMatrix;
//投影矩阵堆栈
GLMatrixStack       projectionMatrix;
//照相机 参数帧
GLFrame             cameraFrame;
//模型 参考帧
GLFrame             objectFrame;
//投影矩阵
GLFrustum           viewFrustum;

//容器类 对应GL_TRIANGLES（三角形） 图元类型
GLBatch             triangleBatch;

//几何变换的管道
GLGeometryTransform transformPipeline;

GLfloat vGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };

//跟踪效果步骤
int nStep = 0;

//设置视口的大小等
void ChangeSize(int w, int h)
{
//    1、设置视口大小
    glViewport(0, 0, w, h);
//    2、创建投影矩阵，并将它载入投影矩阵堆栈中
    viewFrustum.SetPerspective(35.0f, float(w)/float(h), 1.0f, 500.0f);
//    3、将投影矩阵载入投影堆栈
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());

//    将单元矩阵载入模型视图矩阵堆栈
    modelViewMatrix.LoadIdentity();
}



//此函数在呈现上下文中进行任何必要的初始化
//这是第一次或任何与openGL 相关的任务
void SetupRC()
{
//    1、灰色的背景
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
//    2、初始化着色器
    shaderManager.InitializeStockShaders();
    
//    3、启动深度测试，不开启的话看到的黑色边线会透视过来（如图）
    glEnable(GL_DEPTH_TEST);
//    4、设置变换管线以使用两个矩阵堆栈
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
    
//    5、将相机向前移动15个单元
    cameraFrame.MoveForward(-15.0f);

/*
 常见函数
 void GLBatch::Begin(GLenum primitive,GLuint nVerts,GLuint nTextureUnits = 0);
       参数1：表示使用的图元
       参数2：顶点数
       参数3：纹理坐标（可选）

      //负责顶点坐标
      void GLBatch::CopyVertexData3f(GLFloat *vNorms);

      //结束，表示已经完成数据复制工作
      void GLBatch::End(void);
 */
//    6、通过三角形创建金字塔
    GLfloat vPyramid[12][3] = {
        -2.0f, 0.0f, -2.0f,
        2.0f, 0.0f, -2.0f,
        0.0f, 4.0f, 0.0f,

        2.0f, 0.0f, -2.0f,
        2.0f, 0.0f, 2.0f,
        0.0f, 4.0f, 0.0f,

        2.0f, 0.0f, 2.0f,
        -2.0f, 0.0f, 2.0f,
        0.0f, 4.0f, 0.0f,

        -2.0f, 0.0f, 2.0f,
        -2.0f, 0.0f, -2.0f,
        0.0f, 4.0f, 0.0f
    };
//    GL_TRIANGLES 每3个顶点定义一个新的三角形
    triangleBatch.Begin(GL_TRIANGLES, 12);
    triangleBatch.CopyVertexData3f(vPyramid);
    triangleBatch.End();
}


//方法主要实现金字塔的黑色边缘
void DrawWireFramedBatch(GLBatch* pBatch)
{
    /*------------画绿色部分----------------*/
    /* GLShaderManager 中的Uniform 值——平面着色器
     参数1：平面着色器
     参数2：运行为几何图形变换指定一个 4 * 4变换矩阵
          --transformPipeline 变换管线（指定了2个矩阵堆栈）
     参数3：颜色值
    */
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vGreen);
    pBatch->Draw();

    /*-----------边框部分-------------------*/
    /*
        glEnable(GLenum mode); 用于启用各种功能。功能由参数决定
        参数列表：http://blog.csdn.net/augusdi/article/details/23747081
        注意：glEnable() 不能写在glBegin() 和 glEnd()中间
        GL_POLYGON_OFFSET_LINE  根据函数glPolygonOffset的设置，启用线的深度偏移
        GL_LINE_SMOOTH          执行后，过虑线点的锯齿
        GL_BLEND                启用颜色混合。例如实现半透明效果
        GL_DEPTH_TEST           启用深度测试 根据坐标的远近自动隐藏被遮住的图形（材料


        glDisable(GLenum mode); 用于关闭指定的功能 功能由参数决定

     */
//    黑色边框
//偏移深度，在同一位置要绘制填充和边线，会产生冲突（离得太近，系统会区分不出来要显示什么），所以要偏移
    glPolygonOffset(-1.0f, -1.0f);
//    多边形
    glEnable(GL_POLYGON_OFFSET_LINE);

//    画反锯齿(更平滑)，让黑边好看些
    glEnable(GL_LINE_SMOOTH);
    
//    混合
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //绘制线框几何黑色版 三种模式，实心，边框，点，可以作用在正面，背面，或者两面
    //通过调用glPolygonMode将多边形正面或者背面设为线框模式，实现线框渲染
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //设置线条宽度
    glLineWidth(2.5f);

    /* GLShaderManager 中的Uniform 值——平面着色器
     参数1：平面着色器
     参数2：运行为几何图形变换指定一个 4 * 4变换矩阵
         --transformPipeline.GetModelViewProjectionMatrix() 获取的
          GetMatrix函数就可以获得矩阵堆栈顶部的值
     参数3：颜色值（黑色）
     */

    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vBlack);
    pBatch->Draw();

    // 复原原本的设置
    //通过调用glPolygonMode将多边形正面或者背面设为全部填充模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
    glLineWidth(1.0f);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
}


void RenderScene(void)
{
//    用当前清除颜色清除窗口
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//    压栈
    modelViewMatrix.PushMatrix();
//    相机矩阵
    M3DMatrix44f mCanera;
    cameraFrame.GetCameraMatrix(mCanera);

//    矩阵乘以矩阵堆栈的顶部矩阵，相乘的结果随后存入栈顶
    modelViewMatrix.MultMatrix(mCanera);

    M3DMatrix44f mObjectFrame;
//    只要使用 GetMatrix 函数就可以获取矩阵堆栈栈顶的值，这个函数可以进行2次重载用来使用GLShaderManager 的使用。或者是获取顶部矩阵的顶点副本数据
    objectFrame.GetMatrix(mObjectFrame);

//    矩阵乘以矩阵堆栈栈顶的矩阵，相乘的结果存储在栈顶
    modelViewMatrix.MultMatrix(mObjectFrame);

    /* GLShaderManager 中的Uniform 值——平面着色器
    参数1：平面着色器
    参数2：运行为几何图形变换指定一个 4 * 4变换矩阵
    --transformPipeline.GetModelViewProjectionMatrix() 获取的
    GetMatrix函数就可以获得矩阵堆栈顶部的值
    参数3：颜色值（黑色）
    */
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vBlack);

    DrawWireFramedBatch(&triangleBatch);

//    还原到以前的模型视图矩阵（单位矩阵）
    modelViewMatrix.PopMatrix();

//    进行缓冲区交换
    glutSwapBuffers();
}



//通过上下左右键控制翻转
void SpecialKeys(int key, int x, int y)
{
    if(key == GLUT_KEY_UP)
        objectFrame.RotateWorld(m3dDegToRad(-5.0f), 1.0f, 0.0f, 0.0f);
    
    if(key == GLUT_KEY_DOWN)
        objectFrame.RotateWorld(m3dDegToRad(5.0f), 1.0f, 0.0f, 0.0f);
    
    if(key == GLUT_KEY_LEFT)
        objectFrame.RotateWorld(m3dDegToRad(-5.0f), 0.0f, 1.0f, 0.0f);
    
    if(key == GLUT_KEY_RIGHT)
        objectFrame.RotateWorld(m3dDegToRad(5.0f), 0.0f, 1.0f, 0.0f);
    
    glutPostRedisplay();
}



int main(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Pyramid");
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
    
//    ShutdownRC();
    
    return 0;
}
