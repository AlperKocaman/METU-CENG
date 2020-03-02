cmake_minimum_required(VERSION 3.9)
project(HW2)

set(CMAKE_CXX_STANDARD 11)

add_executable(HW2
        Camera.cpp
        Camera.h
        Color.cpp
        Color.h
        Helpers.cpp
        Helpers.h
        Main.cpp
        Matrix4.cpp
        Matrix4.h
        Model.cpp
        Model.h
        Rotation.cpp
        Rotation.h
        Scaling.cpp
        Scaling.h
        Scene.cpp
        Scene.h
        tinyxml2.cpp
        tinyxml2.h
        Translation.cpp
        Translation.h
        Triangle.cpp
        Triangle.h
        Vec3.cpp
        Vec3.h
        Vec4.cpp
        Vec4.h)
