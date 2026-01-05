#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std::chrono_literals;

class WatchdogNode : public rclcpp::Node {
public:
    WatchdogNode() : Node("watchdog_node") {
        status_pub_ = this->create_publisher<std_msgs::msg::String>("/watchdog_status", 10);
        timer_ = this->create_wall_timer(1000ms, std::bind(&WatchdogNode::monitor_system, this));
    }

private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr status_pub_;
    rclcpp::TimerBase::SharedPtr timer_;

    void monitor_system() {
        // Simuler lecture CPU/mémoire (remplacer par code réel si souhaité)
        int cpu_usage = rand() % 100;
        int mem_usage = rand() % 100;

        std_msgs::msg::String msg;
        msg.data = "CPU: " + std::to_string(cpu_usage) + "% | MEM: " + std::to_string(mem_usage) + "%";
        status_pub_->publish(msg);

        RCLCPP_INFO(this->get_logger(), "%s", msg.data.c_str());

        // Déclencher auto-healing si seuil dépassé (exemple)
        if(cpu_usage > 90 || mem_usage > 90) {
            RCLCPP_WARN(this->get_logger(), "Threshold exceeded! Trigger self-healing.");
        }
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<WatchdogNode>());
    rclcpp::shutdown();
    return 0;
}
