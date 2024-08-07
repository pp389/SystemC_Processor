cmake_minimum_required(VERSION 3.28)
project(untitled)

find_package(SystemCLanguage CONFIG REQUIRED)
set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp
        ALU.h
        ALU.cpp
        Controller.h
        Controller.cpp
        Mux.h
        Mux.cpp
        Register.h
        Register.cpp
        Adder.h
        Adder.cpp
        Ffc.h
        Ffc.cpp
        RegisterFile.h
        RegisterFile.cpp
        Stack.h
        Stack.cpp
        Datapath.h
        Datapath.cpp
        Datapath.cpp
        Processor.h
        DataMemory.h
        DataMemory.cpp
        InstructionMemory.h
        InstructionMemory.cpp
        TopLevel.h
        TopLevel.cpp
)
target_link_libraries(untitled SystemC::systemc)