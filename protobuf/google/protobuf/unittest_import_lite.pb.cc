// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_import_lite.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include <google/protobuf/unittest_import_lite.pb.h>

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// @@protoc_insertion_point(includes)

namespace protobuf_unittest_import {

void protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fimport_5flite_2eproto() {
  delete ImportMessageLite::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5flite_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5flite_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5flite_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  ::protobuf_unittest_import::protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5fpublic_5flite_2eproto();
  ImportMessageLite::default_instance_ = new ImportMessageLite();
  ImportMessageLite::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fimport_5flite_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5flite_2eproto_once_);
void protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5flite_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5flite_2eproto_once_,
                 &protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5flite_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_google_2fprotobuf_2funittest_5fimport_5flite_2eproto {
  StaticDescriptorInitializer_google_2fprotobuf_2funittest_5fimport_5flite_2eproto() {
    protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5flite_2eproto();
  }
} static_descriptor_initializer_google_2fprotobuf_2funittest_5fimport_5flite_2eproto_;
#endif
bool ImportEnumLite_IsValid(int value) {
  switch(value) {
    case 7:
    case 8:
    case 9:
      return true;
    default:
      return false;
  }
}


// ===================================================================

static ::std::string* MutableUnknownFieldsForImportMessageLite(
    ImportMessageLite* ptr) {
  return ptr->mutable_unknown_fields();
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ImportMessageLite::kDFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ImportMessageLite::ImportMessageLite()
  : ::google::protobuf::MessageLite(), _arena_ptr_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:protobuf_unittest_import.ImportMessageLite)
}

void ImportMessageLite::InitAsDefaultInstance() {
}

ImportMessageLite::ImportMessageLite(const ImportMessageLite& from)
  : ::google::protobuf::MessageLite(),
    _arena_ptr_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:protobuf_unittest_import.ImportMessageLite)
}

void ImportMessageLite::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  _unknown_fields_.UnsafeSetDefault(
      &::google::protobuf::internal::GetEmptyStringAlreadyInited());
  d_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ImportMessageLite::~ImportMessageLite() {
  // @@protoc_insertion_point(destructor:protobuf_unittest_import.ImportMessageLite)
  SharedDtor();
}

void ImportMessageLite::SharedDtor() {
  _unknown_fields_.DestroyNoArena(
      &::google::protobuf::internal::GetEmptyStringAlreadyInited());
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void ImportMessageLite::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ImportMessageLite& ImportMessageLite::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5flite_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_google_2fprotobuf_2funittest_5fimport_5flite_2eproto();
#endif
  return *default_instance_;
}

ImportMessageLite* ImportMessageLite::default_instance_ = NULL;

ImportMessageLite* ImportMessageLite::New(::google::protobuf::Arena* arena) const {
  ImportMessageLite* n = new ImportMessageLite;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void ImportMessageLite::Clear() {
// @@protoc_insertion_point(message_clear_start:protobuf_unittest_import.ImportMessageLite)
  d_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  _unknown_fields_.ClearToEmptyNoArena(
      &::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

bool ImportMessageLite::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  ::google::protobuf::io::LazyStringOutputStream unknown_fields_string(
      ::google::protobuf::internal::NewPermanentCallback(
          &MutableUnknownFieldsForImportMessageLite, this));
  ::google::protobuf::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_string, false);
  // @@protoc_insertion_point(parse_start:protobuf_unittest_import.ImportMessageLite)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 d = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &d_)));
          set_has_d();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(
            input, tag, &unknown_fields_stream));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:protobuf_unittest_import.ImportMessageLite)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:protobuf_unittest_import.ImportMessageLite)
  return false;
#undef DO_
}

void ImportMessageLite::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:protobuf_unittest_import.ImportMessageLite)
  // optional int32 d = 1;
  if (has_d()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->d(), output);
  }

  output->WriteRaw(unknown_fields().data(),
                   static_cast<int>(unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:protobuf_unittest_import.ImportMessageLite)
}

int ImportMessageLite::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:protobuf_unittest_import.ImportMessageLite)
  int total_size = 0;

  // optional int32 d = 1;
  if (has_d()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->d());
  }

  total_size += unknown_fields().size();

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ImportMessageLite::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const ImportMessageLite*>(&from));
}

void ImportMessageLite::MergeFrom(const ImportMessageLite& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:protobuf_unittest_import.ImportMessageLite)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_d()) {
      set_d(from.d());
    }
  }
  if (!from.unknown_fields().empty()) {
    mutable_unknown_fields()->append(from.unknown_fields());
  }
}

void ImportMessageLite::CopyFrom(const ImportMessageLite& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protobuf_unittest_import.ImportMessageLite)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ImportMessageLite::IsInitialized() const {

  return true;
}

void ImportMessageLite::Swap(ImportMessageLite* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ImportMessageLite::InternalSwap(ImportMessageLite* other) {
  std::swap(d_, other->d_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _unknown_fields_.Swap(&other->_unknown_fields_);
  std::swap(_cached_size_, other->_cached_size_);
}

::std::string ImportMessageLite::GetTypeName() const {
  return "protobuf_unittest_import.ImportMessageLite";
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// ImportMessageLite

// optional int32 d = 1;
bool ImportMessageLite::has_d() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void ImportMessageLite::set_has_d() {
  _has_bits_[0] |= 0x00000001u;
}
void ImportMessageLite::clear_has_d() {
  _has_bits_[0] &= ~0x00000001u;
}
void ImportMessageLite::clear_d() {
  d_ = 0;
  clear_has_d();
}
 ::google::protobuf::int32 ImportMessageLite::d() const {
  // @@protoc_insertion_point(field_get:protobuf_unittest_import.ImportMessageLite.d)
  return d_;
}
 void ImportMessageLite::set_d(::google::protobuf::int32 value) {
  set_has_d();
  d_ = value;
  // @@protoc_insertion_point(field_set:protobuf_unittest_import.ImportMessageLite.d)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf_unittest_import

// @@protoc_insertion_point(global_scope)
