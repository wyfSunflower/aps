// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: graph.proto

#include "graph.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace graph {
PROTOBUF_CONSTEXPR edge::edge(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.x_)*/{}
  , /*decltype(_impl_._x_cached_byte_size_)*/{0}
  , /*decltype(_impl_.y_)*/{}
  , /*decltype(_impl_._y_cached_byte_size_)*/{0}
  , /*decltype(_impl_.z_)*/{}
  , /*decltype(_impl_._z_cached_byte_size_)*/{0}
  , /*decltype(_impl_.edgeid_)*/0u
  , /*decltype(_impl_.startid_)*/0u
  , /*decltype(_impl_.endid_)*/0u
  , /*decltype(_impl_.zsame_)*/0
  , /*decltype(_impl_.type_)*/0u
  , /*decltype(_impl_.theta1_)*/0
  , /*decltype(_impl_.theta2_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct edgeDefaultTypeInternal {
  PROTOBUF_CONSTEXPR edgeDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~edgeDefaultTypeInternal() {}
  union {
    edge _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 edgeDefaultTypeInternal _edge_default_instance_;
PROTOBUF_CONSTEXPR vertex::vertex(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.e_)*/{}
  , /*decltype(_impl_.id_)*/0u
  , /*decltype(_impl_.x_)*/0
  , /*decltype(_impl_.y_)*/0
  , /*decltype(_impl_.z_)*/0
  , /*decltype(_impl_.layerid_)*/0u
  , /*decltype(_impl_.type_)*/0u
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct vertexDefaultTypeInternal {
  PROTOBUF_CONSTEXPR vertexDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~vertexDefaultTypeInternal() {}
  union {
    vertex _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 vertexDefaultTypeInternal _vertex_default_instance_;
}  // namespace graph
static ::_pb::Metadata file_level_metadata_graph_2eproto[2];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_graph_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_graph_2eproto = nullptr;

const uint32_t TableStruct_graph_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::graph::edge, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::graph::edge, _impl_.edgeid_),
  PROTOBUF_FIELD_OFFSET(::graph::edge, _impl_.startid_),
  PROTOBUF_FIELD_OFFSET(::graph::edge, _impl_.endid_),
  PROTOBUF_FIELD_OFFSET(::graph::edge, _impl_.x_),
  PROTOBUF_FIELD_OFFSET(::graph::edge, _impl_.y_),
  PROTOBUF_FIELD_OFFSET(::graph::edge, _impl_.z_),
  PROTOBUF_FIELD_OFFSET(::graph::edge, _impl_.zsame_),
  PROTOBUF_FIELD_OFFSET(::graph::edge, _impl_.type_),
  PROTOBUF_FIELD_OFFSET(::graph::edge, _impl_.theta1_),
  PROTOBUF_FIELD_OFFSET(::graph::edge, _impl_.theta2_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::graph::vertex, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::graph::vertex, _impl_.id_),
  PROTOBUF_FIELD_OFFSET(::graph::vertex, _impl_.x_),
  PROTOBUF_FIELD_OFFSET(::graph::vertex, _impl_.y_),
  PROTOBUF_FIELD_OFFSET(::graph::vertex, _impl_.z_),
  PROTOBUF_FIELD_OFFSET(::graph::vertex, _impl_.layerid_),
  PROTOBUF_FIELD_OFFSET(::graph::vertex, _impl_.type_),
  PROTOBUF_FIELD_OFFSET(::graph::vertex, _impl_.e_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::graph::edge)},
  { 16, -1, -1, sizeof(::graph::vertex)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::graph::_edge_default_instance_._instance,
  &::graph::_vertex_default_instance_._instance,
};

