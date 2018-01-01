// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#ifndef CG_LAB_MYMAINWINDOW_HPP_
#define CG_LAB_MYMAINWINDOW_HPP_

#include <QMainWindow>

class MyOpenGLWidget;
class MyControlWidget;

class MyMainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MyMainWindow(QWidget* parent = nullptr);
    ~MyMainWindow();

    static constexpr auto DEFAULT_SIZE = QSize{400, 400};
    static constexpr auto MINIMUM_SIZE = QSize{10, 10};
    static constexpr auto VARIANT_DESCRIPTION =
        "Computer grapics lab 2\n"
        "Variant 20: octagonal truncated pyramid\n"
        "Made by Roman Khomenko (8O-308)";

private:
    QWidget* CreateCentralWidget();

    MyOpenGLWidget* OpenGLWidget;
    MyControlWidget* ControlWidget;
};

#endif  // CG_LAB_MYMAINWINDOW_HPP_
