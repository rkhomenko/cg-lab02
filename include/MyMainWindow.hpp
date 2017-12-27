// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#ifndef CG_LAB_MYMAINWINDOW_HPP_
#define CG_LAB_MYMAINWINDOW_HPP_

#include <QMainWindow>

class MyOpenGLWidget;

class MyMainWindow : public QMainWindow {
    Q_OBJECT

public:
    MyMainWindow(QWidget* parent = nullptr);
    ~MyMainWindow();

private:
    MyOpenGLWidget* OpenGLWidget;
};

#endif  // CG_LAB_MYMAINWINDOW_HPP_
