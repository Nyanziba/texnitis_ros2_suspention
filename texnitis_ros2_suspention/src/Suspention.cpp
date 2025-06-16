#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <geometry_msgs/msg/twist.hpp>

class SuspentionNode : public rclcpp::Node
{
public:
  SuspentionNode() : Node("suspention_node")
  {
    // パブリッシャーの設定
    odom_publisher_ = this->create_publisher<nav_msgs::msg::Odometry>(
      "odom", 10);

    // サブスクライバーの設定
    joy_subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
      "joy", 10,
      std::bind(&SuspentionNode::joy_callback, this, std::placeholders::_1));

    cmd_vel_subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
      "cmd_vel", 10,
      std::bind(&SuspentionNode::cmd_vel_callback, this, std::placeholders::_1));

    // タイマーの設定（10Hz）
    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(100),
      std::bind(&SuspentionNode::timer_callback, this));

    RCLCPP_INFO(this->get_logger(), "Suspention node has been initialized");
  }

private:
  void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
  {
    // ジョイスティックのデータを処理
    RCLCPP_INFO(this->get_logger(), "Received joy message");
  }

  void cmd_vel_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
  {
    // 速度コマンドを処理
    RCLCPP_INFO(this->get_logger(), "Received cmd_vel message");
  }

  void timer_callback()
  {
    // オドメトリデータをパブリッシュ
    auto odom_msg = std::make_unique<nav_msgs::msg::Odometry>();
    odom_msg->header.stamp = this->now();
    odom_msg->header.frame_id = "odom";
    odom_msg->child_frame_id = "base_link";

    // ここにオドメトリの計算を実装
    // 現在はダミーデータを設定
    odom_msg->pose.pose.position.x = 0.0;
    odom_msg->pose.pose.position.y = 0.0;
    odom_msg->pose.pose.position.z = 0.0;
    odom_msg->pose.pose.orientation.w = 1.0;
    odom_msg->pose.pose.orientation.x = 0.0;
    odom_msg->pose.pose.orientation.y = 0.0;
    odom_msg->pose.pose.orientation.z = 0.0;

    odom_publisher_->publish(std::move(odom_msg));
  }

  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_publisher_;
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_subscription_;
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_subscription_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SuspentionNode>());
  rclcpp::shutdown();
  return 0;
}
