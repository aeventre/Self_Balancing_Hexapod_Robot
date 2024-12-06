// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hexapod_msgs:msg/FootStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hexapod_msgs/msg/foot_status.hpp"


#ifndef HEXAPOD_MSGS__MSG__DETAIL__FOOT_STATUS__STRUCT_HPP_
#define HEXAPOD_MSGS__MSG__DETAIL__FOOT_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hexapod_msgs__msg__FootStatus __attribute__((deprecated))
#else
# define DEPRECATED__hexapod_msgs__msg__FootStatus __declspec(deprecated)
#endif

namespace hexapod_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct FootStatus_
{
  using Type = FootStatus_<ContainerAllocator>;

  explicit FootStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit FootStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _data_type =
    std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>>;
  _data_type data;

  // setters for named parameter idiom
  Type & set__data(
    const std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>> & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hexapod_msgs::msg::FootStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const hexapod_msgs::msg::FootStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hexapod_msgs::msg::FootStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hexapod_msgs::msg::FootStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hexapod_msgs::msg::FootStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hexapod_msgs::msg::FootStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hexapod_msgs::msg::FootStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hexapod_msgs::msg::FootStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hexapod_msgs::msg::FootStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hexapod_msgs::msg::FootStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hexapod_msgs__msg__FootStatus
    std::shared_ptr<hexapod_msgs::msg::FootStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hexapod_msgs__msg__FootStatus
    std::shared_ptr<hexapod_msgs::msg::FootStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const FootStatus_ & other) const
  {
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const FootStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct FootStatus_

// alias to use template instance with default allocator
using FootStatus =
  hexapod_msgs::msg::FootStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace hexapod_msgs

#endif  // HEXAPOD_MSGS__MSG__DETAIL__FOOT_STATUS__STRUCT_HPP_
