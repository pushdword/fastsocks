/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: auth_struct.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "auth_struct.pb-c.h"
void   authenticate_solicitation__init
                     (AuthenticateSolicitation         *message)
{
  static AuthenticateSolicitation init_value = AUTHENTICATE_SOLICITATION__INIT;
  *message = init_value;
}
size_t authenticate_solicitation__get_packed_size
                     (const AuthenticateSolicitation *message)
{
  assert(message->base.descriptor == &authenticate_solicitation__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t authenticate_solicitation__pack
                     (const AuthenticateSolicitation *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &authenticate_solicitation__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t authenticate_solicitation__pack_to_buffer
                     (const AuthenticateSolicitation *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &authenticate_solicitation__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
AuthenticateSolicitation *
       authenticate_solicitation__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (AuthenticateSolicitation *)
     protobuf_c_message_unpack (&authenticate_solicitation__descriptor,
                                allocator, len, data);
}
void   authenticate_solicitation__free_unpacked
                     (AuthenticateSolicitation *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &authenticate_solicitation__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   authenticate_response__init
                     (AuthenticateResponse         *message)
{
  static AuthenticateResponse init_value = AUTHENTICATE_RESPONSE__INIT;
  *message = init_value;
}
size_t authenticate_response__get_packed_size
                     (const AuthenticateResponse *message)
{
  assert(message->base.descriptor == &authenticate_response__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t authenticate_response__pack
                     (const AuthenticateResponse *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &authenticate_response__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t authenticate_response__pack_to_buffer
                     (const AuthenticateResponse *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &authenticate_response__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
AuthenticateResponse *
       authenticate_response__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (AuthenticateResponse *)
     protobuf_c_message_unpack (&authenticate_response__descriptor,
                                allocator, len, data);
}
void   authenticate_response__free_unpacked
                     (AuthenticateResponse *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &authenticate_response__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   authenticate_acknowledgement__init
                     (AuthenticateAcknowledgement         *message)
{
  static AuthenticateAcknowledgement init_value = AUTHENTICATE_ACKNOWLEDGEMENT__INIT;
  *message = init_value;
}
size_t authenticate_acknowledgement__get_packed_size
                     (const AuthenticateAcknowledgement *message)
{
  assert(message->base.descriptor == &authenticate_acknowledgement__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t authenticate_acknowledgement__pack
                     (const AuthenticateAcknowledgement *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &authenticate_acknowledgement__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t authenticate_acknowledgement__pack_to_buffer
                     (const AuthenticateAcknowledgement *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &authenticate_acknowledgement__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
AuthenticateAcknowledgement *
       authenticate_acknowledgement__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (AuthenticateAcknowledgement *)
     protobuf_c_message_unpack (&authenticate_acknowledgement__descriptor,
                                allocator, len, data);
}
void   authenticate_acknowledgement__free_unpacked
                     (AuthenticateAcknowledgement *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &authenticate_acknowledgement__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   register_solicitation__init
                     (RegisterSolicitation         *message)
{
  static RegisterSolicitation init_value = REGISTER_SOLICITATION__INIT;
  *message = init_value;
}
size_t register_solicitation__get_packed_size
                     (const RegisterSolicitation *message)
{
  assert(message->base.descriptor == &register_solicitation__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t register_solicitation__pack
                     (const RegisterSolicitation *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &register_solicitation__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t register_solicitation__pack_to_buffer
                     (const RegisterSolicitation *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &register_solicitation__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
RegisterSolicitation *
       register_solicitation__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (RegisterSolicitation *)
     protobuf_c_message_unpack (&register_solicitation__descriptor,
                                allocator, len, data);
}
void   register_solicitation__free_unpacked
                     (RegisterSolicitation *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &register_solicitation__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   register_response__init
                     (RegisterResponse         *message)
{
  static RegisterResponse init_value = REGISTER_RESPONSE__INIT;
  *message = init_value;
}
size_t register_response__get_packed_size
                     (const RegisterResponse *message)
{
  assert(message->base.descriptor == &register_response__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t register_response__pack
                     (const RegisterResponse *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &register_response__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t register_response__pack_to_buffer
                     (const RegisterResponse *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &register_response__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
RegisterResponse *
       register_response__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (RegisterResponse *)
     protobuf_c_message_unpack (&register_response__descriptor,
                                allocator, len, data);
}
void   register_response__free_unpacked
                     (RegisterResponse *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &register_response__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   connection_solicitation__init
                     (ConnectionSolicitation         *message)
{
  static ConnectionSolicitation init_value = CONNECTION_SOLICITATION__INIT;
  *message = init_value;
}
size_t connection_solicitation__get_packed_size
                     (const ConnectionSolicitation *message)
{
  assert(message->base.descriptor == &connection_solicitation__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t connection_solicitation__pack
                     (const ConnectionSolicitation *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &connection_solicitation__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t connection_solicitation__pack_to_buffer
                     (const ConnectionSolicitation *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &connection_solicitation__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ConnectionSolicitation *
       connection_solicitation__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ConnectionSolicitation *)
     protobuf_c_message_unpack (&connection_solicitation__descriptor,
                                allocator, len, data);
}
void   connection_solicitation__free_unpacked
                     (ConnectionSolicitation *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &connection_solicitation__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   connection_response__init
                     (ConnectionResponse         *message)
{
  static ConnectionResponse init_value = CONNECTION_RESPONSE__INIT;
  *message = init_value;
}
size_t connection_response__get_packed_size
                     (const ConnectionResponse *message)
{
  assert(message->base.descriptor == &connection_response__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t connection_response__pack
                     (const ConnectionResponse *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &connection_response__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t connection_response__pack_to_buffer
                     (const ConnectionResponse *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &connection_response__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ConnectionResponse *
       connection_response__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ConnectionResponse *)
     protobuf_c_message_unpack (&connection_response__descriptor,
                                allocator, len, data);
}
void   connection_response__free_unpacked
                     (ConnectionResponse *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &connection_response__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   connection_acknowledgement__init
                     (ConnectionAcknowledgement         *message)
{
  static ConnectionAcknowledgement init_value = CONNECTION_ACKNOWLEDGEMENT__INIT;
  *message = init_value;
}
size_t connection_acknowledgement__get_packed_size
                     (const ConnectionAcknowledgement *message)
{
  assert(message->base.descriptor == &connection_acknowledgement__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t connection_acknowledgement__pack
                     (const ConnectionAcknowledgement *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &connection_acknowledgement__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t connection_acknowledgement__pack_to_buffer
                     (const ConnectionAcknowledgement *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &connection_acknowledgement__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ConnectionAcknowledgement *
       connection_acknowledgement__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ConnectionAcknowledgement *)
     protobuf_c_message_unpack (&connection_acknowledgement__descriptor,
                                allocator, len, data);
}
void   connection_acknowledgement__free_unpacked
                     (ConnectionAcknowledgement *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &connection_acknowledgement__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor authenticate_solicitation__field_descriptors[3] =
{
  {
    "header",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(AuthenticateSolicitation, has_header),
    offsetof(AuthenticateSolicitation, header),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "usr",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(AuthenticateSolicitation, usr),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "pw",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(AuthenticateSolicitation, pw),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned authenticate_solicitation__field_indices_by_name[] = {
  0,   /* field[0] = header */
  2,   /* field[2] = pw */
  1,   /* field[1] = usr */
};
static const ProtobufCIntRange authenticate_solicitation__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor authenticate_solicitation__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "authenticate_solicitation",
  "AuthenticateSolicitation",
  "AuthenticateSolicitation",
  "",
  sizeof(AuthenticateSolicitation),
  3,
  authenticate_solicitation__field_descriptors,
  authenticate_solicitation__field_indices_by_name,
  1,  authenticate_solicitation__number_ranges,
  (ProtobufCMessageInit) authenticate_solicitation__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor authenticate_response__field_descriptors[2] =
{
  {
    "header",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(AuthenticateResponse, has_header),
    offsetof(AuthenticateResponse, header),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "token",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(AuthenticateResponse, token),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned authenticate_response__field_indices_by_name[] = {
  0,   /* field[0] = header */
  1,   /* field[1] = token */
};
static const ProtobufCIntRange authenticate_response__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor authenticate_response__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "authenticate_response",
  "AuthenticateResponse",
  "AuthenticateResponse",
  "",
  sizeof(AuthenticateResponse),
  2,
  authenticate_response__field_descriptors,
  authenticate_response__field_indices_by_name,
  1,  authenticate_response__number_ranges,
  (ProtobufCMessageInit) authenticate_response__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor authenticate_acknowledgement__field_descriptors[2] =
{
  {
    "header",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(AuthenticateAcknowledgement, has_header),
    offsetof(AuthenticateAcknowledgement, header),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "token",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(AuthenticateAcknowledgement, token),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned authenticate_acknowledgement__field_indices_by_name[] = {
  0,   /* field[0] = header */
  1,   /* field[1] = token */
};
static const ProtobufCIntRange authenticate_acknowledgement__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor authenticate_acknowledgement__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "authenticate_acknowledgement",
  "AuthenticateAcknowledgement",
  "AuthenticateAcknowledgement",
  "",
  sizeof(AuthenticateAcknowledgement),
  2,
  authenticate_acknowledgement__field_descriptors,
  authenticate_acknowledgement__field_indices_by_name,
  1,  authenticate_acknowledgement__number_ranges,
  (ProtobufCMessageInit) authenticate_acknowledgement__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor register_solicitation__field_descriptors[2] =
{
  {
    "header",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(RegisterSolicitation, has_header),
    offsetof(RegisterSolicitation, header),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "token",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(RegisterSolicitation, token),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned register_solicitation__field_indices_by_name[] = {
  0,   /* field[0] = header */
  1,   /* field[1] = token */
};
static const ProtobufCIntRange register_solicitation__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor register_solicitation__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "register_solicitation",
  "RegisterSolicitation",
  "RegisterSolicitation",
  "",
  sizeof(RegisterSolicitation),
  2,
  register_solicitation__field_descriptors,
  register_solicitation__field_indices_by_name,
  1,  register_solicitation__number_ranges,
  (ProtobufCMessageInit) register_solicitation__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor register_response__field_descriptors[3] =
{
  {
    "header",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(RegisterResponse, has_header),
    offsetof(RegisterResponse, header),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "token",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(RegisterResponse, token),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "regnr",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(RegisterResponse, regnr),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned register_response__field_indices_by_name[] = {
  0,   /* field[0] = header */
  2,   /* field[2] = regnr */
  1,   /* field[1] = token */
};
static const ProtobufCIntRange register_response__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor register_response__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "register_response",
  "RegisterResponse",
  "RegisterResponse",
  "",
  sizeof(RegisterResponse),
  3,
  register_response__field_descriptors,
  register_response__field_indices_by_name,
  1,  register_response__number_ranges,
  (ProtobufCMessageInit) register_response__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor connection_solicitation__field_descriptors[3] =
{
  {
    "header",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(ConnectionSolicitation, has_header),
    offsetof(ConnectionSolicitation, header),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "token",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ConnectionSolicitation, token),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "regnr",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ConnectionSolicitation, regnr),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned connection_solicitation__field_indices_by_name[] = {
  0,   /* field[0] = header */
  2,   /* field[2] = regnr */
  1,   /* field[1] = token */
};
static const ProtobufCIntRange connection_solicitation__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor connection_solicitation__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "connection_solicitation",
  "ConnectionSolicitation",
  "ConnectionSolicitation",
  "",
  sizeof(ConnectionSolicitation),
  3,
  connection_solicitation__field_descriptors,
  connection_solicitation__field_indices_by_name,
  1,  connection_solicitation__number_ranges,
  (ProtobufCMessageInit) connection_solicitation__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor connection_response__field_descriptors[3] =
{
  {
    "header",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(ConnectionResponse, has_header),
    offsetof(ConnectionResponse, header),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ip",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(ConnectionResponse, has_ip),
    offsetof(ConnectionResponse, ip),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "port",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(ConnectionResponse, has_port),
    offsetof(ConnectionResponse, port),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned connection_response__field_indices_by_name[] = {
  0,   /* field[0] = header */
  1,   /* field[1] = ip */
  2,   /* field[2] = port */
};
static const ProtobufCIntRange connection_response__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor connection_response__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "connection_response",
  "ConnectionResponse",
  "ConnectionResponse",
  "",
  sizeof(ConnectionResponse),
  3,
  connection_response__field_descriptors,
  connection_response__field_indices_by_name,
  1,  connection_response__number_ranges,
  (ProtobufCMessageInit) connection_response__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor connection_acknowledgement__field_descriptors[4] =
{
  {
    "header",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(ConnectionAcknowledgement, has_header),
    offsetof(ConnectionAcknowledgement, header),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "token",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ConnectionAcknowledgement, token),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ip",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(ConnectionAcknowledgement, has_ip),
    offsetof(ConnectionAcknowledgement, ip),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "port",
    4,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(ConnectionAcknowledgement, has_port),
    offsetof(ConnectionAcknowledgement, port),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned connection_acknowledgement__field_indices_by_name[] = {
  0,   /* field[0] = header */
  2,   /* field[2] = ip */
  3,   /* field[3] = port */
  1,   /* field[1] = token */
};
static const ProtobufCIntRange connection_acknowledgement__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor connection_acknowledgement__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "connection_acknowledgement",
  "ConnectionAcknowledgement",
  "ConnectionAcknowledgement",
  "",
  sizeof(ConnectionAcknowledgement),
  4,
  connection_acknowledgement__field_descriptors,
  connection_acknowledgement__field_indices_by_name,
  1,  connection_acknowledgement__number_ranges,
  (ProtobufCMessageInit) connection_acknowledgement__init,
  NULL,NULL,NULL    /* reserved[123] */
};