cmake_minimum_required(VERSION 3.28)
project(Processor)

find_package(SystemCLanguage CONFIG REQUIRED)
set(CMAKE_CXX_STANDARD 17)

add_executable(Processor
        main.cpp
        ALU.h
        Controller.h
        Controller.cpp
        Mux.h
        Register.h
        Register.cpp
        Adder.h
        Ffc.h
        Ffc.cpp
        RegisterFile.h
        Stack.h
        Datapath.h
        Datapath.cpp
        Datapath.cpp
        Processor.h
        DataMemory.h
        InstructionMemory.h
        TopLevel.h
        TopLevel.cpp
)
target_link_libraries(Processor SystemC::systemc)

add_executable(ALU_testbench
        ALU_testbench.cpp
        ALU.h
)
target_link_libraries(ALU_testbench SystemC::systemc)

add_executable(Adder_testbench
        Adder_testbench.cpp
        Adder.h
)
target_link_libraries(Adder_testbench SystemC::systemc)

add_executable(Mux_testbench
        Mux_testbench.cpp
        Mux.h
)
target_link_libraries(Mux_testbench SystemC::systemc)

add_executable(Ffc_testbench
        Ffc.cpp
        Ffc.h
        Ffc_testbench.cpp
)
target_link_libraries(Ffc_testbench SystemC::systemc)

add_executable(Register_testbench
        Register_testbench.cpp
        Register.h
)

target_link_libraries(Register_testbench SystemC::systemc)

add_executable(RegisterFile_testbench
        RegisterFile_testbench.cpp
        RegisterFile.h
)
target_link_libraries(RegisterFile_testbench SystemC::systemc)

add_executable(Stack_testbench
        Stack_testbench.cpp
        Stack.h
)
target_link_libraries(Stack_testbench SystemC::systemc)

add_executable(InstructionMemory_testbench
        InstructionMemory_testbench.cpp
        InstructionMemory.h
)
target_link_libraries(InstructionMemory_testbench SystemC::systemc)

add_executable(DataMemory_testbench
        DataMemory_testbench.cpp
        DataMemory.h
)
target_link_libraries(DataMemory_testbench SystemC::systemc)

