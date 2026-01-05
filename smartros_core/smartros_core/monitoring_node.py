import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import psutil
import time

class MonitoringNode(Node):

    def __init__(self):
        super().__init__('monitoring_node')

        self.status_pub = self.create_publisher(String, '/system_status', 10)
        self.alert_pub = self.create_publisher(String, '/system_alert', 10)

        self.timer = self.create_timer(2.0, self.monitor_system)

        self.get_logger().info("Monitoring Node started (CPU + TEMP + RAM)")

    def get_cpu_temp(self):
        try:
            temps = psutil.sensors_temperatures()
            if 'cpu_thermal' in temps:
                return temps['cpu_thermal'][0].current
        except:
            pass
        return -1.0

    def monitor_system(self):
        cpu = psutil.cpu_percent()
        ram = psutil.virtual_memory().percent
        temp = self.get_cpu_temp()

        status = f"CPU: {cpu}% | RAM: {ram}% | TEMP: {temp}C"
        self.status_pub.publish(String(data=status))

        if cpu > 80:
            self.alert_pub.publish(String(data="ALERT: High CPU usage"))

        if ram > 80:
            self.alert_pub.publish(String(data="ALERT: High RAM usage"))

        if temp > 70:
            self.alert_pub.publish(String(data="ALERT: High CPU temperature"))

def main(args=None):
    rclpy.init(args=args)
    node = MonitoringNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
