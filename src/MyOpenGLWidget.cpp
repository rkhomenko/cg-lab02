// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#include <MyOpenGLWidget.hpp>
#include <Vertex.hpp>

#include <QApplication>
#include <QDebug>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

void MyOpenGLWidget::initializeGL() {
    const Vertex points[] = {Vertex(-0.90f, -0.90f), Vertex(0.85f, -0.90f),
                             Vertex(-0.90f, 0.85f),  Vertex(0.90f, -0.85f),
                             Vertex(0.90f, 0.90f),   Vertex(-0.85f, 0.90f)};

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

    Buffer = new QOpenGLBuffer;
    Buffer->create();
    Buffer->bind();
    Buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    Buffer->allocate(points, sizeof(points));

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

void MyOpenGLWidget::resizeGL([[maybe_unused]] int width,
                              [[maybe_unused]] int height) {}

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
