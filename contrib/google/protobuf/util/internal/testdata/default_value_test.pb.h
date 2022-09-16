// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/util/internal/testdata/default_value_test.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2futil_2finternal_2ftestdata_2fdefault_5fvalue_5ftest_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2futil_2finternal_2ftestdata_2fdefault_5fvalue_5ftest_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021005 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2futil_2finternal_2ftestdata_2fdefault_5fvalue_5ftest_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_google_2fprotobuf_2futil_2finternal_2ftestdata_2fdefault_5fvalue_5ftest_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_google_2fprotobuf_2futil_2finternal_2ftestdata_2fdefault_5fvalue_5ftest_2eproto;
namespace proto_util_converter {
namespace testing {
class DefaultValueTest;
struct DefaultValueTestDefaultTypeInternal;
extern DefaultValueTestDefaultTypeInternal _DefaultValueTest_default_instance_;
}  // namespace testing
}  // namespace proto_util_converter
PROTOBUF_NAMESPACE_OPEN
template<> ::proto_util_converter::testing::DefaultValueTest* Arena::CreateMaybeMessage<::proto_util_converter::testing::DefaultValueTest>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace proto_util_converter {
namespace testing {

enum DefaultValueTest_EnumDefault : int {
  DefaultValueTest_EnumDefault_ENUM_FIRST = 0,
  DefaultValueTest_EnumDefault_ENUM_SECOND = 1,
  DefaultValueTest_EnumDefault_ENUM_THIRD = 2,
  DefaultValueTest_EnumDefault_DefaultValueTest_EnumDefault_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  DefaultValueTest_EnumDefault_DefaultValueTest_EnumDefault_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool DefaultValueTest_EnumDefault_IsValid(int value);
constexpr DefaultValueTest_EnumDefault DefaultValueTest_EnumDefault_EnumDefault_MIN = DefaultValueTest_EnumDefault_ENUM_FIRST;
constexpr DefaultValueTest_EnumDefault DefaultValueTest_EnumDefault_EnumDefault_MAX = DefaultValueTest_EnumDefault_ENUM_THIRD;
constexpr int DefaultValueTest_EnumDefault_EnumDefault_ARRAYSIZE = DefaultValueTest_EnumDefault_EnumDefault_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* DefaultValueTest_EnumDefault_descriptor();
template<typename T>
inline const std::string& DefaultValueTest_EnumDefault_Name(T enum_t_value) {
  static_assert(::std::is_same<T, DefaultValueTest_EnumDefault>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function DefaultValueTest_EnumDefault_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    DefaultValueTest_EnumDefault_descriptor(), enum_t_value);
}
inline bool DefaultValueTest_EnumDefault_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, DefaultValueTest_EnumDefault* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<DefaultValueTest_EnumDefault>(
    DefaultValueTest_EnumDefault_descriptor(), name, value);
}
// ===================================================================

class DefaultValueTest final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:proto_util_converter.testing.DefaultValueTest) */ {
 public:
  inline DefaultValueTest() : DefaultValueTest(nullptr) {}
  ~DefaultValueTest() override;
  explicit PROTOBUF_CONSTEXPR DefaultValueTest(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  DefaultValueTest(const DefaultValueTest& from);
  DefaultValueTest(DefaultValueTest&& from) noexcept
    : DefaultValueTest() {
    *this = ::std::move(from);
  }

  inline DefaultValueTest& operator=(const DefaultValueTest& from) {
    CopyFrom(from);
    return *this;
  }
  inline DefaultValueTest& operator=(DefaultValueTest&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const DefaultValueTest& default_instance() {
    return *internal_default_instance();
  }
  static inline const DefaultValueTest* internal_default_instance() {
    return reinterpret_cast<const DefaultValueTest*>(
               &_DefaultValueTest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(DefaultValueTest& a, DefaultValueTest& b) {
    a.Swap(&b);
  }
  inline void Swap(DefaultValueTest* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(DefaultValueTest* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  DefaultValueTest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<DefaultValueTest>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const DefaultValueTest& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const DefaultValueTest& from) {
    DefaultValueTest::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(DefaultValueTest* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "proto_util_converter.testing.DefaultValueTest";
  }
  protected:
  explicit DefaultValueTest(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  typedef DefaultValueTest_EnumDefault EnumDefault;
  static constexpr EnumDefault ENUM_FIRST =
    DefaultValueTest_EnumDefault_ENUM_FIRST;
  static constexpr EnumDefault ENUM_SECOND =
    DefaultValueTest_EnumDefault_ENUM_SECOND;
  static constexpr EnumDefault ENUM_THIRD =
    DefaultValueTest_EnumDefault_ENUM_THIRD;
  static inline bool EnumDefault_IsValid(int value) {
    return DefaultValueTest_EnumDefault_IsValid(value);
  }
  static constexpr EnumDefault EnumDefault_MIN =
    DefaultValueTest_EnumDefault_EnumDefault_MIN;
  static constexpr EnumDefault EnumDefault_MAX =
    DefaultValueTest_EnumDefault_EnumDefault_MAX;
  static constexpr int EnumDefault_ARRAYSIZE =
    DefaultValueTest_EnumDefault_EnumDefault_ARRAYSIZE;
  static inline const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
  EnumDefault_descriptor() {
    return DefaultValueTest_EnumDefault_descriptor();
  }
  template<typename T>
  static inline const std::string& EnumDefault_Name(T enum_t_value) {
    static_assert(::std::is_same<T, EnumDefault>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function EnumDefault_Name.");
    return DefaultValueTest_EnumDefault_Name(enum_t_value);
  }
  static inline bool EnumDefault_Parse(::PROTOBUF_NAMESPACE_ID::ConstStringParam name,
      EnumDefault* value) {
    return DefaultValueTest_EnumDefault_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  enum : int {
    kRepeatedDoubleFieldNumber = 2,
    kStringValueFieldNumber = 15,
    kBytesValueFieldNumber = 17,
    kDoubleValueFieldNumber = 1,
    kInt64ValueFieldNumber = 5,
    kFloatValueFieldNumber = 3,
    kInt32ValueFieldNumber = 9,
    kUint64ValueFieldNumber = 7,
    kUint32ValueFieldNumber = 11,
    kBoolValueFieldNumber = 13,
    kEnumValueFieldNumber = 18,
  };
  // repeated double repeated_double = 2;
  int repeated_double_size() const;
  private:
  int _internal_repeated_double_size() const;
  public:
  void clear_repeated_double();
  private:
  double _internal_repeated_double(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >&
      _internal_repeated_double() const;
  void _internal_add_repeated_double(double value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >*
      _internal_mutable_repeated_double();
  public:
  double repeated_double(int index) const;
  void set_repeated_double(int index, double value);
  void add_repeated_double(double value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >&
      repeated_double() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >*
      mutable_repeated_double();

  // string string_value = 15;
  void clear_string_value();
  const std::string& string_value() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_string_value(ArgT0&& arg0, ArgT... args);
  std::string* mutable_string_value();
  PROTOBUF_NODISCARD std::string* release_string_value();
  void set_allocated_string_value(std::string* string_value);
  private:
  const std::string& _internal_string_value() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_string_value(const std::string& value);
  std::string* _internal_mutable_string_value();
  public:

  // bytes bytes_value = 17 [ctype = CORD];
  void clear_bytes_value();
 private:
  // Hidden due to unknown ctype option.
  const std::string& bytes_value() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_bytes_value(ArgT0&& arg0, ArgT... args);
  std::string* mutable_bytes_value();
  PROTOBUF_NODISCARD std::string* release_bytes_value();
  void set_allocated_bytes_value(std::string* bytes_value);
  private:
  const std::string& _internal_bytes_value() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_bytes_value(const std::string& value);
  std::string* _internal_mutable_bytes_value();
  public:
 public:

  // double double_value = 1;
  void clear_double_value();
  double double_value() const;
  void set_double_value(double value);
  private:
  double _internal_double_value() const;
  void _internal_set_double_value(double value);
  public:

  // int64 int64_value = 5;
  void clear_int64_value();
  int64_t int64_value() const;
  void set_int64_value(int64_t value);
  private:
  int64_t _internal_int64_value() const;
  void _internal_set_int64_value(int64_t value);
  public:

  // float float_value = 3;
  void clear_float_value();
  float float_value() const;
  void set_float_value(float value);
  private:
  float _internal_float_value() const;
  void _internal_set_float_value(float value);
  public:

  // int32 int32_value = 9;
  void clear_int32_value();
  int32_t int32_value() const;
  void set_int32_value(int32_t value);
  private:
  int32_t _internal_int32_value() const;
  void _internal_set_int32_value(int32_t value);
  public:

  // uint64 uint64_value = 7;
  void clear_uint64_value();
  uint64_t uint64_value() const;
  void set_uint64_value(uint64_t value);
  private:
  uint64_t _internal_uint64_value() const;
  void _internal_set_uint64_value(uint64_t value);
  public:

  // uint32 uint32_value = 11;
  void clear_uint32_value();
  uint32_t uint32_value() const;
  void set_uint32_value(uint32_t value);
  private:
  uint32_t _internal_uint32_value() const;
  void _internal_set_uint32_value(uint32_t value);
  public:

  // bool bool_value = 13;
  void clear_bool_value();
  bool bool_value() const;
  void set_bool_value(bool value);
  private:
  bool _internal_bool_value() const;
  void _internal_set_bool_value(bool value);
  public:

  // .proto_util_converter.testing.DefaultValueTest.EnumDefault enum_value = 18;
  void clear_enum_value();
  ::proto_util_converter::testing::DefaultValueTest_EnumDefault enum_value() const;
  void set_enum_value(::proto_util_converter::testing::DefaultValueTest_EnumDefault value);
  private:
  ::proto_util_converter::testing::DefaultValueTest_EnumDefault _internal_enum_value() const;
  void _internal_set_enum_value(::proto_util_converter::testing::DefaultValueTest_EnumDefault value);
  public:

  // @@protoc_insertion_point(class_scope:proto_util_converter.testing.DefaultValueTest)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::RepeatedField< double > repeated_double_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr string_value_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr bytes_value_;
    double double_value_;
    int64_t int64_value_;
    float float_value_;
    int32_t int32_value_;
    uint64_t uint64_value_;
    uint32_t uint32_value_;
    bool bool_value_;
    int enum_value_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_google_2fprotobuf_2futil_2finternal_2ftestdata_2fdefault_5fvalue_5ftest_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// DefaultValueTest

// double double_value = 1;
inline void DefaultValueTest::clear_double_value() {
  _impl_.double_value_ = 0;
}
inline double DefaultValueTest::_internal_double_value() const {
  return _impl_.double_value_;
}
inline double DefaultValueTest::double_value() const {
  // @@protoc_insertion_point(field_get:proto_util_converter.testing.DefaultValueTest.double_value)
  return _internal_double_value();
}
inline void DefaultValueTest::_internal_set_double_value(double value) {
  
  _impl_.double_value_ = value;
}
inline void DefaultValueTest::set_double_value(double value) {
  _internal_set_double_value(value);
  // @@protoc_insertion_point(field_set:proto_util_converter.testing.DefaultValueTest.double_value)
}

// repeated double repeated_double = 2;
inline int DefaultValueTest::_internal_repeated_double_size() const {
  return _impl_.repeated_double_.size();
}
inline int DefaultValueTest::repeated_double_size() const {
  return _internal_repeated_double_size();
}
inline void DefaultValueTest::clear_repeated_double() {
  _impl_.repeated_double_.Clear();
}
inline double DefaultValueTest::_internal_repeated_double(int index) const {
  return _impl_.repeated_double_.Get(index);
}
inline double DefaultValueTest::repeated_double(int index) const {
  // @@protoc_insertion_point(field_get:proto_util_converter.testing.DefaultValueTest.repeated_double)
  return _internal_repeated_double(index);
}
inline void DefaultValueTest::set_repeated_double(int index, double value) {
  _impl_.repeated_double_.Set(index, value);
  // @@protoc_insertion_point(field_set:proto_util_converter.testing.DefaultValueTest.repeated_double)
}
inline void DefaultValueTest::_internal_add_repeated_double(double value) {
  _impl_.repeated_double_.Add(value);
}
inline void DefaultValueTest::add_repeated_double(double value) {
  _internal_add_repeated_double(value);
  // @@protoc_insertion_point(field_add:proto_util_converter.testing.DefaultValueTest.repeated_double)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >&
DefaultValueTest::_internal_repeated_double() const {
  return _impl_.repeated_double_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >&
DefaultValueTest::repeated_double() const {
  // @@protoc_insertion_point(field_list:proto_util_converter.testing.DefaultValueTest.repeated_double)
  return _internal_repeated_double();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >*
DefaultValueTest::_internal_mutable_repeated_double() {
  return &_impl_.repeated_double_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< double >*
DefaultValueTest::mutable_repeated_double() {
  // @@protoc_insertion_point(field_mutable_list:proto_util_converter.testing.DefaultValueTest.repeated_double)
  return _internal_mutable_repeated_double();
}

// float float_value = 3;
inline void DefaultValueTest::clear_float_value() {
  _impl_.float_value_ = 0;
}
inline float DefaultValueTest::_internal_float_value() const {
  return _impl_.float_value_;
}
inline float DefaultValueTest::float_value() const {
  // @@protoc_insertion_point(field_get:proto_util_converter.testing.DefaultValueTest.float_value)
  return _internal_float_value();
}
inline void DefaultValueTest::_internal_set_float_value(float value) {
  
  _impl_.float_value_ = value;
}
inline void DefaultValueTest::set_float_value(float value) {
  _internal_set_float_value(value);
  // @@protoc_insertion_point(field_set:proto_util_converter.testing.DefaultValueTest.float_value)
}

// int64 int64_value = 5;
inline void DefaultValueTest::clear_int64_value() {
  _impl_.int64_value_ = int64_t{0};
}
inline int64_t DefaultValueTest::_internal_int64_value() const {
  return _impl_.int64_value_;
}
inline int64_t DefaultValueTest::int64_value() const {
  // @@protoc_insertion_point(field_get:proto_util_converter.testing.DefaultValueTest.int64_value)
  return _internal_int64_value();
}
inline void DefaultValueTest::_internal_set_int64_value(int64_t value) {
  
  _impl_.int64_value_ = value;
}
inline void DefaultValueTest::set_int64_value(int64_t value) {
  _internal_set_int64_value(value);
  // @@protoc_insertion_point(field_set:proto_util_converter.testing.DefaultValueTest.int64_value)
}

// uint64 uint64_value = 7;
inline void DefaultValueTest::clear_uint64_value() {
  _impl_.uint64_value_ = uint64_t{0u};
}
inline uint64_t DefaultValueTest::_internal_uint64_value() const {
  return _impl_.uint64_value_;
}
inline uint64_t DefaultValueTest::uint64_value() const {
  // @@protoc_insertion_point(field_get:proto_util_converter.testing.DefaultValueTest.uint64_value)
  return _internal_uint64_value();
}
inline void DefaultValueTest::_internal_set_uint64_value(uint64_t value) {
  
  _impl_.uint64_value_ = value;
}
inline void DefaultValueTest::set_uint64_value(uint64_t value) {
  _internal_set_uint64_value(value);
  // @@protoc_insertion_point(field_set:proto_util_converter.testing.DefaultValueTest.uint64_value)
}

// int32 int32_value = 9;
inline void DefaultValueTest::clear_int32_value() {
  _impl_.int32_value_ = 0;
}
inline int32_t DefaultValueTest::_internal_int32_value() const {
  return _impl_.int32_value_;
}
inline int32_t DefaultValueTest::int32_value() const {
  // @@protoc_insertion_point(field_get:proto_util_converter.testing.DefaultValueTest.int32_value)
  return _internal_int32_value();
}
inline void DefaultValueTest::_internal_set_int32_value(int32_t value) {
  
  _impl_.int32_value_ = value;
}
inline void DefaultValueTest::set_int32_value(int32_t value) {
  _internal_set_int32_value(value);
  // @@protoc_insertion_point(field_set:proto_util_converter.testing.DefaultValueTest.int32_value)
}

// uint32 uint32_value = 11;
inline void DefaultValueTest::clear_uint32_value() {
  _impl_.uint32_value_ = 0u;
}
inline uint32_t DefaultValueTest::_internal_uint32_value() const {
  return _impl_.uint32_value_;
}
inline uint32_t DefaultValueTest::uint32_value() const {
  // @@protoc_insertion_point(field_get:proto_util_converter.testing.DefaultValueTest.uint32_value)
  return _internal_uint32_value();
}
inline void DefaultValueTest::_internal_set_uint32_value(uint32_t value) {
  
  _impl_.uint32_value_ = value;
}
inline void DefaultValueTest::set_uint32_value(uint32_t value) {
  _internal_set_uint32_value(value);
  // @@protoc_insertion_point(field_set:proto_util_converter.testing.DefaultValueTest.uint32_value)
}

// bool bool_value = 13;
inline void DefaultValueTest::clear_bool_value() {
  _impl_.bool_value_ = false;
}
inline bool DefaultValueTest::_internal_bool_value() const {
  return _impl_.bool_value_;
}
inline bool DefaultValueTest::bool_value() const {
  // @@protoc_insertion_point(field_get:proto_util_converter.testing.DefaultValueTest.bool_value)
  return _internal_bool_value();
}
inline void DefaultValueTest::_internal_set_bool_value(bool value) {
  
  _impl_.bool_value_ = value;
}
inline void DefaultValueTest::set_bool_value(bool value) {
  _internal_set_bool_value(value);
  // @@protoc_insertion_point(field_set:proto_util_converter.testing.DefaultValueTest.bool_value)
}

// string string_value = 15;
inline void DefaultValueTest::clear_string_value() {
  _impl_.string_value_.ClearToEmpty();
}
inline const std::string& DefaultValueTest::string_value() const {
  // @@protoc_insertion_point(field_get:proto_util_converter.testing.DefaultValueTest.string_value)
  return _internal_string_value();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void DefaultValueTest::set_string_value(ArgT0&& arg0, ArgT... args) {
 
 _impl_.string_value_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:proto_util_converter.testing.DefaultValueTest.string_value)
}
inline std::string* DefaultValueTest::mutable_string_value() {
  std::string* _s = _internal_mutable_string_value();
  // @@protoc_insertion_point(field_mutable:proto_util_converter.testing.DefaultValueTest.string_value)
  return _s;
}
inline const std::string& DefaultValueTest::_internal_string_value() const {
  return _impl_.string_value_.Get();
}
inline void DefaultValueTest::_internal_set_string_value(const std::string& value) {
  
  _impl_.string_value_.Set(value, GetArenaForAllocation());
}
inline std::string* DefaultValueTest::_internal_mutable_string_value() {
  
  return _impl_.string_value_.Mutable(GetArenaForAllocation());
}
inline std::string* DefaultValueTest::release_string_value() {
  // @@protoc_insertion_point(field_release:proto_util_converter.testing.DefaultValueTest.string_value)
  return _impl_.string_value_.Release();
}
inline void DefaultValueTest::set_allocated_string_value(std::string* string_value) {
  if (string_value != nullptr) {
    
  } else {
    
  }
  _impl_.string_value_.SetAllocated(string_value, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.string_value_.IsDefault()) {
    _impl_.string_value_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:proto_util_converter.testing.DefaultValueTest.string_value)
}

// bytes bytes_value = 17 [ctype = CORD];
inline void DefaultValueTest::clear_bytes_value() {
  _impl_.bytes_value_.ClearToEmpty();
}
inline const std::string& DefaultValueTest::bytes_value() const {
  // @@protoc_insertion_point(field_get:proto_util_converter.testing.DefaultValueTest.bytes_value)
  return _internal_bytes_value();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void DefaultValueTest::set_bytes_value(ArgT0&& arg0, ArgT... args) {
 
 _impl_.bytes_value_.SetBytes(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:proto_util_converter.testing.DefaultValueTest.bytes_value)
}
inline std::string* DefaultValueTest::mutable_bytes_value() {
  std::string* _s = _internal_mutable_bytes_value();
  // @@protoc_insertion_point(field_mutable:proto_util_converter.testing.DefaultValueTest.bytes_value)
  return _s;
}
inline const std::string& DefaultValueTest::_internal_bytes_value() const {
  return _impl_.bytes_value_.Get();
}
inline void DefaultValueTest::_internal_set_bytes_value(const std::string& value) {
  
  _impl_.bytes_value_.Set(value, GetArenaForAllocation());
}
inline std::string* DefaultValueTest::_internal_mutable_bytes_value() {
  
  return _impl_.bytes_value_.Mutable(GetArenaForAllocation());
}
inline std::string* DefaultValueTest::release_bytes_value() {
  // @@protoc_insertion_point(field_release:proto_util_converter.testing.DefaultValueTest.bytes_value)
  return _impl_.bytes_value_.Release();
}
inline void DefaultValueTest::set_allocated_bytes_value(std::string* bytes_value) {
  if (bytes_value != nullptr) {
    
  } else {
    
  }
  _impl_.bytes_value_.SetAllocated(bytes_value, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.bytes_value_.IsDefault()) {
    _impl_.bytes_value_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:proto_util_converter.testing.DefaultValueTest.bytes_value)
}

// .proto_util_converter.testing.DefaultValueTest.EnumDefault enum_value = 18;
inline void DefaultValueTest::clear_enum_value() {
  _impl_.enum_value_ = 0;
}
inline ::proto_util_converter::testing::DefaultValueTest_EnumDefault DefaultValueTest::_internal_enum_value() const {
  return static_cast< ::proto_util_converter::testing::DefaultValueTest_EnumDefault >(_impl_.enum_value_);
}
inline ::proto_util_converter::testing::DefaultValueTest_EnumDefault DefaultValueTest::enum_value() const {
  // @@protoc_insertion_point(field_get:proto_util_converter.testing.DefaultValueTest.enum_value)
  return _internal_enum_value();
}
inline void DefaultValueTest::_internal_set_enum_value(::proto_util_converter::testing::DefaultValueTest_EnumDefault value) {
  
  _impl_.enum_value_ = value;
}
inline void DefaultValueTest::set_enum_value(::proto_util_converter::testing::DefaultValueTest_EnumDefault value) {
  _internal_set_enum_value(value);
  // @@protoc_insertion_point(field_set:proto_util_converter.testing.DefaultValueTest.enum_value)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace testing
}  // namespace proto_util_converter

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::proto_util_converter::testing::DefaultValueTest_EnumDefault> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto_util_converter::testing::DefaultValueTest_EnumDefault>() {
  return ::proto_util_converter::testing::DefaultValueTest_EnumDefault_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2futil_2finternal_2ftestdata_2fdefault_5fvalue_5ftest_2eproto
