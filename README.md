# ROS2-Suspension
----ROS2
          ┌────────────┐
          │  上位アプリ │  Nav2 / FSM
          └─────▲──────┘
                │ /cmd_vel
────MCU──────────┼───────────────
    (non-RT)    ▼
          ┌────────────┐  rclcpp::Node
          │  BaseDriver │  ★独自に実装
          └─────▲──────┘
    USB/CAN      │  1 kHz

   (RT)          ▼
          ┌────────────┐
          │  Motor MCU  │  PID + 電流制限
          └────────────┘
