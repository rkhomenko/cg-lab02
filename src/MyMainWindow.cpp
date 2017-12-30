// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#include <MyMainWindow.hpp>
#include <MyOpenGLWidget.hpp>

#include <QSurfaceFormat>

MyMainWindow::MyMainWindow(QWidget* parent) : QMainWindow(parent) {
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);

    OpenGLWidget = new MyOpenGLWidget(this);
    OpenGLWidget->setFormat(format);

    setMinimumSize(MINIMUM_SIZE);
    resize(DEFAULT_SIZE);
    setCentralWidget(OpenGLWidget);
}

MyMainWindow::~MyMainWindow() {
    delete OpenGLWidget;
}
