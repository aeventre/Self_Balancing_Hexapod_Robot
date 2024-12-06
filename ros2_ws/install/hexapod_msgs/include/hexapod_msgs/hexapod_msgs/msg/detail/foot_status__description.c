// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from hexapod_msgs:msg/FootStatus.idl
// generated code does not contain a copyright notice

#include "hexapod_msgs/msg/detail/foot_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_hexapod_msgs
const rosidl_type_hash_t *
hexapod_msgs__msg__FootStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xd2, 0x2c, 0x5f, 0x74, 0xe4, 0x1b, 0xe5, 0x66,
      0x93, 0xa6, 0x1e, 0xed, 0x32, 0xef, 0x1f, 0xf1,
      0x39, 0x1a, 0xe1, 0x89, 0xee, 0x9a, 0x90, 0x99,
      0x7e, 0xd8, 0xec, 0x9b, 0xfe, 0x12, 0x71, 0xb1,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char hexapod_msgs__msg__FootStatus__TYPE_NAME[] = "hexapod_msgs/msg/FootStatus";

// Define type names, field names, and default values
static char hexapod_msgs__msg__FootStatus__FIELD_NAME__data[] = "data";

static rosidl_runtime_c__type_description__Field hexapod_msgs__msg__FootStatus__FIELDS[] = {
  {
    {hexapod_msgs__msg__FootStatus__FIELD_NAME__data, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
hexapod_msgs__msg__FootStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {hexapod_msgs__msg__FootStatus__TYPE_NAME, 27, 27},
      {hexapod_msgs__msg__FootStatus__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "bool[] data";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
hexapod_msgs__msg__FootStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {hexapod_msgs__msg__FootStatus__TYPE_NAME, 27, 27},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 11, 11},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
hexapod_msgs__msg__FootStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *hexapod_msgs__msg__FootStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
