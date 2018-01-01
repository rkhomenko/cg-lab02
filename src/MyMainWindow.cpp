// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#include <MyControlWidget.hpp>
#include <MyMainWindow.hpp>
#include <MyOpenGLWidget.hpp>

#include <QHBoxLayout>
#include <QLabel>
#include <QSurfaceFormat>
#include <QVBoxLayout>

MyMainWindow::MyMainWindow(QWidget* parent) : QMainWindow(parent) {
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);

    OpenGLWidget = new MyOpenGLWidget;
    OpenGLWidget->setFormat(format);

    ControlWidget = new MyControlWidget;

    // set connection for redraw on scale changed
    connect(ControlWidget, &MyControlWidget::ScaleUpSignal, OpenGLWidget,
            &MyOpenGLWidget::ScaleUpSlot);
    connect(ControlWidget, &MyControlWidget::ScaleDownSignal, OpenGLWidget,
            &MyOpenGLWidget::ScaleDownSlot);

    // set connection for redraw on angle changed
    connect(ControlWidget, &MyControlWidget::OXAngleChangedSignal, OpenGLWidget,
            &MyOpenGLWidget::OXAngleChangedSlot);
    connect(ControlWidget, &MyControlWidget::OYAngleChangedSignal, OpenGLWidget,
            &MyOpenGLWidget::OYAngleChangedSlot);
    connect(ControlWidget, &MyControlWidget::OZAngleChangedSignal, OpenGLWidget,
            &MyOpenGLWidget::OZAngleChangedSlot);

    setCentralWidget(CreateCentralWidget());
}

MyMainWindow::~MyMainWindow() {
    delete OpenGLWidget;
    delete ControlWidget;
}

QWidget* MyMainWindow::CreateCentralWidget() {
    auto widget = new QWidget;
    auto layout = new QVBoxLayout;
    auto toolLayout = new QHBoxLayout;

    toolLayout->addWidget(ControlWidget);
    toolLayout->addWidget(new QLabel(VARIANT_DESCRIPTION));

    layout->setSizeConstraint(QLayout::SetNoConstraint);
    layout->addLayout(toolLayout);
    layout->addWidget(OpenGLWidget);

    widget->setLayout(layout);
    return widget;
}
