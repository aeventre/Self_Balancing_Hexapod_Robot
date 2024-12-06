// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hexapod_msgs:msg/LegPositions.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hexapod_msgs/msg/leg_positions.hpp"


#ifndef HEXAPOD_MSGS__MSG__DETAIL__LEG_POSITIONS__BUILDER_HPP_
#define HEXAPOD_MSGS__MSG__DETAIL__LEG_POSITIONS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hexapod_msgs/msg/detail/leg_positions__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hexapod_msgs
{

namespace msg
{

namespace builder
{

class Init_LegPositions_positions
{
public:
  Init_LegPositions_positions()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::hexapod_msgs::msg::LegPositions positions(::hexapod_msgs::msg::LegPositions::_positions_type arg)
  {
    msg_.positions = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hexapod_msgs::msg::LegPositions msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hexapod_msgs::msg::LegPositions>()
{
  return hexapod_msgs::msg::builder::Init_LegPositions_positions();
}

}  // namespace hexapod_msgs

#endif  // HEXAPOD_MSGS__MSG__DETAIL__LEG_POSITIONS__BUILDER_HPP_
