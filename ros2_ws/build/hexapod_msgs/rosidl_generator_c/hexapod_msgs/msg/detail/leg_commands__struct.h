// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hexapod_msgs:msg/LegCommands.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hexapod_msgs/msg/leg_commands.h"


#ifndef HEXAPOD_MSGS__MSG__DETAIL__LEG_COMMANDS__STRUCT_H_
#define HEXAPOD_MSGS__MSG__DETAIL__LEG_COMMANDS__STRUCT_H_

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

/// Struct defined in msg/LegCommands in the package hexapod_msgs.
typedef struct hexapod_msgs__msg__LegCommands
{
  /// Desired Cartesian positions of the feet
  geometry_msgs__msg__Point__Sequence positions;
} hexapod_msgs__msg__LegCommands;

// Struct for a sequence of hexapod_msgs__msg__LegCommands.
typedef struct hexapod_msgs__msg__LegCommands__Sequence
{
  hexapod_msgs__msg__LegCommands * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__msg__LegCommands__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HEXAPOD_MSGS__MSG__DETAIL__LEG_COMMANDS__STRUCT_H_
