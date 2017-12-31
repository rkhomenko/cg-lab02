// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#include <MyMainWindow.hpp>
#include <MyOpenGLWidget.hpp>
#include <Pyramid.hpp>

#include <cstring>
#include <vector>

#include <QApplication>
#include <QDebug>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent), Pyramid8Faces{8, 0.9f, 0.9f} {}

void MyOpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();

    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this,
            &MyOpenGLWidget::CleanUp);

    ShaderProgram = new QOpenGLShaderProgram(this);
    ShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertexShader.glsl");
    ShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragmentShader.glsl");

    if (!ShaderProgram->link()) {
        qDebug() << ShaderProgram->log();
        QApplication::quit();
    }

    Buffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    Buffer->create();
    Buffer->bind();
    Buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    Buffer->allocate(Pyramid8Faces.GetData(),
                     sizeof(Vertex) * Pyramid8Faces.GetVerticesCount());

    VertexArray = new QOpenGLVertexArrayObject;
    VertexArray->create();
    VertexArray->bind();

    int posAttr = ShaderProgram->attributeLocation("position");
    ShaderProgram->enableAttributeArray(posAttr);
    ShaderProgram->setAttributeBuffer(posAttr, GL_FLOAT, Vertex::GetOffset(),
                                      Vertex::GetTupleSize(),
                                      Vertex::GetStride());
    auto color = QVector4D(0.0f, 0.0f, 1.0f, 1.0f);
    ShaderProgram->bind();
    ShaderProgram->setUniformValue("color", color);

    VertexArray->release();
    Buffer->release();
    ShaderProgram->release();
}

void MyOpenGLWidget::resizeGL(int width, int height) {
    const auto DEFAULT_WIDTH = MyMainWindow::DEFAULT_SIZE.width();
    const auto DEFAULT_HEIGHT = MyMainWindow::DEFAULT_SIZE.height();

    auto xScaleFactor = 1.0f * DEFAULT_WIDTH / width;
    auto yScaleFactor = 1.0f * DEFAULT_HEIGHT / height;

    GLfloat matrixData[] = {
        xScaleFactor, 0.0f,         0.0f, 0.0f,  // first line
        0.0f,         yScaleFactor, 0.0f, 0.0f,  // second line
        0.0f,         0.0f,         1.0f, 0.0f,  // third line
        0.0f,         0.0f,         0.0f, 1.0f   // fourth line
    };
    QMatrix4x4 matrix(matrixData);

    ShaderProgram->bind();
    ShaderProgram->setUniformValue("transformMatrix", matrix);
    ShaderProgram->release();

    repaint();
}

void MyOpenGLWidget::paintGL() {
    if (!ShaderProgram->bind()) {
        qDebug() << "Cannot bind program";
        QApplication::quit();
    }

    VertexArray->bind();
    glDrawArrays(GL_TRIANGLES, 0, Pyramid8Faces.GetVerticesCount());
    VertexArray->release();

    ShaderProgram->release();
}

void MyOpenGLWidget::CleanUp() {
    VertexArray->destroy();
    Buffer->destroy();
    delete VertexArray;
    delete Buffer;
    delete ShaderProgram;
}
