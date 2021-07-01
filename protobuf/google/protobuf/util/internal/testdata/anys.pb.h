// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/util/internal/testdata/anys.proto

#ifndef PROTOBUF_google_2fprotobuf_2futil_2finternal_2ftestdata_2fanys_2eproto__INCLUDED
#define PROTOBUF_google_2fprotobuf_2futil_2finternal_2ftestdata_2fanys_2eproto__INCLUDED

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
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/any.pb.h>
// @@protoc_insertion_point(includes)

namespace google {
namespace protobuf {
namespace testing {
namespace anys {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_google_2fprotobuf_2futil_2finternal_2ftestdata_2fanys_2eproto();
void protobuf_AssignDesc_google_2fprotobuf_2futil_2finternal_2ftestdata_2fanys_2eproto();
void protobuf_ShutdownFile_google_2fprotobuf_2futil_2finternal_2ftestdata_2fanys_2eproto();

class AnyIn;
class AnyM;
class AnyOut;

// ===================================================================

class AnyIn : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:google.protobuf.testing.anys.AnyIn) */ {
 public:
  AnyIn();
  virtual ~AnyIn();

  AnyIn(const AnyIn& from);

  inline AnyIn& operator=(const AnyIn& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const AnyIn& default_instance();

  void Swap(AnyIn* other);

  // implements Message ----------------------------------------------

  inline AnyIn* New() const { return New(NULL); }

  AnyIn* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AnyIn& from);
  void MergeFrom(const AnyIn& from);
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
  void InternalSwap(AnyIn* other);
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

  // accessors -------------------------------------------------------

  // optional string something = 1;
  void clear_something();
  static const int kSomethingFieldNumber = 1;
  const ::std::string& something() const;
  void set_something(const ::std::string& value);
  void set_something(const char* value);
  void set_something(const char* value, size_t size);
  ::std::string* mutable_something();
  ::std::string* release_something();
  void set_allocated_something(::std::string* something);

  // @@protoc_insertion_point(class_scope:google.protobuf.testing.anys.AnyIn)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr something_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_google_2fprotobuf_2futil_2finternal_2ftestdata_2fanys_2eproto();
  friend void protobuf_AssignDesc_google_2fprotobuf_2futil_2finternal_2ftestdata_2fanys_2eproto();
  friend void protobuf_ShutdownFile_google_2fprotobuf_2futil_2finternal_2ftestdata_2fanys_2eproto();

  void InitAsDefaultInstance();
  static AnyIn* default_instance_;
};
// -------------------------------------------------------------------

class AnyOut : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:google.protobuf.testing.anys.AnyOut) */ {
 public:
  AnyOut();
  virtual ~AnyOut();

  AnyOut(const AnyOut& from);

  inline AnyOut& operator=(const AnyOut& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const AnyOut& default_instance();

  void Swap(AnyOut* other);

  // implements Message ----------------------------------------------

  inline AnyOut* New() const { return New(NULL); }

  AnyOut* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AnyOut& from);
  void MergeFrom(const AnyOut& from);
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
  void InternalSwap(AnyOut* other);
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

  // accessors -------------------------------------------------------

  // optional .google.protobuf.Any any = 1;
  bool has_any() const;
  void clear_any();
  static const int kAnyFieldNumber = 1;
  const ::google::protobuf::Any& any() const;
  ::google::protobuf::Any* mutable_any();
  ::google::protobuf::Any* release_any();
  void set_allocated_any(::google::protobuf::Any* any);

  // @@protoc_insertion_point(class_scope:google.protobuf.testing.anys.AnyOut)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::Any* any_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_google_2fprotobuf_2futil_2finternal_2ftestdata_2fanys_2eproto();
  friend void protobuf_AssignDesc_google_2fprotobuf_2futil_2finternal_2ftestdata_2fanys_2eproto();
  friend void protobuf_ShutdownFile_google_2fprotobuf_2futil_2finternal_2ftestdata_2fanys_2eproto();

  void InitAsDefaultInstance();
  static AnyOut* default_instance_;
};
// -------------------------------------------------------------------

class AnyM : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:google.protobuf.testing.anys.AnyM) */ {
 public:
  AnyM();
  virtual ~AnyM();

  AnyM(const AnyM& from);

  inline AnyM& operator=(const AnyM& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const AnyM& default_instance();

  void Swap(AnyM* other);

  // implements Message ----------------------------------------------

  inline AnyM* New() const { return New(NULL); }

  AnyM* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AnyM& from);
  void MergeFrom(const AnyM& from);
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
  void InternalSwap(AnyM* other);
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

  // accessors -------------------------------------------------------

