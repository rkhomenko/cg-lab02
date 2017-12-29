// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#include <MyMainWindow.hpp>
#include <MyOpenGLWidget.hpp>
#include <Vertex.hpp>

#include <cstring>
#include <vector>

#include <QApplication>
#include <QDebug>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

static const std::vector<Vertex> POINTS = {
    Vertex(-0.90f, -0.90f), Vertex(0.85f, -0.90f), Vertex(-0.90f, 0.85f),
    Vertex(0.90f, -0.85f),  Vertex(0.90f, 0.90f),  Vertex(-0.85f, 0.90f)};

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
    Buffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    Buffer->allocate(POINTS.data(), sizeof(Vertex) * POINTS.size());

    VertexArray = new QOpenGLVertexArrayObject;
    VertexArray->create();
    VertexArray->bind();

    int posAttr = ShaderProgram->attributeLocation("position");
    ShaderProgram->enableAttributeArray(posAttr);
    ShaderProgram->setAttributeBuffer(posAttr, GL_FLOAT, Vertex::GetOffset(),
                                      Vertex::GetTupleSize(),
                                      Vertex::GetStride());

    VertexArray->release();
    Buffer->release();
    ShaderProgram->release();
}

void MyOpenGLWidget::resizeGL(int width, int height) {
    Matrix4x4 matrix = {1.0f * MyMainWindow::DEFAULT_SIZE.width() / width,
                        0.0f,
                        0.0f,
                        0.0f,
                        0.0f,  // second line
                        1.0f * MyMainWindow::DEFAULT_SIZE.height() / height,
                        0.0f,
                        0.0f,
                        0.0f,  // third line
                        0.0f,
                        1.0f,
                        0.0f,
                        0.0f,  // fours line
                        0.0f,
                        0.0f,
                        1.0f};

    // TODO: Calculate new point coordinates on GPU
    std::vector<Vertex> newVertexes;
    for (const auto& vertex : POINTS) {
        newVertexes.push_back(vertex.GetPositon() * matrix);
    }

    Buffer->bind();
    Buffer->write(0, newVertexes.data(), newVertexes.size() * sizeof(Vertex));
    Buffer->release();

    repaint();
}

void MyOpenGLWidget::paintGL() {
    if (!ShaderProgram->bind()) {
        qDebug() << "Cannot bind program";
        QApplication::quit();
    }

    VertexArray->bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
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
