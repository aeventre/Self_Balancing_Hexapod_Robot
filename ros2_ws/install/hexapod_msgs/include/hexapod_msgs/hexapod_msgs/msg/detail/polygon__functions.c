// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hexapod_msgs:msg/Polygon.idl
// generated code does not contain a copyright notice
#include "hexapod_msgs/msg/detail/polygon__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `vertices`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
hexapod_msgs__msg__Polygon__init(hexapod_msgs__msg__Polygon * msg)
{
  if (!msg) {
    return false;
  }
  // vertices
  if (!geometry_msgs__msg__Point__Sequence__init(&msg->vertices, 0)) {
    hexapod_msgs__msg__Polygon__fini(msg);
    return false;
  }
  return true;
}

void
hexapod_msgs__msg__Polygon__fini(hexapod_msgs__msg__Polygon * msg)
{
  if (!msg) {
    return;
  }
  // vertices
  geometry_msgs__msg__Point__Sequence__fini(&msg->vertices);
}

bool
hexapod_msgs__msg__Polygon__are_equal(const hexapod_msgs__msg__Polygon * lhs, const hexapod_msgs__msg__Polygon * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // vertices
  if (!geometry_msgs__msg__Point__Sequence__are_equal(
      &(lhs->vertices), &(rhs->vertices)))
  {
    return false;
  }
  return true;
}

bool
hexapod_msgs__msg__Polygon__copy(
  const hexapod_msgs__msg__Polygon * input,
  hexapod_msgs__msg__Polygon * output)
{
  if (!input || !output) {
    return false;
  }
  // vertices
  if (!geometry_msgs__msg__Point__Sequence__copy(
      &(input->vertices), &(output->vertices)))
  {
    return false;
  }
  return true;
}

hexapod_msgs__msg__Polygon *
hexapod_msgs__msg__Polygon__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__msg__Polygon * msg = (hexapod_msgs__msg__Polygon *)allocator.allocate(sizeof(hexapod_msgs__msg__Polygon), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hexapod_msgs__msg__Polygon));
  bool success = hexapod_msgs__msg__Polygon__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hexapod_msgs__msg__Polygon__destroy(hexapod_msgs__msg__Polygon * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hexapod_msgs__msg__Polygon__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hexapod_msgs__msg__Polygon__Sequence__init(hexapod_msgs__msg__Polygon__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__msg__Polygon * data = NULL;

  if (size) {
    data = (hexapod_msgs__msg__Polygon *)allocator.zero_allocate(size, sizeof(hexapod_msgs__msg__Polygon), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hexapod_msgs__msg__Polygon__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hexapod_msgs__msg__Polygon__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
hexapod_msgs__msg__Polygon__Sequence__fini(hexapod_msgs__msg__Polygon__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hexapod_msgs__msg__Polygon__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

hexapod_msgs__msg__Polygon__Sequence *
hexapod_msgs__msg__Polygon__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__msg__Polygon__Sequence * array = (hexapod_msgs__msg__Polygon__Sequence *)allocator.allocate(sizeof(hexapod_msgs__msg__Polygon__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hexapod_msgs__msg__Polygon__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hexapod_msgs__msg__Polygon__Sequence__destroy(hexapod_msgs__msg__Polygon__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hexapod_msgs__msg__Polygon__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hexapod_msgs__msg__Polygon__Sequence__are_equal(const hexapod_msgs__msg__Polygon__Sequence * lhs, const hexapod_msgs__msg__Polygon__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hexapod_msgs__msg__Polygon__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hexapod_msgs__msg__Polygon__Sequence__copy(
  const hexapod_msgs__msg__Polygon__Sequence * input,
  hexapod_msgs__msg__Polygon__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hexapod_msgs__msg__Polygon);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hexapod_msgs__msg__Polygon * data =
      (hexapod_msgs__msg__Polygon *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hexapod_msgs__msg__Polygon__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hexapod_msgs__msg__Polygon__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hexapod_msgs__msg__Polygon__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
