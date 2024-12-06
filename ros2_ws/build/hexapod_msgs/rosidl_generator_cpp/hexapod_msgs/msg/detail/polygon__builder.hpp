// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hexapod_msgs:msg/Polygon.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hexapod_msgs/msg/polygon.hpp"


#ifndef HEXAPOD_MSGS__MSG__DETAIL__POLYGON__BUILDER_HPP_
#define HEXAPOD_MSGS__MSG__DETAIL__POLYGON__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hexapod_msgs/msg/detail/polygon__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hexapod_msgs
{

namespace msg
{

namespace builder
{

class Init_Polygon_vertices
{
public:
  Init_Polygon_vertices()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::hexapod_msgs::msg::Polygon vertices(::hexapod_msgs::msg::Polygon::_vertices_type arg)
  {
    msg_.vertices = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hexapod_msgs::msg::Polygon msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hexapod_msgs::msg::Polygon>()
{
  return hexapod_msgs::msg::builder::Init_Polygon_vertices();
}

}  // namespace hexapod_msgs

#endif  // HEXAPOD_MSGS__MSG__DETAIL__POLYGON__BUILDER_HPP_