  // optional string foo = 1;
  void clear_foo();
  static const int kFooFieldNumber = 1;
  const ::std::string& foo() const;
  void set_foo(const ::std::string& value);
  void set_foo(const char* value);
  void set_foo(const char* value, size_t size);
  ::std::string* mutable_foo();
  ::std::string* release_foo();
  void set_allocated_foo(::std::string* foo);

  // @@protoc_insertion_point(class_scope:google.protobuf.testing.anys.AnyM)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr foo_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_google_2fprotobuf_2futil_2finternal_2ftestdata_2fanys_2eproto();
  friend void protobuf_AssignDesc_google_2fprotobuf_2futil_2finternal_2ftestdata_2fanys_2eproto();
  friend void protobuf_ShutdownFile_google_2fprotobuf_2futil_2finternal_2ftestdata_2fanys_2eproto();

  void InitAsDefaultInstance();
  static AnyM* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// AnyIn

// optional string something = 1;
inline void AnyIn::clear_something() {
  something_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& AnyIn::something() const {
  // @@protoc_insertion_point(field_get:google.protobuf.testing.anys.AnyIn.something)
  return something_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void AnyIn::set_something(const ::std::string& value) {
  
  something_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:google.protobuf.testing.anys.AnyIn.something)
}
inline void AnyIn::set_something(const char* value) {
  
  something_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:google.protobuf.testing.anys.AnyIn.something)
}
inline void AnyIn::set_something(const char* value, size_t size) {
  
  something_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:google.protobuf.testing.anys.AnyIn.something)
}
inline ::std::string* AnyIn::mutable_something() {
  
  // @@protoc_insertion_point(field_mutable:google.protobuf.testing.anys.AnyIn.something)
  return something_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* AnyIn::release_something() {
  // @@protoc_insertion_point(field_release:google.protobuf.testing.anys.AnyIn.something)
  
  return something_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void AnyIn::set_allocated_something(::std::string* something) {
  if (something != NULL) {
    
  } else {
    
  }
  something_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), something);
  // @@protoc_insertion_point(field_set_allocated:google.protobuf.testing.anys.AnyIn.something)
}

// -------------------------------------------------------------------

// AnyOut

// optional .google.protobuf.Any any = 1;
inline bool AnyOut::has_any() const {
  return !_is_default_instance_ && any_ != NULL;
}
inline void AnyOut::clear_any() {
  if (GetArenaNoVirtual() == NULL && any_ != NULL) delete any_;
  any_ = NULL;
}
inline const ::google::protobuf::Any& AnyOut::any() const {
  // @@protoc_insertion_point(field_get:google.protobuf.testing.anys.AnyOut.any)
  return any_ != NULL ? *any_ : *default_instance_->any_;
}
inline ::google::protobuf::Any* AnyOut::mutable_any() {
  
  if (any_ == NULL) {
    any_ = new ::google::protobuf::Any;
  }
  // @@protoc_insertion_point(field_mutable:google.protobuf.testing.anys.AnyOut.any)
  return any_;
}
inline ::google::protobuf::Any* AnyOut::release_any() {
  // @@protoc_insertion_point(field_release:google.protobuf.testing.anys.AnyOut.any)
  
  ::google::protobuf::Any* temp = any_;
  any_ = NULL;
  return temp;
}
inline void AnyOut::set_allocated_any(::google::protobuf::Any* any) {
  delete any_;
  any_ = any;
  if (any) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:google.protobuf.testing.anys.AnyOut.any)
}

// -------------------------------------------------------------------

// AnyM

// optional string foo = 1;
inline void AnyM::clear_foo() {
  foo_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& AnyM::foo() const {
  // @@protoc_insertion_point(field_get:google.protobuf.testing.anys.AnyM.foo)
  return foo_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void AnyM::set_foo(const ::std::string& value) {
  
  foo_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:google.protobuf.testing.anys.AnyM.foo)
}
inline void AnyM::set_foo(const char* value) {
  
  foo_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:google.protobuf.testing.anys.AnyM.foo)
}
inline void AnyM::set_foo(const char* value, size_t size) {
  
  foo_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:google.protobuf.testing.anys.AnyM.foo)
}
inline ::std::string* AnyM::mutable_foo() {
  
  // @@protoc_insertion_point(field_mutable:google.protobuf.testing.anys.AnyM.foo)
  return foo_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* AnyM::release_foo() {
  // @@protoc_insertion_point(field_release:google.protobuf.testing.anys.AnyM.foo)
  
  return foo_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void AnyM::set_allocated_foo(::std::string* foo) {
  if (foo != NULL) {
    
  } else {
    
  }
  foo_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), foo);
  // @@protoc_insertion_point(field_set_allocated:google.protobuf.testing.anys.AnyM.foo)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace anys
}  // namespace testing
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_google_2fprotobuf_2futil_2finternal_2ftestdata_2fanys_2eproto__INCLUDED
