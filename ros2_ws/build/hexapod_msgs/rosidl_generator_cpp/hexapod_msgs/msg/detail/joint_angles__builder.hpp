// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hexapod_msgs:msg/JointAngles.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hexapod_msgs/msg/joint_angles.hpp"


#ifndef HEXAPOD_MSGS__MSG__DETAIL__JOINT_ANGLES__BUILDER_HPP_
#define HEXAPOD_MSGS__MSG__DETAIL__JOINT_ANGLES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hexapod_msgs/msg/detail/joint_angles__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hexapod_msgs
{

namespace msg
{

namespace builder
{

class Init_JointAngles_angles
{
public:
  Init_JointAngles_angles()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::hexapod_msgs::msg::JointAngles angles(::hexapod_msgs::msg::JointAngles::_angles_type arg)
  {
    msg_.angles = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hexapod_msgs::msg::JointAngles msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hexapod_msgs::msg::JointAngles>()
{
  return hexapod_msgs::msg::builder::Init_JointAngles_angles();
}

}  // namespace hexapod_msgs

#endif  // HEXAPOD_MSGS__MSG__DETAIL__JOINT_ANGLES__BUILDER_HPP_
