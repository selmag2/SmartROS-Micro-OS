from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # Watchdog C++ node
        Node(
            package='smartros_core_cpp',
            executable='watchdog_node',
            name='watchdog_node'
        ),
        # Self-healing C++ node
        Node(
            package='smartros_core_cpp',
            executable='self_healing_node',
            name='self_healing_node'
        ),
        # Task manager Python node
        Node(
            package='smartros_core',
            executable='task_manager_node',
            name='task_manager_node'
        ),
        # Monitoring Python node
        Node(
            package='smartros_core',
            executable='monitoring_node',
            name='monitoring_node'
        ),
       Node(
           package='smartros_core',      # <-- package Python existant
           executable='dashboard_node',   # <-- nouveau node
           name='dashboard_node'
       ),
    ])
