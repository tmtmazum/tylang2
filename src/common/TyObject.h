#pragma once

#include <cinttypes>
#include <exception>
#include <string>
#include <type_traits>

namespace ty
{
namespace Attribute
{

//! List of static attributes for TyObjects
enum TyObjectAttribute
{
  HasGlobal = 0x0001
};

} // namespace Attribute

//! Base object for all types in the tylang libraries
class TyObjectBase
{
};

//! Object that all tylang objects must derive from
template<uint64_t attributes = 0>
class TyObject : public TyObjectBase
{
public:
  //! Returns true if this type has a top-level global instance
  constexpr static auto has_global() { return attributes & Attribute::HasGlobal; }
};

template<typename T>
class TyVirtual : public T
{
public:
  virtual ~TyVirtual() = default;
};

//! Returns a reference to the top-level global instance of a TyObject
template<typename T>
static T& Global()
{
  static_assert(std::is_base_of<TyObjectBase, T>::value, "T must derive TyObject");
  static_assert(T::has_global(), "T is not defined to have a global instance");

  static T object;
  return object;
}

class TyException : public std::exception
{
  std::string m_name;

public:
  explicit TyException(std::string wh)
    : m_name{ std::move(wh) }
  {
  }

  const char* what() const noexcept override { return m_name.c_str(); }
};

} // namespace ty

// -- Logging/Debugging Macros --

#define TY_ASSERTF(cond, format, ...)                                                                                  \
  if (!(cond))                                                                                                         \
  {                                                                                                                    \
    fprintf(stderr, "[%s][%s][%d] Assertion Failed: '" #cond "'\n" format "\n", __FILE__, __FUNCTION__, __LINE__,      \
            __VA_ARGS__);                                                                                              \
    std::abort();                                                                                                      \
  }

#define TY_STDOUT(format, ...) fprintf(stdout, format "\n", __VA_ARGS__)

#define TY_STDERR(format, ...) fprintf(stderr, format "\n", __VA_ARGS__)
