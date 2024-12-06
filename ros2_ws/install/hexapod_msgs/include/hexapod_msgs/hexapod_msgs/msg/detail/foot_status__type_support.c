// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from hexapod_msgs:msg/FootStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "hexapod_msgs/msg/detail/foot_status__rosidl_typesupport_introspection_c.h"
#include "hexapod_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "hexapod_msgs/msg/detail/foot_status__functions.h"
#include "hexapod_msgs/msg/detail/foot_status__struct.h"


// Include directives for member types
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__FootStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  hexapod_msgs__msg__FootStatus__init(message_memory);
}

void hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__FootStatus_fini_function(void * message_memory)
{
  hexapod_msgs__msg__FootStatus__fini(message_memory);
}

size_t hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__size_function__FootStatus__data(
  const void * untyped_member)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return member->size;
}

const void * hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__get_const_function__FootStatus__data(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void * hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__get_function__FootStatus__data(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__fetch_function__FootStatus__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const bool * item =
    ((const bool *)
    hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__get_const_function__FootStatus__data(untyped_member, index));
  bool * value =
    (bool *)(untyped_value);
  *value = *item;
}

void hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__assign_function__FootStatus__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  bool * item =
    ((bool *)
    hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__get_function__FootStatus__data(untyped_member, index));
  const bool * value =
    (const bool *)(untyped_value);
  *item = *value;
}

bool hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__resize_function__FootStatus__data(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  rosidl_runtime_c__boolean__Sequence__fini(member);
  return rosidl_runtime_c__boolean__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__FootStatus_message_member_array[1] = {
  {
    "data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hexapod_msgs__msg__FootStatus, data),  // bytes offset in struct
    NULL,  // default value
    hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__size_function__FootStatus__data,  // size() function pointer
    hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__get_const_function__FootStatus__data,  // get_const(index) function pointer
    hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__get_function__FootStatus__data,  // get(index) function pointer
    hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__fetch_function__FootStatus__data,  // fetch(index, &value) function pointer
    hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__assign_function__FootStatus__data,  // assign(index, value) function pointer
    hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__resize_function__FootStatus__data  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__FootStatus_message_members = {
  "hexapod_msgs__msg",  // message namespace
  "FootStatus",  // message name
  1,  // number of fields
  sizeof(hexapod_msgs__msg__FootStatus),
  false,  // has_any_key_member_
  hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__FootStatus_message_member_array,  // message members
  hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__FootStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__FootStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__FootStatus_message_type_support_handle = {
  0,
  &hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__FootStatus_message_members,
  get_message_typesupport_handle_function,
  &hexapod_msgs__msg__FootStatus__get_type_hash,
  &hexapod_msgs__msg__FootStatus__get_type_description,
  &hexapod_msgs__msg__FootStatus__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hexapod_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hexapod_msgs, msg, FootStatus)() {
  if (!hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__FootStatus_message_type_support_handle.typesupport_identifier) {
    hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__FootStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &hexapod_msgs__msg__FootStatus__rosidl_typesupport_introspection_c__FootStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
