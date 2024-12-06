// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from hexapod_msgs:msg/JointAngles.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "hexapod_msgs/msg/detail/joint_angles__functions.h"
#include "hexapod_msgs/msg/detail/joint_angles__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace hexapod_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void JointAngles_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) hexapod_msgs::msg::JointAngles(_init);
}

void JointAngles_fini_function(void * message_memory)
{
  auto typed_message = static_cast<hexapod_msgs::msg::JointAngles *>(message_memory);
  typed_message->~JointAngles();
}

size_t size_function__JointAngles__angles(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__JointAngles__angles(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__JointAngles__angles(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__JointAngles__angles(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__JointAngles__angles(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__JointAngles__angles(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__JointAngles__angles(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__JointAngles__angles(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember JointAngles_message_member_array[1] = {
  {
    "angles",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hexapod_msgs::msg::JointAngles, angles),  // bytes offset in struct
    nullptr,  // default value
    size_function__JointAngles__angles,  // size() function pointer
    get_const_function__JointAngles__angles,  // get_const(index) function pointer
    get_function__JointAngles__angles,  // get(index) function pointer
    fetch_function__JointAngles__angles,  // fetch(index, &value) function pointer
    assign_function__JointAngles__angles,  // assign(index, value) function pointer
    resize_function__JointAngles__angles  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers JointAngles_message_members = {
  "hexapod_msgs::msg",  // message namespace
  "JointAngles",  // message name
  1,  // number of fields
  sizeof(hexapod_msgs::msg::JointAngles),
  false,  // has_any_key_member_
  JointAngles_message_member_array,  // message members
  JointAngles_init_function,  // function to initialize message memory (memory has to be allocated)
  JointAngles_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t JointAngles_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &JointAngles_message_members,
  get_message_typesupport_handle_function,
  &hexapod_msgs__msg__JointAngles__get_type_hash,
  &hexapod_msgs__msg__JointAngles__get_type_description,
  &hexapod_msgs__msg__JointAngles__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace hexapod_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<hexapod_msgs::msg::JointAngles>()
{
  return &::hexapod_msgs::msg::rosidl_typesupport_introspection_cpp::JointAngles_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, hexapod_msgs, msg, JointAngles)() {
  return &::hexapod_msgs::msg::rosidl_typesupport_introspection_cpp::JointAngles_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
