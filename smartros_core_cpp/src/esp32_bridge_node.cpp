#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/u_int32.hpp>
#include <std_msgs/msg/int32.hpp>

#include <libserial/SerialPort.h>

#include <chrono>
#include <string>
#include <sstream>

using namespace std::chrono_literals;

class ESP32BridgeNode : public rclcpp::Node
{
public:
  ESP32BridgeNode() : Node("esp32_bridge_node")
  {
    RCLCPP_INFO(get_logger(), "ESP32 Bridge Node started");

    /* Publishers */
    motion_pub_    = create_publisher<std_msgs::msg::Bool>("/esp32/motion", 10);
    heartbeat_pub_ = create_publisher<std_msgs::msg::Bool>("/esp32/heartbeat", 10);
    free_heap_pub_ = create_publisher<std_msgs::msg::UInt32>("/esp32/free_heap", 10);
    uptime_pub_    = create_publisher<std_msgs::msg::UInt32>("/esp32/uptime", 10);
    rssi_pub_      = create_publisher<std_msgs::msg::Int32>("/esp32/rssi", 10);
    status_pub_    = create_publisher<std_msgs::msg::String>("/esp32/status", 10);

    connectSerial();

    last_rx_time_ = now();

    timer_ = create_wall_timer(
        100ms, std::bind(&ESP32BridgeNode::readSerial, this));
  }

private:
  /* ================= SERIAL ================= */

  void connectSerial()
  {
    try
    {
      serial_.Open("/dev/ttyUSB1");
      serial_.SetBaudRate(LibSerial::BaudRate::BAUD_115200);
      serial_.SetCharacterSize(LibSerial::CharacterSize::CHAR_SIZE_8);
      serial_.SetStopBits(LibSerial::StopBits::STOP_BITS_1);
      serial_.SetParity(LibSerial::Parity::PARITY_NONE);
      serial_.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);

      RCLCPP_INFO(get_logger(), "ESP32 connected via serial");
    }
    catch (...)
    {
      RCLCPP_ERROR(get_logger(), "Failed to open serial port");
    }
  }

  /* ================= MAIN LOOP ================= */

  void readSerial()
  {
    if (!serial_.IsOpen())
    {
      reconnectIfNeeded();
      return;
    }

    try
    {
      std::string line;
      serial_.ReadLine(line, '\n', 100);

      if (!line.empty())
      {
        parseJSON(line);
        last_rx_time_ = now();
      }
      else
      {
        checkTimeout();
      }
    }
    catch (const LibSerial::ReadTimeout &)
    {
      checkTimeout();
    }
    catch (...)
    {
      RCLCPP_WARN(get_logger(), "Serial error, reconnecting...");
      reconnectIfNeeded();
    }
  }

  /* ================= JSON PARSING ================= */

  void parseJSON(const std::string &json)
  {
    bool motion = extractBool(json, "motion");
    bool alive  = extractBool(json, "alive");

    uint32_t free_heap = extractUInt(json, "free_heap");
    uint32_t uptime    = extractUInt(json, "uptime");
    int32_t rssi       = extractInt(json, "rssi");

    publishBool(motion_pub_, motion);
    publishBool(heartbeat_pub_, alive);

    publishUInt(free_heap_pub_, free_heap);
    publishUInt(uptime_pub_, uptime);
    publishInt(rssi_pub_, rssi);

    std_msgs::msg::String status_msg;
    status_msg.data = json;
    status_pub_->publish(status_msg);

    /* Auto-healing condition */
    if (free_heap > 0 && free_heap < 20000)
    {
      RCLCPP_WARN(get_logger(), "ESP32 LOW MEMORY detected!");
    }
  }

  /* ================= AUTO-HEALING ================= */
  bool esp_timeout_reported_ = false;

  void checkTimeout()
{
  double dt = (now() - last_rx_time_).seconds();
  if (dt > 2.0 && !esp_timeout_reported_)
  {
    RCLCPP_ERROR(get_logger(), "ESP32 not responding (timeout)");
    esp_timeout_reported_ = true;
  }
  else if (dt <= 2.0)
  {
    esp_timeout_reported_ = false;
  }
}

  void reconnectIfNeeded()
  {
    if (!serial_.IsOpen())
    {
      RCLCPP_WARN(get_logger(), "Reconnecting to ESP32...");
      connectSerial();
    }
  }

  /* ================= HELPERS ================= */

  bool extractBool(const std::string &s, const std::string &key)
  {
    auto pos = s.find(key);
    if (pos == std::string::npos) return false;
    return s.substr(pos).find("1") != std::string::npos;
  }

  uint32_t extractUInt(const std::string &s, const std::string &key)
  {
    auto pos = s.find(key);
    if (pos == std::string::npos) return 0;
    return std::stoul(s.substr(s.find(":", pos) + 1));
  }

  int32_t extractInt(const std::string &s, const std::string &key)
  {
    auto pos = s.find(key);
    if (pos == std::string::npos) return 0;
    return std::stoi(s.substr(s.find(":", pos) + 1));
  }

  void publishBool(const rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr &pub, bool v)
  {
    std_msgs::msg::Bool msg;
    msg.data = v;
    pub->publish(msg);
  }

  void publishUInt(const rclcpp::Publisher<std_msgs::msg::UInt32>::SharedPtr &pub, uint32_t v)
  {
    std_msgs::msg::UInt32 msg;
    msg.data = v;
    pub->publish(msg);
  }

  void publishInt(const rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr &pub, int32_t v)
  {
    std_msgs::msg::Int32 msg;
    msg.data = v;
    pub->publish(msg);
  }

  /* ================= MEMBERS ================= */

  LibSerial::SerialPort serial_;
  rclcpp::Time last_rx_time_;

  rclcpp::TimerBase::SharedPtr timer_;

  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr motion_pub_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr heartbeat_pub_;
  rclcpp::Publisher<std_msgs::msg::UInt32>::SharedPtr free_heap_pub_;
  rclcpp::Publisher<std_msgs::msg::UInt32>::SharedPtr uptime_pub_;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr rssi_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr status_pub_;
};

/* ================= MAIN ================= */

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ESP32BridgeNode>());
  rclcpp::shutdown();
  return 0;
}