const char descriptor_table_protodef_graph_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\013graph.proto\022\005graph\"\224\001\n\004edge\022\016\n\006edgeid\030"
  "\001 \001(\r\022\017\n\007startid\030\002 \001(\r\022\r\n\005endid\030\003 \001(\r\022\t\n"
  "\001x\030\004 \003(\005\022\t\n\001y\030\005 \003(\005\022\t\n\001z\030\006 \003(\005\022\r\n\005zsame\030"
  "\007 \001(\005\022\014\n\004type\030\010 \001(\r\022\016\n\006theta1\030\t \001(\005\022\016\n\006t"
  "heta2\030\n \001(\005\"l\n\006vertex\022\n\n\002id\030\001 \001(\r\022\t\n\001x\030\002"
  " \001(\005\022\t\n\001y\030\003 \001(\005\022\t\n\001z\030\004 \001(\005\022\017\n\007layerid\030\005 "
  "\001(\r\022\014\n\004type\030\006 \001(\r\022\026\n\001e\030\007 \003(\0132\013.graph.edg"
  "eb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_graph_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_graph_2eproto = {
    false, false, 289, descriptor_table_protodef_graph_2eproto,
    "graph.proto",
    &descriptor_table_graph_2eproto_once, nullptr, 0, 2,
    schemas, file_default_instances, TableStruct_graph_2eproto::offsets,
    file_level_metadata_graph_2eproto, file_level_enum_descriptors_graph_2eproto,
    file_level_service_descriptors_graph_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_graph_2eproto_getter() {
  return &descriptor_table_graph_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_graph_2eproto(&descriptor_table_graph_2eproto);
namespace graph {

// ===================================================================

class edge::_Internal {
 public:
};

edge::edge(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:graph.edge)
}
edge::edge(const edge& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  edge* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.x_){from._impl_.x_}
    , /*decltype(_impl_._x_cached_byte_size_)*/{0}
    , decltype(_impl_.y_){from._impl_.y_}
    , /*decltype(_impl_._y_cached_byte_size_)*/{0}
    , decltype(_impl_.z_){from._impl_.z_}
    , /*decltype(_impl_._z_cached_byte_size_)*/{0}
    , decltype(_impl_.edgeid_){}
    , decltype(_impl_.startid_){}
    , decltype(_impl_.endid_){}
    , decltype(_impl_.zsame_){}
    , decltype(_impl_.type_){}
    , decltype(_impl_.theta1_){}
    , decltype(_impl_.theta2_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.edgeid_, &from._impl_.edgeid_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.theta2_) -
    reinterpret_cast<char*>(&_impl_.edgeid_)) + sizeof(_impl_.theta2_));
  // @@protoc_insertion_point(copy_constructor:graph.edge)
}

inline void edge::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.x_){arena}
    , /*decltype(_impl_._x_cached_byte_size_)*/{0}
    , decltype(_impl_.y_){arena}
    , /*decltype(_impl_._y_cached_byte_size_)*/{0}
    , decltype(_impl_.z_){arena}
    , /*decltype(_impl_._z_cached_byte_size_)*/{0}
    , decltype(_impl_.edgeid_){0u}
    , decltype(_impl_.startid_){0u}
    , decltype(_impl_.endid_){0u}
    , decltype(_impl_.zsame_){0}
    , decltype(_impl_.type_){0u}
    , decltype(_impl_.theta1_){0}
    , decltype(_impl_.theta2_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

edge::~edge() {
  // @@protoc_insertion_point(destructor:graph.edge)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void edge::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.x_.~RepeatedField();
  _impl_.y_.~RepeatedField();
  _impl_.z_.~RepeatedField();
}

void edge::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void edge::Clear() {
// @@protoc_insertion_point(message_clear_start:graph.edge)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.x_.Clear();
  _impl_.y_.Clear();
  _impl_.z_.Clear();
  ::memset(&_impl_.edgeid_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.theta2_) -
      reinterpret_cast<char*>(&_impl_.edgeid_)) + sizeof(_impl_.theta2_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* edge::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint32 edgeid = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.edgeid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 startid = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.startid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 endid = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          _impl_.endid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated int32 x = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 34)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedInt32Parser(_internal_mutable_x(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 32) {
          _internal_add_x(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated int32 y = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 42)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedInt32Parser(_internal_mutable_y(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 40) {
          _internal_add_y(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated int32 z = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 50)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedInt32Parser(_internal_mutable_z(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 48) {
          _internal_add_z(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 zsame = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 56)) {
          _impl_.zsame_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 type = 8;
      case 8:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 64)) {
          _impl_.type_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 theta1 = 9;
      case 9:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 72)) {
          _impl_.theta1_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 theta2 = 10;
      case 10:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 80)) {
          _impl_.theta2_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* edge::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:graph.edge)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 edgeid = 1;
  if (this->_internal_edgeid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(1, this->_internal_edgeid(), target);
  }

  // uint32 startid = 2;
  if (this->_internal_startid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(2, this->_internal_startid(), target);
  }

  // uint32 endid = 3;
  if (this->_internal_endid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(3, this->_internal_endid(), target);
  }

  // repeated int32 x = 4;
  {
    int byte_size = _impl_._x_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteInt32Packed(
          4, _internal_x(), byte_size, target);
    }
  }

  // repeated int32 y = 5;
  {
    int byte_size = _impl_._y_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteInt32Packed(
          5, _internal_y(), byte_size, target);
    }
  }

  // repeated int32 z = 6;
  {
    int byte_size = _impl_._z_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteInt32Packed(
          6, _internal_z(), byte_size, target);
    }
  }

  // int32 zsame = 7;
  if (this->_internal_zsame() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(7, this->_internal_zsame(), target);
  }

  // uint32 type = 8;
  if (this->_internal_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(8, this->_internal_type(), target);
  }

  // int32 theta1 = 9;
  if (this->_internal_theta1() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(9, this->_internal_theta1(), target);
  }

  // int32 theta2 = 10;
  if (this->_internal_theta2() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(10, this->_internal_theta2(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:graph.edge)
  return target;
}

size_t edge::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:graph.edge)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated int32 x = 4;
  {
    size_t data_size = ::_pbi::WireFormatLite::
      Int32Size(this->_impl_.x_);
    if (data_size > 0) {
      total_size += 1 +
        ::_pbi::WireFormatLite::Int32Size(static_cast<int32_t>(data_size));
    }
    int cached_size = ::_pbi::ToCachedSize(data_size);
    _impl_._x_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  // repeated int32 y = 5;
  {
    size_t data_size = ::_pbi::WireFormatLite::
      Int32Size(this->_impl_.y_);
    if (data_size > 0) {
      total_size += 1 +
        ::_pbi::WireFormatLite::Int32Size(static_cast<int32_t>(data_size));
    }
    int cached_size = ::_pbi::ToCachedSize(data_size);
    _impl_._y_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  // repeated int32 z = 6;
  {
    size_t data_size = ::_pbi::WireFormatLite::
      Int32Size(this->_impl_.z_);
    if (data_size > 0) {
      total_size += 1 +
        ::_pbi::WireFormatLite::Int32Size(static_cast<int32_t>(data_size));
    }
    int cached_size = ::_pbi::ToCachedSize(data_size);
    _impl_._z_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  // uint32 edgeid = 1;
  if (this->_internal_edgeid() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_edgeid());
  }

  // uint32 startid = 2;
  if (this->_internal_startid() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_startid());
  }

  // uint32 endid = 3;
  if (this->_internal_endid() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_endid());
  }

  // int32 zsame = 7;
  if (this->_internal_zsame() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_zsame());
  }

  // uint32 type = 8;
  if (this->_internal_type() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_type());
  }

  // int32 theta1 = 9;
  if (this->_internal_theta1() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_theta1());
  }

  // int32 theta2 = 10;
  if (this->_internal_theta2() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_theta2());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData edge::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    edge::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*edge::GetClassData() const { return &_class_data_; }


