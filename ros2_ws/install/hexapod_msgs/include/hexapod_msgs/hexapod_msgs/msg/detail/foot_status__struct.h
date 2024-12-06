// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hexapod_msgs:msg/FootStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hexapod_msgs/msg/foot_status.h"


#ifndef HEXAPOD_MSGS__MSG__DETAIL__FOOT_STATUS__STRUCT_H_
#define HEXAPOD_MSGS__MSG__DETAIL__FOOT_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'data'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/FootStatus in the package hexapod_msgs.
typedef struct hexapod_msgs__msg__FootStatus
{
  rosidl_runtime_c__boolean__Sequence data;
} hexapod_msgs__msg__FootStatus;

// Struct for a sequence of hexapod_msgs__msg__FootStatus.
typedef struct hexapod_msgs__msg__FootStatus__Sequence
{
  hexapod_msgs__msg__FootStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__msg__FootStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HEXAPOD_MSGS__MSG__DETAIL__FOOT_STATUS__STRUCT_H_
