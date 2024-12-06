// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from hexapod_msgs:msg/LegCommands.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "hexapod_msgs/msg/detail/leg_commands__rosidl_typesupport_introspection_c.h"
#include "hexapod_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "hexapod_msgs/msg/detail/leg_commands__functions.h"
#include "hexapod_msgs/msg/detail/leg_commands__struct.h"


// Include directives for member types
// Member `positions`
#include "geometry_msgs/msg/point.h"
// Member `positions`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__LegCommands_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  hexapod_msgs__msg__LegCommands__init(message_memory);
}

void hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__LegCommands_fini_function(void * message_memory)
{
  hexapod_msgs__msg__LegCommands__fini(message_memory);
}

size_t hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__size_function__LegCommands__positions(
  const void * untyped_member)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return member->size;
}

const void * hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__get_const_function__LegCommands__positions(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void * hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__get_function__LegCommands__positions(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__fetch_function__LegCommands__positions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Point * item =
    ((const geometry_msgs__msg__Point *)
    hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__get_const_function__LegCommands__positions(untyped_member, index));
  geometry_msgs__msg__Point * value =
    (geometry_msgs__msg__Point *)(untyped_value);
  *value = *item;
}

void hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__assign_function__LegCommands__positions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Point * item =
    ((geometry_msgs__msg__Point *)
    hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__get_function__LegCommands__positions(untyped_member, index));
  const geometry_msgs__msg__Point * value =
    (const geometry_msgs__msg__Point *)(untyped_value);
  *item = *value;
}

bool hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__resize_function__LegCommands__positions(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  geometry_msgs__msg__Point__Sequence__fini(member);
  return geometry_msgs__msg__Point__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__LegCommands_message_member_array[1] = {
  {
    "positions",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hexapod_msgs__msg__LegCommands, positions),  // bytes offset in struct
    NULL,  // default value
    hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__size_function__LegCommands__positions,  // size() function pointer
    hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__get_const_function__LegCommands__positions,  // get_const(index) function pointer
    hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__get_function__LegCommands__positions,  // get(index) function pointer
    hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__fetch_function__LegCommands__positions,  // fetch(index, &value) function pointer
    hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__assign_function__LegCommands__positions,  // assign(index, value) function pointer
    hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__resize_function__LegCommands__positions  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__LegCommands_message_members = {
  "hexapod_msgs__msg",  // message namespace
  "LegCommands",  // message name
  1,  // number of fields
  sizeof(hexapod_msgs__msg__LegCommands),
  false,  // has_any_key_member_
  hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__LegCommands_message_member_array,  // message members
  hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__LegCommands_init_function,  // function to initialize message memory (memory has to be allocated)
  hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__LegCommands_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__LegCommands_message_type_support_handle = {
  0,
  &hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__LegCommands_message_members,
  get_message_typesupport_handle_function,
  &hexapod_msgs__msg__LegCommands__get_type_hash,
  &hexapod_msgs__msg__LegCommands__get_type_description,
  &hexapod_msgs__msg__LegCommands__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hexapod_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hexapod_msgs, msg, LegCommands)() {
  hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__LegCommands_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__LegCommands_message_type_support_handle.typesupport_identifier) {
    hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__LegCommands_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &hexapod_msgs__msg__LegCommands__rosidl_typesupport_introspection_c__LegCommands_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
