// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from hexapod_msgs:msg/JointAngles.idl
// generated code does not contain a copyright notice

#include "hexapod_msgs/msg/detail/joint_angles__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_hexapod_msgs
const rosidl_type_hash_t *
hexapod_msgs__msg__JointAngles__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xca, 0xd3, 0xd2, 0x3d, 0xd1, 0xa4, 0xef, 0x20,
      0xd3, 0x1f, 0xe3, 0x18, 0x2c, 0xbe, 0xf7, 0x98,
      0x5b, 0x33, 0xb9, 0x35, 0xd0, 0x8d, 0x86, 0x44,
      0xda, 0x0f, 0xa7, 0xae, 0x07, 0x04, 0x38, 0xf3,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char hexapod_msgs__msg__JointAngles__TYPE_NAME[] = "hexapod_msgs/msg/JointAngles";

// Define type names, field names, and default values
static char hexapod_msgs__msg__JointAngles__FIELD_NAME__angles[] = "angles";

static rosidl_runtime_c__type_description__Field hexapod_msgs__msg__JointAngles__FIELDS[] = {
  {
    {hexapod_msgs__msg__JointAngles__FIELD_NAME__angles, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
hexapod_msgs__msg__JointAngles__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {hexapod_msgs__msg__JointAngles__TYPE_NAME, 28, 28},
      {hexapod_msgs__msg__JointAngles__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float64[] angles  # Array of joint angles for all servos";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
hexapod_msgs__msg__JointAngles__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {hexapod_msgs__msg__JointAngles__TYPE_NAME, 28, 28},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 57, 57},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
hexapod_msgs__msg__JointAngles__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *hexapod_msgs__msg__JointAngles__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
