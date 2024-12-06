// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from hexapod_msgs:msg/LegCommands.idl
// generated code does not contain a copyright notice

#include "hexapod_msgs/msg/detail/leg_commands__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_hexapod_msgs
const rosidl_type_hash_t *
hexapod_msgs__msg__LegCommands__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xa6, 0xab, 0x39, 0x43, 0x1f, 0x60, 0xe8, 0xee,
      0x2a, 0xf8, 0xc1, 0x1c, 0x75, 0xfc, 0xee, 0x49,
      0x34, 0xe0, 0xe3, 0x34, 0x14, 0xf6, 0x5e, 0xe0,
      0xac, 0xd9, 0xdf, 0x55, 0xb6, 0xfd, 0xa9, 0xde,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "geometry_msgs/msg/detail/point__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t geometry_msgs__msg__Point__EXPECTED_HASH = {1, {
    0x69, 0x63, 0x08, 0x48, 0x42, 0xa9, 0xb0, 0x44,
    0x94, 0xd6, 0xb2, 0x94, 0x1d, 0x11, 0x44, 0x47,
    0x08, 0xd8, 0x92, 0xda, 0x2f, 0x4b, 0x09, 0x84,
    0x3b, 0x9c, 0x43, 0xf4, 0x2a, 0x7f, 0x68, 0x81,
  }};
#endif

static char hexapod_msgs__msg__LegCommands__TYPE_NAME[] = "hexapod_msgs/msg/LegCommands";
static char geometry_msgs__msg__Point__TYPE_NAME[] = "geometry_msgs/msg/Point";

// Define type names, field names, and default values
static char hexapod_msgs__msg__LegCommands__FIELD_NAME__positions[] = "positions";

static rosidl_runtime_c__type_description__Field hexapod_msgs__msg__LegCommands__FIELDS[] = {
  {
    {hexapod_msgs__msg__LegCommands__FIELD_NAME__positions, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription hexapod_msgs__msg__LegCommands__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
hexapod_msgs__msg__LegCommands__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {hexapod_msgs__msg__LegCommands__TYPE_NAME, 28, 28},
      {hexapod_msgs__msg__LegCommands__FIELDS, 1, 1},
    },
    {hexapod_msgs__msg__LegCommands__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&geometry_msgs__msg__Point__EXPECTED_HASH, geometry_msgs__msg__Point__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = geometry_msgs__msg__Point__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "geometry_msgs/Point[] positions  # Desired Cartesian positions of the feet";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
hexapod_msgs__msg__LegCommands__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {hexapod_msgs__msg__LegCommands__TYPE_NAME, 28, 28},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 75, 75},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
hexapod_msgs__msg__LegCommands__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *hexapod_msgs__msg__LegCommands__get_individual_type_description_source(NULL),
    sources[1] = *geometry_msgs__msg__Point__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
