cmake_minimum_required(VERSION 3.8)
project(smartros_core_cpp)

add_compile_options(-Wall -Wextra -Wpedantic)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# ===== LIBSERIAL (system) =====
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBSERIAL REQUIRED libserial)

include_directories(${LIBSERIAL_INCLUDE_DIRS})
link_directories(${LIBSERIAL_LIBRARY_DIRS})

# ===== WATCHDOG =====
add_executable(watchdog_node src/watchdog_node.cpp)
ament_target_dependencies(watchdog_node rclcpp std_msgs)
install(TARGETS watchdog_node DESTINATION lib/${PROJECT_NAME})

# ===== SELF HEALING =====
add_executable(self_healing_node src/self_healing_node.cpp)
ament_target_dependencies(self_healing_node rclcpp std_msgs)
install(TARGETS self_healing_node DESTINATION lib/${PROJECT_NAME})

# ===== ESP32 BRIDGE =====
add_executable(esp32_bridge_node src/esp32_bridge_node.cpp)
ament_target_dependencies(esp32_bridge_node rclcpp std_msgs)
target_link_libraries(esp32_bridge_node ${LIBSERIAL_LIBRARIES})
install(TARGETS esp32_bridge_node DESTINATION lib/${PROJECT_NAME})

ament_package()
