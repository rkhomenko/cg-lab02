// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#include <MyMainWindow.hpp>
#include <MyOpenGLWidget.hpp>
#include <Pyramid.hpp>

#include <cmath>
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
    : QOpenGLWidget(parent),
      Pyramid8Faces{8, 0.9f, 0.9f},
      ScaleFactor{1.0f},
      AngleOX{0},
      AngleOY{0},
      AngleOZ{0} {
    auto sizePolicy =
        QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(sizePolicy);
}

void MyOpenGLWidget::ScaleUpSlot() {
    ScaleFactor *= SCALE_FACTOR_PER_ONCE;
    UpdateScaleMatrix();
}

void MyOpenGLWidget::ScaleDownSlot() {
    ScaleFactor /= SCALE_FACTOR_PER_ONCE;
    UpdateScaleMatrix();
}

void MyOpenGLWidget::OXAngleChangedSlot(FloatType angle) {
    AngleOX = angle;
    OnMatrixRegenerated(ROTATE_OX_MATRIX,
                        &MyOpenGLWidget::GenerateOXRotateMatrix);
}

void MyOpenGLWidget::OYAngleChangedSlot(FloatType angle) {
    AngleOY = angle;
    OnMatrixRegenerated(ROTATE_OY_MATRIX,
                        &MyOpenGLWidget::GenerateOYRotateMatrix);
}

void MyOpenGLWidget::OZAngleChangedSlot(FloatType angle) {
    AngleOZ = angle;
    OnMatrixRegenerated(ROTATE_OZ_MATRIX,
                        &MyOpenGLWidget::GenerateOZRotateMatrix);
}

void MyOpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();

    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this,
            &MyOpenGLWidget::CleanUp);

    ShaderProgram = new QOpenGLShaderProgram(this);
    ShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           VERTEX_SHADER);
    ShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           FRAGMENT_SHADER);

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

    int posAttr = ShaderProgram->attributeLocation(POSITION);
    ShaderProgram->enableAttributeArray(posAttr);
    ShaderProgram->setAttributeBuffer(posAttr, GL_FLOAT, Vertex::GetOffset(),
                                      Vertex::GetTupleSize(),
                                      Vertex::GetStride());
    auto color = QVector4D(0.0f, 0.0f, 1.0f, 1.0f);
    ShaderProgram->bind();
    ShaderProgram->setUniformValue(COLOR, color);

    SetUniformMatrix(ROTATE_OX_MATRIX, GenerateOXRotateMatrix());
    SetUniformMatrix(ROTATE_OY_MATRIX, GenerateOYRotateMatrix());
    SetUniformMatrix(ROTATE_OZ_MATRIX, GenerateOZRotateMatrix());

    VertexArray->release();
    Buffer->release();
    ShaderProgram->release();
}

void MyOpenGLWidget::resizeGL(int width, int height) {
    OnMatrixRegenerated(SCALE_MATRIX, &MyOpenGLWidget::GenerateScaleMatrix,
                        width, height);
}

void MyOpenGLWidget::paintGL() {
    if (!ShaderProgram->bind()) {
        qDebug() << "Cannot bind program";
        QApplication::quit();
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

void MyOpenGLWidget::UpdateScaleMatrix() {
    OnMatrixRegenerated(SCALE_MATRIX, &MyOpenGLWidget::GenerateScaleMatrix,
                        width(), height());
}

void MyOpenGLWidget::SetUniformMatrix(const char* uniformName,
                                      const QMatrix4x4& matrix) {
    ShaderProgram->bind();
    ShaderProgram->setUniformValue(uniformName, matrix);
    ShaderProgram->release();
}

QMatrix4x4 MyOpenGLWidget::GenerateScaleMatrix(int width, int height) const {
    const auto DEFAULT_WIDTH = MyMainWindow::DEFAULT_SIZE.width();
    const auto DEFAULT_HEIGHT = MyMainWindow::DEFAULT_SIZE.height();

    auto xScaleFactor = 1.0f * DEFAULT_WIDTH / width;
    auto yScaleFactor = 1.0f * DEFAULT_HEIGHT / height;

    GLfloat matrixData[] = {
        xScaleFactor * ScaleFactor,
        0.0f,
        0.0f,
        0.0f,  // first line
        0.0f,
        yScaleFactor * ScaleFactor,
        0.0f,
        0.0f,  // second line
        0.0f,
        0.0f,
        1.0f,
        0.0f,  // third line
        0.0f,
        0.0f,
        0.0f,
        1.0f  // fourth line
    };
    return QMatrix4x4(matrixData);
}

QMatrix4x4 MyOpenGLWidget::GenerateOXRotateMatrix() const {
    GLfloat matrixData[] = {
        1.0f,
        0,
        0,
        0,  // first line
        0,
        std::cos(AngleOX),
        std::sin(AngleOX),
        0,  // second line
        0,
        -std::sin(AngleOX),
        std::cos(AngleOX),
        0,  // third line
        0,
        0,
        0,
        1.0f  // fourth line
    };
    return QMatrix4x4(matrixData);
}

QMatrix4x4 MyOpenGLWidget::GenerateOYRotateMatrix() const {
    GLfloat matrixData[] = {
        std::cos(AngleOY),
        0,
        -std::sin(AngleOY),
        0,  // fist line
        0,
        1.0f,
        0,
        0,  // second line
        std::sin(AngleOY),
        0,
        std::cos(AngleOY),
        0,  // third line
        0,
        0,
        0,
        1.0f  // fourth line
    };
    return QMatrix4x4(matrixData);
}

QMatrix4x4 MyOpenGLWidget::GenerateOZRotateMatrix() const {
    GLfloat matrixData[] = {
        std::cos(AngleOZ),
        std::sin(AngleOZ),
        0,
        0,  // first line
        -std::sin(AngleOZ),
        std::cos(AngleOZ),
        0,
        0,  // second line
        0,
        0,
        1.0f,
        0,  // third line
        0,
        0,
        0,
        1.0f  // fourth line
    };
    return QMatrix4x4(matrixData);
}
