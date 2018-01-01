// Computer graphic lab 2
// Variant 20
// Copyright © 2017-2018 Roman Khomenko (8O-308)
// All rights reserved

#version 330
attribute highp vec4 position;

uniform highp mat4x4 scaleMatrix;
uniform highp mat4x4 rotateOXMatrix;
uniform highp mat4x4 rotateOYMatrix;
uniform highp mat4x4 rotateOZMatrix;

void main() {
    mat4x4 rotateMatrix = rotateOXMatrix * rotateOYMatrix * rotateOZMatrix;
    mat4x4 transformMatrix = rotateMatrix * scaleMatrix;
    gl_Position = position * transformMatrix;
}
