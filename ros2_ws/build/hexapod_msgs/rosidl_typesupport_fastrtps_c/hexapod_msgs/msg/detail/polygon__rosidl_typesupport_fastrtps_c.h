// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from hexapod_msgs:msg/Polygon.idl
// generated code does not contain a copyright notice
#ifndef HEXAPOD_MSGS__MSG__DETAIL__POLYGON__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define HEXAPOD_MSGS__MSG__DETAIL__POLYGON__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "hexapod_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "hexapod_msgs/msg/detail/polygon__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
bool cdr_serialize_hexapod_msgs__msg__Polygon(
  const hexapod_msgs__msg__Polygon * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
bool cdr_deserialize_hexapod_msgs__msg__Polygon(
  eprosima::fastcdr::Cdr &,
  hexapod_msgs__msg__Polygon * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
size_t get_serialized_size_hexapod_msgs__msg__Polygon(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
size_t max_serialized_size_hexapod_msgs__msg__Polygon(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
bool cdr_serialize_key_hexapod_msgs__msg__Polygon(
  const hexapod_msgs__msg__Polygon * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
size_t get_serialized_size_key_hexapod_msgs__msg__Polygon(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
size_t max_serialized_size_key_hexapod_msgs__msg__Polygon(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hexapod_msgs, msg, Polygon)();

#ifdef __cplusplus
}
#endif

#endif  // HEXAPOD_MSGS__MSG__DETAIL__POLYGON__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
