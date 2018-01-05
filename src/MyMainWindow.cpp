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
#include <QTabWidget>
#include <QVBoxLayout>

MyMainWindow::MyMainWindow(QWidget* parent) : QMainWindow(parent) {
    ControlWidget = new MyControlWidget;

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);

    OrthoOpenGLWidgets[0] =
        new MyOpenGLWidget(MyOpenGLWidget::ProjectionType::ORTHOGRAPHIC,
                           MyOpenGLWidget::ProjectionSurface::X);
    OrthoOpenGLWidgets[0]->setFormat(format);
    OrthoOpenGLWidgets[1] =
        new MyOpenGLWidget(MyOpenGLWidget::ProjectionType::ORTHOGRAPHIC,
                           MyOpenGLWidget::ProjectionSurface::Y);
    OrthoOpenGLWidgets[1]->setFormat(format);
    OrthoOpenGLWidgets[2] =
        new MyOpenGLWidget(MyOpenGLWidget::ProjectionType::ORTHOGRAPHIC,
                           MyOpenGLWidget::ProjectionSurface::Z);
    OrthoOpenGLWidgets[2]->setFormat(format);

    auto initWidget = [this](MyOpenGLWidget* openGLWidget) {
        // set connection for redraw on scale changed
        connect(ControlWidget, &MyControlWidget::ScaleUpSignal, openGLWidget,
                &MyOpenGLWidget::ScaleUpSlot);
        connect(ControlWidget, &MyControlWidget::ScaleDownSignal, openGLWidget,
                &MyOpenGLWidget::ScaleDownSlot);

        // set connection for redraw on angle changed
        connect(ControlWidget, &MyControlWidget::OXAngleChangedSignal,
                openGLWidget, &MyOpenGLWidget::OXAngleChangedSlot);
        connect(ControlWidget, &MyControlWidget::OYAngleChangedSignal,
                openGLWidget, &MyOpenGLWidget::OYAngleChangedSlot);
        connect(ControlWidget, &MyControlWidget::OZAngleChangedSignal,
                openGLWidget, &MyOpenGLWidget::OZAngleChangedSlot);
    };

    for (auto ptr : OrthoOpenGLWidgets) {
        initWidget(ptr);
    }

    setCentralWidget(CreateCentralWidget());
}

MyMainWindow::~MyMainWindow() {
    for (auto ptr : OrthoOpenGLWidgets) {
        delete ptr;
    }
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

    auto orthoWidgetsLayout = new QHBoxLayout;
    for (auto ptr : OrthoOpenGLWidgets) {
        orthoWidgetsLayout->addWidget(ptr);
    }

    auto isometricWidgetsLayout = new QHBoxLayout;
    // TODO: add isometric projection widgets

    auto createWidgetWithLayout = [](QLayout* layout) {
        auto widget = new QWidget;
        widget->setLayout(layout);
        return widget;
    };

    auto orthoTabWidget = createWidgetWithLayout(orthoWidgetsLayout);
    auto isometricTabWidget = createWidgetWithLayout(isometricWidgetsLayout);

    auto tabWidget = new QTabWidget;
    tabWidget->addTab(orthoTabWidget, "Orthogonal projections");
    tabWidget->addTab(isometricTabWidget, "Isometric projections");

    layout->addWidget(tabWidget);
    widget->setLayout(layout);

    return widget;
}
