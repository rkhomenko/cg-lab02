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
    using FloatType = float;

    explicit MyOpenGLWidget(QWidget* parent = nullptr);

public slots:
    void ScaleUpSlot();
    void ScaleDownSlot();

    void OXAngleChangedSlot(FloatType angle);
    void OYAngleChangedSlot(FloatType angle);
    void OZAngleChangedSlot(FloatType angle);

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

private slots:
    void CleanUp();

private:
    static constexpr auto DEFAULT_SIZE = QSize(350, 350);

    static constexpr auto VERTEX_SHADER = ":/shaders/vertexShader.glsl";
    static constexpr auto FRAGMENT_SHADER = ":/shaders/fragmentShader.glsl";
    static constexpr auto POSITION = "position";
    static constexpr auto COLOR = "color";
    static constexpr auto SCALE_MATRIX = "scaleMatrix";
    static constexpr auto ROTATE_OX_MATRIX = "rotateOXMatrix";
    static constexpr auto ROTATE_OY_MATRIX = "rotateOYMatrix";
    static constexpr auto ROTATE_OZ_MATRIX = "rotateOZMatrix";

    static constexpr auto SCALE_FACTOR_PER_ONCE = 1.15f;

    template <class Func, class... Args>
    void OnMatrixRegenerated(const char* matrixName,
                             Func generate,
                             Args... args) {
        SetUniformMatrix(matrixName, std::invoke(generate, this, args...));
        repaint();
    }

    void UpdateScaleMatrix();
    void SetUniformMatrix(const char* uniformName, const QMatrix4x4& matrix);

    QMatrix4x4 GenerateScaleMatrix(int width, int height) const;
    QMatrix4x4 GenerateOXRotateMatrix() const;
    QMatrix4x4 GenerateOYRotateMatrix() const;
    QMatrix4x4 GenerateOZRotateMatrix() const;

    QOpenGLShaderProgram* ShaderProgram;
    QOpenGLBuffer* Buffer;
    QOpenGLVertexArrayObject* VertexArray;
    Pyramid Pyramid8Faces;
    FloatType ScaleFactor;
    FloatType AngleOX;
    FloatType AngleOY;
    FloatType AngleOZ;
};

#endif  // CG_LAB_MYOPENGLWIDGET_HPP_
