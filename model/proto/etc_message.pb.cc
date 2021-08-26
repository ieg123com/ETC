// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: etc_message.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "etc_message.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace Model {

namespace {

const ::google::protobuf::Descriptor* MessageHead_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MessageHead_reflection_ = NULL;
const ::google::protobuf::Descriptor* TestRequest_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TestRequest_reflection_ = NULL;
const ::google::protobuf::Descriptor* TestResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TestResponse_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_etc_5fmessage_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_etc_5fmessage_2eproto() {
  protobuf_AddDesc_etc_5fmessage_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "etc_message.proto");
  GOOGLE_CHECK(file != NULL);
  MessageHead_descriptor_ = file->message_type(0);
  static const int MessageHead_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHead, rpcid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHead, error_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHead, message_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHead, actorid_),
  };
  MessageHead_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      MessageHead_descriptor_,
      MessageHead::default_instance_,
      MessageHead_offsets_,
      -1,
      -1,
      -1,
      sizeof(MessageHead),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHead, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHead, _is_default_instance_));
  TestRequest_descriptor_ = file->message_type(1);
  static const int TestRequest_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestRequest, a_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestRequest, b_),
  };
  TestRequest_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      TestRequest_descriptor_,
      TestRequest::default_instance_,
      TestRequest_offsets_,
      -1,
      -1,
      -1,
      sizeof(TestRequest),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestRequest, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestRequest, _is_default_instance_));
  TestResponse_descriptor_ = file->message_type(2);
  static const int TestResponse_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestResponse, sum_),
  };
  TestResponse_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      TestResponse_descriptor_,
      TestResponse::default_instance_,
      TestResponse_offsets_,
      -1,
      -1,
      -1,
      sizeof(TestResponse),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestResponse, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestResponse, _is_default_instance_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_etc_5fmessage_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      MessageHead_descriptor_, &MessageHead::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      TestRequest_descriptor_, &TestRequest::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      TestResponse_descriptor_, &TestResponse::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_etc_5fmessage_2eproto() {
  delete MessageHead::default_instance_;
  delete MessageHead_reflection_;
  delete TestRequest::default_instance_;
  delete TestRequest_reflection_;
  delete TestResponse::default_instance_;
  delete TestResponse_reflection_;
}

void protobuf_AddDesc_etc_5fmessage_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_etc_5fmessage_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\021etc_message.proto\022\005Model\"M\n\013MessageHea"
    "d\022\r\n\005RpcId\030Z \001(\005\022\r\n\005Error\030[ \001(\005\022\017\n\007Messa"
    "ge\030\\ \001(\t\022\017\n\007ActorId\030] \001(\003\"#\n\013TestRequest"
    "\022\t\n\001A\030\001 \001(\005\022\t\n\001B\030\002 \001(\005\"\033\n\014TestResponse\022\013"
    "\n\003Sum\030\001 \001(\005b\006proto3", 179);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "etc_message.proto", &protobuf_RegisterTypes);
  MessageHead::default_instance_ = new MessageHead();
  TestRequest::default_instance_ = new TestRequest();
  TestResponse::default_instance_ = new TestResponse();
  MessageHead::default_instance_->InitAsDefaultInstance();
  TestRequest::default_instance_->InitAsDefaultInstance();
  TestResponse::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_etc_5fmessage_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_etc_5fmessage_2eproto {
  StaticDescriptorInitializer_etc_5fmessage_2eproto() {
    protobuf_AddDesc_etc_5fmessage_2eproto();
  }
} static_descriptor_initializer_etc_5fmessage_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int MessageHead::kRpcIdFieldNumber;
const int MessageHead::kErrorFieldNumber;
const int MessageHead::kMessageFieldNumber;
const int MessageHead::kActorIdFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

MessageHead::MessageHead()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Model.MessageHead)
}

void MessageHead::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

MessageHead::MessageHead(const MessageHead& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Model.MessageHead)
}

void MessageHead::SharedCtor() {
    _is_default_instance_ = false;
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  rpcid_ = 0;
  error_ = 0;
  message_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  actorid_ = GOOGLE_LONGLONG(0);
}

MessageHead::~MessageHead() {
  // @@protoc_insertion_point(destructor:Model.MessageHead)
  SharedDtor();
}

void MessageHead::SharedDtor() {
  message_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void MessageHead::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MessageHead::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MessageHead_descriptor_;
}

const MessageHead& MessageHead::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_etc_5fmessage_2eproto();
  return *default_instance_;
}

