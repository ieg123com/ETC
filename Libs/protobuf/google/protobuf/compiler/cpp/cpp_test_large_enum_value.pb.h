// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/compiler/cpp/cpp_test_large_enum_value.proto

#ifndef PROTOBUF_google_2fprotobuf_2fcompiler_2fcpp_2fcpp_5ftest_5flarge_5fenum_5fvalue_2eproto__INCLUDED
#define PROTOBUF_google_2fprotobuf_2fcompiler_2fcpp_2fcpp_5ftest_5flarge_5fenum_5fvalue_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000002 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace protobuf_unittest {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_google_2fprotobuf_2fcompiler_2fcpp_2fcpp_5ftest_5flarge_5fenum_5fvalue_2eproto();
void protobuf_AssignDesc_google_2fprotobuf_2fcompiler_2fcpp_2fcpp_5ftest_5flarge_5fenum_5fvalue_2eproto();
void protobuf_ShutdownFile_google_2fprotobuf_2fcompiler_2fcpp_2fcpp_5ftest_5flarge_5fenum_5fvalue_2eproto();

class TestLargeEnumValue;

enum TestLargeEnumValue_EnumWithLargeValue {
  TestLargeEnumValue_EnumWithLargeValue_VALUE_1 = 1,
  TestLargeEnumValue_EnumWithLargeValue_VALUE_MAX = 2147483647
};
bool TestLargeEnumValue_EnumWithLargeValue_IsValid(int value);
const TestLargeEnumValue_EnumWithLargeValue TestLargeEnumValue_EnumWithLargeValue_EnumWithLargeValue_MIN = TestLargeEnumValue_EnumWithLargeValue_VALUE_1;
const TestLargeEnumValue_EnumWithLargeValue TestLargeEnumValue_EnumWithLargeValue_EnumWithLargeValue_MAX = TestLargeEnumValue_EnumWithLargeValue_VALUE_MAX;
const ::google::protobuf::EnumDescriptor* TestLargeEnumValue_EnumWithLargeValue_descriptor();
inline const ::std::string& TestLargeEnumValue_EnumWithLargeValue_Name(TestLargeEnumValue_EnumWithLargeValue value) {
  return ::google::protobuf::internal::NameOfEnum(
    TestLargeEnumValue_EnumWithLargeValue_descriptor(), value);
}
inline bool TestLargeEnumValue_EnumWithLargeValue_Parse(
    const ::std::string& name, TestLargeEnumValue_EnumWithLargeValue* value) {
  return ::google::protobuf::internal::ParseNamedEnum<TestLargeEnumValue_EnumWithLargeValue>(
    TestLargeEnumValue_EnumWithLargeValue_descriptor(), name, value);
}
// ===================================================================

class TestLargeEnumValue : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:protobuf_unittest.TestLargeEnumValue) */ {
 public:
  TestLargeEnumValue();
  virtual ~TestLargeEnumValue();

  TestLargeEnumValue(const TestLargeEnumValue& from);

  inline TestLargeEnumValue& operator=(const TestLargeEnumValue& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TestLargeEnumValue& default_instance();

  void Swap(TestLargeEnumValue* other);

  // implements Message ----------------------------------------------

  inline TestLargeEnumValue* New() const { return New(NULL); }

  TestLargeEnumValue* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TestLargeEnumValue& from);
  void MergeFrom(const TestLargeEnumValue& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(TestLargeEnumValue* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef TestLargeEnumValue_EnumWithLargeValue EnumWithLargeValue;
  static const EnumWithLargeValue VALUE_1 =
    TestLargeEnumValue_EnumWithLargeValue_VALUE_1;
  static const EnumWithLargeValue VALUE_MAX =
    TestLargeEnumValue_EnumWithLargeValue_VALUE_MAX;
  static inline bool EnumWithLargeValue_IsValid(int value) {
    return TestLargeEnumValue_EnumWithLargeValue_IsValid(value);
  }
  static const EnumWithLargeValue EnumWithLargeValue_MIN =
    TestLargeEnumValue_EnumWithLargeValue_EnumWithLargeValue_MIN;
  static const EnumWithLargeValue EnumWithLargeValue_MAX =
    TestLargeEnumValue_EnumWithLargeValue_EnumWithLargeValue_MAX;
  static inline const ::google::protobuf::EnumDescriptor*
  EnumWithLargeValue_descriptor() {
    return TestLargeEnumValue_EnumWithLargeValue_descriptor();
  }
  static inline const ::std::string& EnumWithLargeValue_Name(EnumWithLargeValue value) {
    return TestLargeEnumValue_EnumWithLargeValue_Name(value);
  }
  static inline bool EnumWithLargeValue_Parse(const ::std::string& name,
      EnumWithLargeValue* value) {
    return TestLargeEnumValue_EnumWithLargeValue_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:protobuf_unittest.TestLargeEnumValue)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_google_2fprotobuf_2fcompiler_2fcpp_2fcpp_5ftest_5flarge_5fenum_5fvalue_2eproto();
  friend void protobuf_AssignDesc_google_2fprotobuf_2fcompiler_2fcpp_2fcpp_5ftest_5flarge_5fenum_5fvalue_2eproto();
  friend void protobuf_ShutdownFile_google_2fprotobuf_2fcompiler_2fcpp_2fcpp_5ftest_5flarge_5fenum_5fvalue_2eproto();

  void InitAsDefaultInstance();
  static TestLargeEnumValue* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// TestLargeEnumValue

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf_unittest

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::protobuf_unittest::TestLargeEnumValue_EnumWithLargeValue> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::protobuf_unittest::TestLargeEnumValue_EnumWithLargeValue>() {
  return ::protobuf_unittest::TestLargeEnumValue_EnumWithLargeValue_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_google_2fprotobuf_2fcompiler_2fcpp_2fcpp_5ftest_5flarge_5fenum_5fvalue_2eproto__INCLUDED
