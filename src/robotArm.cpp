// mylib.cpp
#include <iostream>

extern "C" void mechanical_arm_origin();

void mechanical_arm_origin() {
    std::cout << "C++ function mechanical_arm_origin is called." << std::endl;
    // 你可以在这里添加原始机械臂函数的实现
    // Angle_value_1: 0, Angle_value_2: -0.02, Angle_value_3: 0.96, Angle_value_4: 0, Angle_value_5: 0, Angle_value_6: 0
    // TH.j[0] = 0;
    // TH.j[1] = -0.02;
    // TH.j[2] = 0.96;
    // TH.j[3] = 0;
    // TH.j[4] = 0;
    // TH.j[5] = 0;
    // plan_move(2);
    // move_to_joint(2);
    // sleep(5);
    // show_value("TH.j: ", TH.j);
    // brake();
}