MessageHead* MessageHead::default_instance_ = NULL;

MessageHead* MessageHead::New(::google::protobuf::Arena* arena) const {
  MessageHead* n = new MessageHead;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void MessageHead::Clear() {
// @@protoc_insertion_point(message_clear_start:Model.MessageHead)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(MessageHead, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<MessageHead*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  ZR_(rpcid_, error_);
  message_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  actorid_ = GOOGLE_LONGLONG(0);

#undef ZR_HELPER_
#undef ZR_

}

bool MessageHead::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Model.MessageHead)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(16383);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 RpcId = 90;
      case 90: {
        if (tag == 720) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &rpcid_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(728)) goto parse_Error;
        break;
      }

      // optional int32 Error = 91;
      case 91: {
        if (tag == 728) {
         parse_Error:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &error_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(738)) goto parse_Message;
        break;
      }

      // optional string Message = 92;
      case 92: {
        if (tag == 738) {
         parse_Message:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_message()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->message().data(), this->message().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "Model.MessageHead.Message"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(744)) goto parse_ActorId;
        break;
      }

      // optional int64 ActorId = 93;
      case 93: {
        if (tag == 744) {
         parse_ActorId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &actorid_)));

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
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Model.MessageHead)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Model.MessageHead)
  return false;
#undef DO_
}

void MessageHead::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Model.MessageHead)
  // optional int32 RpcId = 90;
  if (this->rpcid() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(90, this->rpcid(), output);
  }

  // optional int32 Error = 91;
  if (this->error() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(91, this->error(), output);
  }

  // optional string Message = 92;
  if (this->message().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->message().data(), this->message().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Model.MessageHead.Message");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      92, this->message(), output);
  }

  // optional int64 ActorId = 93;
  if (this->actorid() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(93, this->actorid(), output);
  }

  // @@protoc_insertion_point(serialize_end:Model.MessageHead)
}

::google::protobuf::uint8* MessageHead::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:Model.MessageHead)
  // optional int32 RpcId = 90;
  if (this->rpcid() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(90, this->rpcid(), target);
  }

  // optional int32 Error = 91;
  if (this->error() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(91, this->error(), target);
  }

  // optional string Message = 92;
  if (this->message().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->message().data(), this->message().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "Model.MessageHead.Message");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        92, this->message(), target);
  }

  // optional int64 ActorId = 93;
  if (this->actorid() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(93, this->actorid(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:Model.MessageHead)
  return target;
}

int MessageHead::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:Model.MessageHead)
  int total_size = 0;

  // optional int32 RpcId = 90;
  if (this->rpcid() != 0) {
    total_size += 2 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->rpcid());
  }

  // optional int32 Error = 91;
  if (this->error() != 0) {
    total_size += 2 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->error());
  }

  // optional string Message = 92;
  if (this->message().size() > 0) {
    total_size += 2 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->message());
  }

  // optional int64 ActorId = 93;
  if (this->actorid() != 0) {
    total_size += 2 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->actorid());
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MessageHead::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Model.MessageHead)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const MessageHead* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const MessageHead>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Model.MessageHead)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Model.MessageHead)
    MergeFrom(*source);
  }
}

void MessageHead::MergeFrom(const MessageHead& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Model.MessageHead)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from.rpcid() != 0) {
    set_rpcid(from.rpcid());
  }
  if (from.error() != 0) {
    set_error(from.error());
  }
  if (from.message().size() > 0) {

    message_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.message_);
  }
  if (from.actorid() != 0) {
    set_actorid(from.actorid());
  }
}

void MessageHead::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Model.MessageHead)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MessageHead::CopyFrom(const MessageHead& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Model.MessageHead)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MessageHead::IsInitialized() const {

  return true;
}

