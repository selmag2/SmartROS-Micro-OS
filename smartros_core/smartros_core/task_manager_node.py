import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import time

class TaskManagerNode(Node):

    def __init__(self):
        super().__init__('task_manager_node')

        self.status_pub = self.create_publisher(
            String,
            '/task_manager_status',
            10
        )

        self.tasks = {
            "watchdog": True,
            "self_healing": True,
            "monitoring": True
        }

        self.timer = self.create_timer(2.0, self.publish_status)
        self.current_status = "RUNNING"

        self.get_logger().info("Task Manager started")

    def publish_status(self):
        active_tasks = sum(1 for t in self.tasks.values() if t)

        if active_tasks < len(self.tasks):
            self.current_status = "DEGRADED"
        else:
            self.current_status = "RUNNING"

        msg = String()
        msg.data = f"{self.current_status} ({active_tasks} tasks)"

        self.status_pub.publish(msg)
        self.get_logger().info(f"Task Manager Status: {msg.data}")


def main(args=None):
    rclpy.init(args=args)
    node = TaskManagerNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
