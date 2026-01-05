#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class SelfHealingNode : public rclcpp::Node {
public:
    SelfHealingNode() : Node("self_healing_node") {
        alert_sub_ = this->create_subscription<std_msgs::msg::String>(
            "/system_alert", 10, std::bind(&SelfHealingNode::handle_alert, this, std::placeholders::_1));

        status_pub_ = this->create_publisher<std_msgs::msg::String>("/system_status", 10);
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr alert_sub_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr status_pub_;

    void handle_alert(const std_msgs::msg::String::SharedPtr msg) {
        RCLCPP_WARN(this->get_logger(), "Alert received: %s", msg->data.c_str());

        // Exemple: décider de relancer une tâche ou passer en mode dégradé
        std::string action = decide_action(msg->data);
        publish_status(action);
    }

    std::string decide_action(const std::string &alert) {
        // Logique simple: selon le message d'alerte
        if(alert.find("CRITICAL") != std::string::npos) {
            return "MODE_DEGRADE";
        }
        return "RESTART_TASK";
    }

    void publish_status(const std::string &status) {
        std_msgs::msg::String msg;
        msg.data = status;
        status_pub_->publish(msg);
        RCLCPP_INFO(this->get_logger(), "Action taken: %s", status.c_str());
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SelfHealingNode>());
    rclcpp::shutdown();
    return 0;
}
