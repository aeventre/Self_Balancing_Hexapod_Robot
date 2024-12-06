// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from hexapod_msgs:msg/JointAngles.idl
// generated code does not contain a copyright notice
#ifndef HEXAPOD_MSGS__MSG__DETAIL__JOINT_ANGLES__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define HEXAPOD_MSGS__MSG__DETAIL__JOINT_ANGLES__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "hexapod_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "hexapod_msgs/msg/detail/joint_angles__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
bool cdr_serialize_hexapod_msgs__msg__JointAngles(
  const hexapod_msgs__msg__JointAngles * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
bool cdr_deserialize_hexapod_msgs__msg__JointAngles(
  eprosima::fastcdr::Cdr &,
  hexapod_msgs__msg__JointAngles * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
size_t get_serialized_size_hexapod_msgs__msg__JointAngles(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
size_t max_serialized_size_hexapod_msgs__msg__JointAngles(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
bool cdr_serialize_key_hexapod_msgs__msg__JointAngles(
  const hexapod_msgs__msg__JointAngles * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
size_t get_serialized_size_key_hexapod_msgs__msg__JointAngles(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
size_t max_serialized_size_key_hexapod_msgs__msg__JointAngles(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hexapod_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hexapod_msgs, msg, JointAngles)();

#ifdef __cplusplus
}
#endif

#endif  // HEXAPOD_MSGS__MSG__DETAIL__JOINT_ANGLES__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
