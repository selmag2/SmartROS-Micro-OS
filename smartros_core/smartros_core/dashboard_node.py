#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import psutil
import subprocess
import json
import time


class DashboardNode(Node):

    def __init__(self):
        super().__init__('dashboard_node')

        self.publisher_ = self.create_publisher(
            String,
            '/system_dashboard',
            10
        )

        self.timer = self.create_timer(2.0, self.publish_dashboard)
        self.get_logger().info('📊 Dashboard node started')


    def get_cpu_temperature(self):
        try:
            temp = subprocess.check_output(
                ["vcgencmd", "measure_temp"]
            ).decode()
            return float(temp.replace("temp=", "").replace("'C\n", ""))
        except Exception:
            return -1.0


    def publish_dashboard(self):
        cpu = psutil.cpu_percent()
        memory = psutil.virtual_memory().percent
        temperature = self.get_cpu_temperature()

        data = {
            "cpu_usage": cpu,
            "memory_usage": memory,
            "cpu_temperature": temperature,
            "timestamp": time.time()
        }

        msg = String()
        msg.data = json.dumps(data)

        self.publisher_.publish(msg)

        self.get_logger().info(
            f"CPU: {cpu}% | RAM: {memory}% | TEMP: {temperature}°C"
        )


def main(args=None):
    rclpy.init(args=args)

    node = DashboardNode()
    rclpy.spin(node)

    node.destroy_node()
    rclpy.shutdown()
