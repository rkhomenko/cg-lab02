// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#include <MyControlWidget.hpp>
#include <MyMainWindow.hpp>
#include <MyOpenGLWidget.hpp>

#include <vector>

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

    auto i = 0UL;
    for (auto projSurface : MyOpenGLWidget::GetProjectionSurfaces()) {
        OrthoOpenGLWidgets[i] = new MyOpenGLWidget(
            MyOpenGLWidget::ProjectionType::ORTHOGRAPHIC, projSurface);
        OrthoOpenGLWidgets[i]->setFormat(format);
        i++;
    }

    i = 0UL;
    for (auto isoProjType : MyOpenGLWidget::GetIsoProjTypes()) {
        IsoOpenGLWidgets[i] = new MyOpenGLWidget(
            MyOpenGLWidget::ProjectionType ::ISOMETRIC, isoProjType);
        IsoOpenGLWidgets[i]->setFormat(format);
        i++;
    }

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

    for (auto ptr : IsoOpenGLWidgets) {
        initWidget(ptr);
    }

    setCentralWidget(CreateCentralWidget());
}

MyMainWindow::~MyMainWindow() {
    for (auto ptr : OrthoOpenGLWidgets) {
        delete ptr;
    }
    for (auto ptr : IsoOpenGLWidgets) {
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

    auto createOpenGLWidgetWithLabel = [](QWidget* widget, const char* str) {
        const auto fixedSizePolicy =
            QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        auto vertLayout = new QVBoxLayout;
        auto label = new QLabel(str);
        label->setSizePolicy(fixedSizePolicy);

        vertLayout->addWidget(label);
        vertLayout->addWidget(widget);

        return vertLayout;
    };

    std::vector<const char*> projInfoArray = {"x = 0 (YZ)", "y = 0 (XZ)",
                                              "z = 0 (XY)"};

    auto orthoWidgetsLayout = new QHBoxLayout;
    auto i = 0U;
    for (auto projInfo : projInfoArray) {
        orthoWidgetsLayout->addLayout(
            createOpenGLWidgetWithLabel(OrthoOpenGLWidgets[i++], projInfo));
    }

    std::vector<const char*> isoProjInfoArray = {"- -", "- +", "+ -", "++"};
    auto isometricWidgetsLayout = new QHBoxLayout;
    i = 0;
    for (auto projInfo : isoProjInfoArray) {
        isometricWidgetsLayout->addLayout(
            createOpenGLWidgetWithLabel(IsoOpenGLWidgets[i++], projInfo));
    }

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
