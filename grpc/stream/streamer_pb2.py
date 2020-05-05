# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: streamer.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='streamer.proto',
  package='',
  syntax='proto3',
  serialized_options=None,
  serialized_pb=_b('\n\x0estreamer.proto\"\x1b\n\x0bSendRequest\x12\x0c\n\x04text\x18\x01 \x01(\t\"\x14\n\x05Reply\x12\x0b\n\x03ret\x18\x01 \x01(\x05\"\x1e\n\x0eReceiveRequest\x12\x0c\n\x04text\x18\x01 \x01(\t\"\x1e\n\x0fReceiveResponse\x12\x0b\n\x03ret\x18\x01 \x01(\x05\"\"\n\x12\x43ommunicateRequest\x12\x0c\n\x04text\x18\x01 \x01(\t\"#\n\x13\x43ommunicateResponse\x12\x0c\n\x04text\x18\x01 \x01(\t2\x9e\x01\n\x08Streamer\x12 \n\x04Send\x12\x0c.SendRequest\x1a\x06.Reply\"\x00(\x01\x12\x30\n\x07Receive\x12\x0f.ReceiveRequest\x1a\x10.ReceiveResponse\"\x00\x30\x01\x12>\n\x0b\x43ommunicate\x12\x13.CommunicateRequest\x1a\x14.CommunicateResponse\"\x00(\x01\x30\x01\x62\x06proto3')
)




_SENDREQUEST = _descriptor.Descriptor(
  name='SendRequest',
  full_name='SendRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='text', full_name='SendRequest.text', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=18,
  serialized_end=45,
)


_REPLY = _descriptor.Descriptor(
  name='Reply',
  full_name='Reply',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='ret', full_name='Reply.ret', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=47,
  serialized_end=67,
)


_RECEIVEREQUEST = _descriptor.Descriptor(
  name='ReceiveRequest',
  full_name='ReceiveRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='text', full_name='ReceiveRequest.text', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=69,
  serialized_end=99,
)


_RECEIVERESPONSE = _descriptor.Descriptor(
  name='ReceiveResponse',
  full_name='ReceiveResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='ret', full_name='ReceiveResponse.ret', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=101,
  serialized_end=131,
)


_COMMUNICATEREQUEST = _descriptor.Descriptor(
  name='CommunicateRequest',
  full_name='CommunicateRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='text', full_name='CommunicateRequest.text', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=133,
  serialized_end=167,
)


_COMMUNICATERESPONSE = _descriptor.Descriptor(
  name='CommunicateResponse',
  full_name='CommunicateResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='text', full_name='CommunicateResponse.text', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=169,
  serialized_end=204,
)

DESCRIPTOR.message_types_by_name['SendRequest'] = _SENDREQUEST
DESCRIPTOR.message_types_by_name['Reply'] = _REPLY
DESCRIPTOR.message_types_by_name['ReceiveRequest'] = _RECEIVEREQUEST
DESCRIPTOR.message_types_by_name['ReceiveResponse'] = _RECEIVERESPONSE
DESCRIPTOR.message_types_by_name['CommunicateRequest'] = _COMMUNICATEREQUEST
DESCRIPTOR.message_types_by_name['CommunicateResponse'] = _COMMUNICATERESPONSE
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

SendRequest = _reflection.GeneratedProtocolMessageType('SendRequest', (_message.Message,), {
  'DESCRIPTOR' : _SENDREQUEST,
  '__module__' : 'streamer_pb2'
  # @@protoc_insertion_point(class_scope:SendRequest)
  })
_sym_db.RegisterMessage(SendRequest)

Reply = _reflection.GeneratedProtocolMessageType('Reply', (_message.Message,), {
  'DESCRIPTOR' : _REPLY,
  '__module__' : 'streamer_pb2'
  # @@protoc_insertion_point(class_scope:Reply)
  })
_sym_db.RegisterMessage(Reply)

ReceiveRequest = _reflection.GeneratedProtocolMessageType('ReceiveRequest', (_message.Message,), {
  'DESCRIPTOR' : _RECEIVEREQUEST,
  '__module__' : 'streamer_pb2'
  # @@protoc_insertion_point(class_scope:ReceiveRequest)
  })
_sym_db.RegisterMessage(ReceiveRequest)

ReceiveResponse = _reflection.GeneratedProtocolMessageType('ReceiveResponse', (_message.Message,), {
  'DESCRIPTOR' : _RECEIVERESPONSE,
  '__module__' : 'streamer_pb2'
  # @@protoc_insertion_point(class_scope:ReceiveResponse)
  })
_sym_db.RegisterMessage(ReceiveResponse)

CommunicateRequest = _reflection.GeneratedProtocolMessageType('CommunicateRequest', (_message.Message,), {
  'DESCRIPTOR' : _COMMUNICATEREQUEST,
  '__module__' : 'streamer_pb2'
  # @@protoc_insertion_point(class_scope:CommunicateRequest)
  })
_sym_db.RegisterMessage(CommunicateRequest)

CommunicateResponse = _reflection.GeneratedProtocolMessageType('CommunicateResponse', (_message.Message,), {
  'DESCRIPTOR' : _COMMUNICATERESPONSE,
  '__module__' : 'streamer_pb2'
  # @@protoc_insertion_point(class_scope:CommunicateResponse)
  })
_sym_db.RegisterMessage(CommunicateResponse)



_STREAMER = _descriptor.ServiceDescriptor(
  name='Streamer',
  full_name='Streamer',
  file=DESCRIPTOR,
  index=0,
  serialized_options=None,
  serialized_start=207,
  serialized_end=365,
  methods=[
  _descriptor.MethodDescriptor(
    name='Send',
    full_name='Streamer.Send',
    index=0,
    containing_service=None,
    input_type=_SENDREQUEST,
    output_type=_REPLY,
    serialized_options=None,
  ),
  _descriptor.MethodDescriptor(
    name='Receive',
    full_name='Streamer.Receive',
    index=1,
    containing_service=None,
    input_type=_RECEIVEREQUEST,
    output_type=_RECEIVERESPONSE,
    serialized_options=None,
  ),
  _descriptor.MethodDescriptor(
    name='Communicate',
    full_name='Streamer.Communicate',
    index=2,
    containing_service=None,
    input_type=_COMMUNICATEREQUEST,
    output_type=_COMMUNICATERESPONSE,
    serialized_options=None,
  ),
])
_sym_db.RegisterServiceDescriptor(_STREAMER)

DESCRIPTOR.services_by_name['Streamer'] = _STREAMER

# @@protoc_insertion_point(module_scope)
