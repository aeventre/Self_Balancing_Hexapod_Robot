// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hexapod_msgs:msg/JointAngles.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hexapod_msgs/msg/joint_angles.hpp"


#ifndef HEXAPOD_MSGS__MSG__DETAIL__JOINT_ANGLES__STRUCT_HPP_
#define HEXAPOD_MSGS__MSG__DETAIL__JOINT_ANGLES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hexapod_msgs__msg__JointAngles __attribute__((deprecated))
#else
# define DEPRECATED__hexapod_msgs__msg__JointAngles __declspec(deprecated)
#endif

namespace hexapod_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct JointAngles_
{
  using Type = JointAngles_<ContainerAllocator>;

  explicit JointAngles_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit JointAngles_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _angles_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _angles_type angles;

  // setters for named parameter idiom
  Type & set__angles(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->angles = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hexapod_msgs::msg::JointAngles_<ContainerAllocator> *;
  using ConstRawPtr =
    const hexapod_msgs::msg::JointAngles_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hexapod_msgs::msg::JointAngles_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hexapod_msgs::msg::JointAngles_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hexapod_msgs::msg::JointAngles_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hexapod_msgs::msg::JointAngles_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hexapod_msgs::msg::JointAngles_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hexapod_msgs::msg::JointAngles_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hexapod_msgs::msg::JointAngles_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hexapod_msgs::msg::JointAngles_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hexapod_msgs__msg__JointAngles
    std::shared_ptr<hexapod_msgs::msg::JointAngles_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hexapod_msgs__msg__JointAngles
    std::shared_ptr<hexapod_msgs::msg::JointAngles_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const JointAngles_ & other) const
  {
    if (this->angles != other.angles) {
      return false;
    }
    return true;
  }
  bool operator!=(const JointAngles_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct JointAngles_

// alias to use template instance with default allocator
using JointAngles =
  hexapod_msgs::msg::JointAngles_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace hexapod_msgs

#endif  // HEXAPOD_MSGS__MSG__DETAIL__JOINT_ANGLES__STRUCT_HPP_