void MessageHead::Swap(MessageHead* other) {
  if (other == this) return;
  InternalSwap(other);
}
void MessageHead::InternalSwap(MessageHead* other) {
  std::swap(rpcid_, other->rpcid_);
  std::swap(error_, other->error_);
  message_.Swap(&other->message_);
  std::swap(actorid_, other->actorid_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata MessageHead::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MessageHead_descriptor_;
  metadata.reflection = MessageHead_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// MessageHead

// optional int32 RpcId = 90;
void MessageHead::clear_rpcid() {
  rpcid_ = 0;
}
 ::google::protobuf::int32 MessageHead::rpcid() const {
  // @@protoc_insertion_point(field_get:Model.MessageHead.RpcId)
  return rpcid_;
}
 void MessageHead::set_rpcid(::google::protobuf::int32 value) {
  
  rpcid_ = value;
  // @@protoc_insertion_point(field_set:Model.MessageHead.RpcId)
}

// optional int32 Error = 91;
void MessageHead::clear_error() {
  error_ = 0;
}
 ::google::protobuf::int32 MessageHead::error() const {
  // @@protoc_insertion_point(field_get:Model.MessageHead.Error)
  return error_;
}
 void MessageHead::set_error(::google::protobuf::int32 value) {
  
  error_ = value;
  // @@protoc_insertion_point(field_set:Model.MessageHead.Error)
}

// optional string Message = 92;
void MessageHead::clear_message() {
  message_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& MessageHead::message() const {
  // @@protoc_insertion_point(field_get:Model.MessageHead.Message)
  return message_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void MessageHead::set_message(const ::std::string& value) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Model.MessageHead.Message)
}
 void MessageHead::set_message(const char* value) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Model.MessageHead.Message)
}
 void MessageHead::set_message(const char* value, size_t size) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Model.MessageHead.Message)
}
 ::std::string* MessageHead::mutable_message() {
  
  // @@protoc_insertion_point(field_mutable:Model.MessageHead.Message)
  return message_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* MessageHead::release_message() {
  // @@protoc_insertion_point(field_release:Model.MessageHead.Message)
  
  return message_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void MessageHead::set_allocated_message(::std::string* message) {
  if (message != NULL) {
    
  } else {
    
  }
  message_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), message);
  // @@protoc_insertion_point(field_set_allocated:Model.MessageHead.Message)
}

// optional int64 ActorId = 93;
void MessageHead::clear_actorid() {
  actorid_ = GOOGLE_LONGLONG(0);
}
 ::google::protobuf::int64 MessageHead::actorid() const {
  // @@protoc_insertion_point(field_get:Model.MessageHead.ActorId)
  return actorid_;
}
 void MessageHead::set_actorid(::google::protobuf::int64 value) {
  
  actorid_ = value;
  // @@protoc_insertion_point(field_set:Model.MessageHead.ActorId)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int TestRequest::kAFieldNumber;
const int TestRequest::kBFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

TestRequest::TestRequest()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Model.TestRequest)
}

void TestRequest::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

TestRequest::TestRequest(const TestRequest& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Model.TestRequest)
}

void TestRequest::SharedCtor() {
    _is_default_instance_ = false;
  _cached_size_ = 0;
  a_ = 0;
  b_ = 0;
}

TestRequest::~TestRequest() {
  // @@protoc_insertion_point(destructor:Model.TestRequest)
  SharedDtor();
}

void TestRequest::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TestRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TestRequest::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TestRequest_descriptor_;
}

const TestRequest& TestRequest::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_etc_5fmessage_2eproto();
  return *default_instance_;
}

TestRequest* TestRequest::default_instance_ = NULL;

TestRequest* TestRequest::New(::google::protobuf::Arena* arena) const {
  TestRequest* n = new TestRequest;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void TestRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:Model.TestRequest)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(TestRequest, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<TestRequest*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  ZR_(a_, b_);

#undef ZR_HELPER_
#undef ZR_

}

bool TestRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Model.TestRequest)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 A = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &a_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_B;
        break;
      }

      // optional int32 B = 2;
      case 2: {
        if (tag == 16) {
         parse_B:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &b_)));

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
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Model.TestRequest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Model.TestRequest)
  return false;
#undef DO_
}

void TestRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Model.TestRequest)
  // optional int32 A = 1;
  if (this->a() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->a(), output);
  }

  // optional int32 B = 2;
  if (this->b() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->b(), output);
  }

  // @@protoc_insertion_point(serialize_end:Model.TestRequest)
}

::google::protobuf::uint8* TestRequest::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:Model.TestRequest)
  // optional int32 A = 1;
  if (this->a() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->a(), target);
  }

  // optional int32 B = 2;
  if (this->b() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->b(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:Model.TestRequest)
  return target;
}

int TestRequest::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:Model.TestRequest)
  int total_size = 0;

  // optional int32 A = 1;
  if (this->a() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->a());
  }

  // optional int32 B = 2;
  if (this->b() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->b());
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void TestRequest::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Model.TestRequest)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const TestRequest* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const TestRequest>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Model.TestRequest)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Model.TestRequest)
    MergeFrom(*source);
  }
}