void edge::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<edge*>(&to_msg);
  auto& from = static_cast<const edge&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:graph.edge)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.x_.MergeFrom(from._impl_.x_);
  _this->_impl_.y_.MergeFrom(from._impl_.y_);
  _this->_impl_.z_.MergeFrom(from._impl_.z_);
  if (from._internal_edgeid() != 0) {
    _this->_internal_set_edgeid(from._internal_edgeid());
  }
  if (from._internal_startid() != 0) {
    _this->_internal_set_startid(from._internal_startid());
  }
  if (from._internal_endid() != 0) {
    _this->_internal_set_endid(from._internal_endid());
  }
  if (from._internal_zsame() != 0) {
    _this->_internal_set_zsame(from._internal_zsame());
  }
  if (from._internal_type() != 0) {
    _this->_internal_set_type(from._internal_type());
  }
  if (from._internal_theta1() != 0) {
    _this->_internal_set_theta1(from._internal_theta1());
  }
  if (from._internal_theta2() != 0) {
    _this->_internal_set_theta2(from._internal_theta2());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void edge::CopyFrom(const edge& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:graph.edge)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool edge::IsInitialized() const {
  return true;
}

void edge::InternalSwap(edge* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.x_.InternalSwap(&other->_impl_.x_);
  _impl_.y_.InternalSwap(&other->_impl_.y_);
  _impl_.z_.InternalSwap(&other->_impl_.z_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(edge, _impl_.theta2_)
      + sizeof(edge::_impl_.theta2_)
      - PROTOBUF_FIELD_OFFSET(edge, _impl_.edgeid_)>(
          reinterpret_cast<char*>(&_impl_.edgeid_),
          reinterpret_cast<char*>(&other->_impl_.edgeid_));
}

::PROTOBUF_NAMESPACE_ID::Metadata edge::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_graph_2eproto_getter, &descriptor_table_graph_2eproto_once,
      file_level_metadata_graph_2eproto[0]);
}

// ===================================================================

class vertex::_Internal {
 public:
};

vertex::vertex(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:graph.vertex)
}
vertex::vertex(const vertex& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  vertex* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.e_){from._impl_.e_}
    , decltype(_impl_.id_){}
    , decltype(_impl_.x_){}
    , decltype(_impl_.y_){}
    , decltype(_impl_.z_){}
    , decltype(_impl_.layerid_){}
    , decltype(_impl_.type_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.id_, &from._impl_.id_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.type_) -
    reinterpret_cast<char*>(&_impl_.id_)) + sizeof(_impl_.type_));
  // @@protoc_insertion_point(copy_constructor:graph.vertex)
}

