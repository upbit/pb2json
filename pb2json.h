#ifndef __PB_2_JSON_H__
#define __PB_2_JSON_H__

#include <string>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

#include "json.h" // jsoncpp

int pb2json(const google::protobuf::Message &msg, Json::Value &root);

#endif

