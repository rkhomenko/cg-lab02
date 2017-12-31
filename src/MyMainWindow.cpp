// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#include <MyMainWindow.hpp>
#include <MyOpenGLWidget.hpp>

#include <QGroupBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QSurfaceFormat>
#include <QVBoxLayout>

MyMainWindow::MyMainWindow(QWidget* parent) : QMainWindow(parent) {
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);

    OpenGLWidget = new MyOpenGLWidget(this);
    OpenGLWidget->setFormat(format);
    OpenGLWidget->setMinimumSize(DEFAULT_SIZE);

    setCentralWidget(CreateCentralWidget());
}

QWidget* MyMainWindow::CreateCentralWidget() {
    const auto fixedSizePolicy =
        QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto centralWidget = new QWidget;
    auto mainLayout = new QVBoxLayout;
    auto toolLineLayout = new QHBoxLayout;

    auto scaleDownButton = new QPushButton;
    auto scaleUpButton = new QPushButton;
    scaleDownButton->setIcon(QIcon(QPixmap(":/icons/scaleDownIcon.svg")));
    scaleUpButton->setIcon(QIcon(QPixmap(":/icons/scaleUpIcon.svg")));
    scaleDownButton->setSizePolicy(fixedSizePolicy);
    scaleUpButton->setSizePolicy(fixedSizePolicy);
    toolLineLayout->addWidget(scaleDownButton);
    toolLineLayout->addWidget(scaleUpButton);

    connect(scaleDownButton, &QPushButton::clicked, OpenGLWidget,
            &MyOpenGLWidget::ScaleDown);
    connect(scaleUpButton, &QPushButton::clicked, OpenGLWidget,
            &MyOpenGLWidget::ScaleUp);

    auto label = new QLabel(
        "Computer grapics lab 2\n"
        "Variant 20: octagonal truncated pyramid\n"
        "Made by Roman Khomenko (8O-308)");
    label->setSizePolicy(fixedSizePolicy);
    toolLineLayout->addWidget(label);

    toolLineLayout->addStretch();
    mainLayout->addLayout(toolLineLayout);
    mainLayout->addWidget(OpenGLWidget);

    auto sizePolicy = QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    centralWidget->setSizePolicy(sizePolicy);
    centralWidget->setLayout(mainLayout);

    return centralWidget;
}

MyMainWindow::~MyMainWindow() {
    delete OpenGLWidget;
}