inline void vertex::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.e_){arena}
    , decltype(_impl_.id_){0u}
    , decltype(_impl_.x_){0}
    , decltype(_impl_.y_){0}
    , decltype(_impl_.z_){0}
    , decltype(_impl_.layerid_){0u}
    , decltype(_impl_.type_){0u}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

vertex::~vertex() {
  // @@protoc_insertion_point(destructor:graph.vertex)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void vertex::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.e_.~RepeatedPtrField();
}

void vertex::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void vertex::Clear() {
// @@protoc_insertion_point(message_clear_start:graph.vertex)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.e_.Clear();
  ::memset(&_impl_.id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.type_) -
      reinterpret_cast<char*>(&_impl_.id_)) + sizeof(_impl_.type_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* vertex::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint32 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 x = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.x_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 y = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          _impl_.y_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 z = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _impl_.z_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 layerid = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 40)) {
          _impl_.layerid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 type = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 48)) {
          _impl_.type_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated .graph.edge e = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 58)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_e(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<58>(ptr));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* vertex::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:graph.vertex)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 id = 1;
  if (this->_internal_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(1, this->_internal_id(), target);
  }

  // int32 x = 2;
  if (this->_internal_x() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_x(), target);
  }

  // int32 y = 3;
  if (this->_internal_y() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(3, this->_internal_y(), target);
  }

  // int32 z = 4;
  if (this->_internal_z() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(4, this->_internal_z(), target);
  }

  // uint32 layerid = 5;
  if (this->_internal_layerid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(5, this->_internal_layerid(), target);
  }

  // uint32 type = 6;
  if (this->_internal_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(6, this->_internal_type(), target);
  }

  // repeated .graph.edge e = 7;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_e_size()); i < n; i++) {
    const auto& repfield = this->_internal_e(i);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessage(7, repfield, repfield.GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:graph.vertex)
  return target;
}

size_t vertex::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:graph.vertex)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .graph.edge e = 7;
  total_size += 1UL * this->_internal_e_size();
  for (const auto& msg : this->_impl_.e_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // uint32 id = 1;
  if (this->_internal_id() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_id());
  }

  // int32 x = 2;
  if (this->_internal_x() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_x());
  }

  // int32 y = 3;
  if (this->_internal_y() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_y());
  }

  // int32 z = 4;
  if (this->_internal_z() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_z());
  }

  // uint32 layerid = 5;
  if (this->_internal_layerid() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_layerid());
  }

  // uint32 type = 6;
  if (this->_internal_type() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData vertex::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    vertex::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*vertex::GetClassData() const { return &_class_data_; }


void vertex::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<vertex*>(&to_msg);
  auto& from = static_cast<const vertex&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:graph.vertex)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.e_.MergeFrom(from._impl_.e_);
  if (from._internal_id() != 0) {
    _this->_internal_set_id(from._internal_id());
  }
  if (from._internal_x() != 0) {
    _this->_internal_set_x(from._internal_x());
  }
  if (from._internal_y() != 0) {
    _this->_internal_set_y(from._internal_y());
  }
  if (from._internal_z() != 0) {
    _this->_internal_set_z(from._internal_z());
  }
  if (from._internal_layerid() != 0) {
    _this->_internal_set_layerid(from._internal_layerid());
  }
  if (from._internal_type() != 0) {
    _this->_internal_set_type(from._internal_type());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void vertex::CopyFrom(const vertex& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:graph.vertex)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool vertex::IsInitialized() const {
  return true;
}

void vertex::InternalSwap(vertex* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.e_.InternalSwap(&other->_impl_.e_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(vertex, _impl_.type_)
      + sizeof(vertex::_impl_.type_)
      - PROTOBUF_FIELD_OFFSET(vertex, _impl_.id_)>(
          reinterpret_cast<char*>(&_impl_.id_),
          reinterpret_cast<char*>(&other->_impl_.id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata vertex::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_graph_2eproto_getter, &descriptor_table_graph_2eproto_once,
      file_level_metadata_graph_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace graph
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::graph::edge*
Arena::CreateMaybeMessage< ::graph::edge >(Arena* arena) {
  return Arena::CreateMessageInternal< ::graph::edge >(arena);
}
template<> PROTOBUF_NOINLINE ::graph::vertex*
Arena::CreateMaybeMessage< ::graph::vertex >(Arena* arena) {
  return Arena::CreateMessageInternal< ::graph::vertex >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
