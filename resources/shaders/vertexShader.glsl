// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#version 330
attribute highp vec4 position;

uniform highp mat4x4 shiftMatrix;
uniform highp mat4x4 scaleMatrix;
uniform highp mat4x4 rotateOXMatrix;
uniform highp mat4x4 rotateOYMatrix;
uniform highp mat4x4 rotateOZMatrix;
uniform highp mat4x4 projectionMatrix;
uniform highp mat4x4 moveToXYMatrix;

void main() {
    mat4x4 rotateMatrix = rotateOXMatrix *
                          rotateOYMatrix *
                          rotateOZMatrix;
    gl_Position = position *
                  shiftMatrix *
                  rotateMatrix *
                  projectionMatrix *
                  moveToXYMatrix *
                  scaleMatrix;
}