void TestRequest::MergeFrom(const TestRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Model.TestRequest)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from.a() != 0) {
    set_a(from.a());
  }
  if (from.b() != 0) {
    set_b(from.b());
  }
}

void TestRequest::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Model.TestRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TestRequest::CopyFrom(const TestRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Model.TestRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TestRequest::IsInitialized() const {

  return true;
}

void TestRequest::Swap(TestRequest* other) {
  if (other == this) return;
  InternalSwap(other);
}
void TestRequest::InternalSwap(TestRequest* other) {
  std::swap(a_, other->a_);
  std::swap(b_, other->b_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata TestRequest::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TestRequest_descriptor_;
  metadata.reflection = TestRequest_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// TestRequest

// optional int32 A = 1;
void TestRequest::clear_a() {
  a_ = 0;
}
 ::google::protobuf::int32 TestRequest::a() const {
  // @@protoc_insertion_point(field_get:Model.TestRequest.A)
  return a_;
}
 void TestRequest::set_a(::google::protobuf::int32 value) {
  
  a_ = value;
  // @@protoc_insertion_point(field_set:Model.TestRequest.A)
}

// optional int32 B = 2;
void TestRequest::clear_b() {
  b_ = 0;
}
 ::google::protobuf::int32 TestRequest::b() const {
  // @@protoc_insertion_point(field_get:Model.TestRequest.B)
  return b_;
}
 void TestRequest::set_b(::google::protobuf::int32 value) {
  
  b_ = value;
  // @@protoc_insertion_point(field_set:Model.TestRequest.B)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int TestResponse::kSumFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

TestResponse::TestResponse()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Model.TestResponse)
}

void TestResponse::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

TestResponse::TestResponse(const TestResponse& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Model.TestResponse)
}

void TestResponse::SharedCtor() {
    _is_default_instance_ = false;
  _cached_size_ = 0;
  sum_ = 0;
}

TestResponse::~TestResponse() {
  // @@protoc_insertion_point(destructor:Model.TestResponse)
  SharedDtor();
}

void TestResponse::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TestResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TestResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TestResponse_descriptor_;
}

const TestResponse& TestResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_etc_5fmessage_2eproto();
  return *default_instance_;
}

TestResponse* TestResponse::default_instance_ = NULL;

TestResponse* TestResponse::New(::google::protobuf::Arena* arena) const {
  TestResponse* n = new TestResponse;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void TestResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:Model.TestResponse)
  sum_ = 0;
}

bool TestResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Model.TestResponse)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 Sum = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &sum_)));

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
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Model.TestResponse)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Model.TestResponse)
  return false;
#undef DO_
}

void TestResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Model.TestResponse)
  // optional int32 Sum = 1;
  if (this->sum() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->sum(), output);
  }

  // @@protoc_insertion_point(serialize_end:Model.TestResponse)
}

::google::protobuf::uint8* TestResponse::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:Model.TestResponse)
  // optional int32 Sum = 1;
  if (this->sum() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->sum(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:Model.TestResponse)
  return target;
}

int TestResponse::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:Model.TestResponse)
  int total_size = 0;

  // optional int32 Sum = 1;
  if (this->sum() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->sum());
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void TestResponse::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Model.TestResponse)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const TestResponse* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const TestResponse>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Model.TestResponse)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Model.TestResponse)
    MergeFrom(*source);
  }
}

void TestResponse::MergeFrom(const TestResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Model.TestResponse)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from.sum() != 0) {
    set_sum(from.sum());
  }
}

void TestResponse::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Model.TestResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TestResponse::CopyFrom(const TestResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Model.TestResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TestResponse::IsInitialized() const {

  return true;
}

void TestResponse::Swap(TestResponse* other) {
  if (other == this) return;
  InternalSwap(other);
}
void TestResponse::InternalSwap(TestResponse* other) {
  std::swap(sum_, other->sum_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata TestResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TestResponse_descriptor_;
  metadata.reflection = TestResponse_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// TestResponse

// optional int32 Sum = 1;
void TestResponse::clear_sum() {
  sum_ = 0;
}
 ::google::protobuf::int32 TestResponse::sum() const {
  // @@protoc_insertion_point(field_get:Model.TestResponse.Sum)
  return sum_;
}
 void TestResponse::set_sum(::google::protobuf::int32 value) {
  
  sum_ = value;
  // @@protoc_insertion_point(field_set:Model.TestResponse.Sum)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Model

// @@protoc_insertion_point(global_scope)