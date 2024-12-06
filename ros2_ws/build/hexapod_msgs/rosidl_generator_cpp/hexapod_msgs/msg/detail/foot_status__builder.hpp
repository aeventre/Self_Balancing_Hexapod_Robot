// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hexapod_msgs:msg/FootStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hexapod_msgs/msg/foot_status.hpp"


#ifndef HEXAPOD_MSGS__MSG__DETAIL__FOOT_STATUS__BUILDER_HPP_
#define HEXAPOD_MSGS__MSG__DETAIL__FOOT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hexapod_msgs/msg/detail/foot_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hexapod_msgs
{

namespace msg
{

namespace builder
{

class Init_FootStatus_data
{
public:
  Init_FootStatus_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::hexapod_msgs::msg::FootStatus data(::hexapod_msgs::msg::FootStatus::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hexapod_msgs::msg::FootStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hexapod_msgs::msg::FootStatus>()
{
  return hexapod_msgs::msg::builder::Init_FootStatus_data();
}

}  // namespace hexapod_msgs

#endif  // HEXAPOD_MSGS__MSG__DETAIL__FOOT_STATUS__BUILDER_HPP_
