// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hexapod_msgs:msg/LegPositions.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hexapod_msgs/msg/leg_positions.h"


#ifndef HEXAPOD_MSGS__MSG__DETAIL__LEG_POSITIONS__STRUCT_H_
#define HEXAPOD_MSGS__MSG__DETAIL__LEG_POSITIONS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'positions'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/LegPositions in the package hexapod_msgs.
typedef struct hexapod_msgs__msg__LegPositions
{
  /// Array of leg positions
  geometry_msgs__msg__Point__Sequence positions;
} hexapod_msgs__msg__LegPositions;

// Struct for a sequence of hexapod_msgs__msg__LegPositions.
typedef struct hexapod_msgs__msg__LegPositions__Sequence
{
  hexapod_msgs__msg__LegPositions * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__msg__LegPositions__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HEXAPOD_MSGS__MSG__DETAIL__LEG_POSITIONS__STRUCT_H_
