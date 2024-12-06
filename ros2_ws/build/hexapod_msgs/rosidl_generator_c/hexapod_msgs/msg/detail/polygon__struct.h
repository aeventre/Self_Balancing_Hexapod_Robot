// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hexapod_msgs:msg/Polygon.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hexapod_msgs/msg/polygon.h"


#ifndef HEXAPOD_MSGS__MSG__DETAIL__POLYGON__STRUCT_H_
#define HEXAPOD_MSGS__MSG__DETAIL__POLYGON__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'vertices'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/Polygon in the package hexapod_msgs.
typedef struct hexapod_msgs__msg__Polygon
{
  /// Points forming the polygon
  geometry_msgs__msg__Point__Sequence vertices;
} hexapod_msgs__msg__Polygon;

// Struct for a sequence of hexapod_msgs__msg__Polygon.
typedef struct hexapod_msgs__msg__Polygon__Sequence
{
  hexapod_msgs__msg__Polygon * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__msg__Polygon__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HEXAPOD_MSGS__MSG__DETAIL__POLYGON__STRUCT_H_
