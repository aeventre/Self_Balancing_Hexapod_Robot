// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hexapod_msgs:msg/JointAngles.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hexapod_msgs/msg/joint_angles.h"


#ifndef HEXAPOD_MSGS__MSG__DETAIL__JOINT_ANGLES__STRUCT_H_
#define HEXAPOD_MSGS__MSG__DETAIL__JOINT_ANGLES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'angles'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/JointAngles in the package hexapod_msgs.
typedef struct hexapod_msgs__msg__JointAngles
{
  /// Array of joint angles for all servos
  rosidl_runtime_c__double__Sequence angles;
} hexapod_msgs__msg__JointAngles;

// Struct for a sequence of hexapod_msgs__msg__JointAngles.
typedef struct hexapod_msgs__msg__JointAngles__Sequence
{
  hexapod_msgs__msg__JointAngles * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__msg__JointAngles__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HEXAPOD_MSGS__MSG__DETAIL__JOINT_ANGLES__STRUCT_H_
