from flask import Flask, render_template, jsonify
import threading
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import json

app = Flask(__name__, template_folder='templates')

# GLOBAL pour stocker les données ROS
dashboard_data = {}

class DashboardNode(Node):
    def __init__(self):
        super().__init__('dashboard_node')
        self.create_subscription(
            String,
            '/system_dashboard',
            self.listener_callback,
            10
        )

    def listener_callback(self, msg):
        global dashboard_data
        try:
            dashboard_data = json.loads(msg.data)
        except Exception as e:
            self.get_logger().error(f"Erreur JSON: {e}")

# Thread ROS 2
def ros_thread():
    rclpy.init()
    node = DashboardNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

threading.Thread(target=ros_thread, daemon=True).start()

# Routes Flask
@app.route('/')
def index():
    return render_template('dashboard.html')

@app.route('/data')
def data():
    return jsonify(dashboard_data)  # retourne le JSON actuel

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
