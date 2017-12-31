// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#ifndef CG_LAB_MYOPENGLWIDGET_HPP_
#define CG_LAB_MYOPENGLWIDGET_HPP_

#include <Pyramid.hpp>

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

class QOpenGLBuffer;
class QOpenGLVertexArrayObject;
class QOpenGLShaderProgram;

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit MyOpenGLWidget(QWidget* parent = nullptr);

public slots:
    void ScaleUp();
    void ScaleDown();

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

private slots:
    void CleanUp();

private:
    static constexpr auto SCALE_FACTOR_PER_ONCE = 1.15f;

    QOpenGLShaderProgram* ShaderProgram;
    QOpenGLBuffer* Buffer;
    QOpenGLVertexArrayObject* VertexArray;
    Pyramid Pyramid8Faces;
    float ScaleFactor;
};

#endif  // CG_LAB_MYOPENGLWIDGET_HPP_
