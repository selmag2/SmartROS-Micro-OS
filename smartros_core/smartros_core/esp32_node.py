import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import serial

class ESP32Node(Node):
    def __init__(self):
        super().__init__('esp32_node')
        self.publisher_ = self.create_publisher(String, '/esp32_data', 10)
        self.ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
        self.timer = self.create_timer(2.0, self.timer_callback)  # toutes les 2s

    def timer_callback(self):
        if self.ser.in_waiting > 0:
            line = self.ser.readline().decode('utf-8').strip()
            # Exemple : "24.5,60.0"
            msg = String()
            msg.data = line
            self.publisher_.publish(msg)
            self.get_logger().info(f'Published: {msg.data}')
        else:
            self.get_logger().info("Waiting for data...")
def main(args=None):
    rclpy.init(args=args)
    node = ESP32Node()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

