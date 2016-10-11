#include "pb2json.h"

int _parse_msg(const google::protobuf::Message *msg, Json::Value &root);
void _parse_repeated_field(const google::protobuf::Message *msg, const google::protobuf::Reflection * ref,
	const google::protobuf::FieldDescriptor *field, Json::Value &arr);

int pb2json(const google::protobuf::Message &msg, Json::Value &root)
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	return _parse_msg(&msg, root);
}

void _parse_repeated_field(const google::protobuf::Message *msg, const google::protobuf::Reflection * ref,
	const google::protobuf::FieldDescriptor *field, Json::Value &arr)
{
	size_t count = ref->FieldSize(*msg, field);
	switch(field->cpp_type())	
	{
		case google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE:
			for(size_t i = 0 ; i != count ; ++i)
			{
				double value1 = ref->GetRepeatedDouble(*msg,field,i);
				arr.append(value1);
			}
			break;
		case google::protobuf::FieldDescriptor::CPPTYPE_FLOAT:
			for(size_t i = 0 ; i != count ; ++i)
			{
				float value2 = ref->GetRepeatedFloat(*msg,field,i);
				arr.append(value2);
			}
			break;
		case google::protobuf::FieldDescriptor::CPPTYPE_INT64:
			for(size_t i = 0 ; i != count ; ++i)
			{
				int64_t value3 = ref->GetRepeatedInt64(*msg,field,i);
				arr.append((int)value3); // jsoncpp is too old, no Int64 exist
			}
			break;
		case google::protobuf::FieldDescriptor::CPPTYPE_UINT64:
			for(size_t i = 0 ; i != count ; ++i)
			{
				uint64_t value4 = ref->GetRepeatedUInt64(*msg,field,i);
				arr.append((unsigned int)value4); // jsoncpp is too old, no UInt64 exist
			}
			break;
		case google::protobuf::FieldDescriptor::CPPTYPE_INT32:
			for(size_t i = 0 ; i != count ; ++i)
			{
				int32_t value5 = ref->GetRepeatedInt32(*msg,field,i);
				arr.append(value5);
			}
			break;
		case google::protobuf::FieldDescriptor::CPPTYPE_UINT32:
			for(size_t i = 0 ; i != count ; ++i)
			{
				uint32_t value6 = ref->GetRepeatedUInt32(*msg,field,i);
				arr.append(value6);
			}
			break;
		case google::protobuf::FieldDescriptor::CPPTYPE_BOOL:
			for(size_t i = 0 ; i != count ; ++i)
			{
				bool value7 = ref->GetRepeatedBool(*msg,field,i);
				arr.append(value7);
			}
			break;
		case google::protobuf::FieldDescriptor::CPPTYPE_STRING:
			for(size_t i = 0 ; i != count ; ++i)
			{
				std::string value8 = ref->GetRepeatedString(*msg,field,i);
				arr.append(value8);
			}
			break;
		case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE:
			for(size_t i = 0 ; i != count ; ++i)
			{
				const google::protobuf::Message *value9 = &(ref->GetRepeatedMessage(*msg,field,i));
				Json::Value obj;
				_parse_msg(value9, obj);
				arr.append(obj);
			}
			break;
		case google::protobuf::FieldDescriptor::CPPTYPE_ENUM:
			for(size_t i = 0 ; i != count ; ++i)
			{
				const google::protobuf::EnumValueDescriptor* value10 = ref->GetRepeatedEnum(*msg,field,i);
				arr.append(value10->number());
			}
			break;
		default:
			break;
	}
	return;
}

int _parse_msg(const google::protobuf::Message *msg, Json::Value &root)
{
	const google::protobuf::Descriptor *d = msg->GetDescriptor();
	if(!d)return -__LINE__;

	size_t count = d->field_count();
	for (size_t i = 0; i != count ; ++i)
	{
		const google::protobuf::FieldDescriptor *field = d->field(i);
		if(!field)return -__LINE__;
		const google::protobuf::Reflection *ref = msg->GetReflection();
		if(!ref)return -__LINE__;

		const char *name = field->name().c_str();
		if (field->is_repeated())
		{
			Json::Value arr;
			_parse_repeated_field(msg,ref,field,arr);
            if (arr.size() > 0)
			    root[name] = arr;
		}

		if(!field->is_repeated() && ref->HasField(*msg,field))
		{
			switch (field->cpp_type())
			{
				case google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE: {
					double value1 = ref->GetDouble(*msg,field);
					root[name] = value1;
					break;
				}
				case google::protobuf::FieldDescriptor::CPPTYPE_FLOAT: {
					float value2 = ref->GetFloat(*msg,field);
					root[name] = value2;
					break;
				}
				case google::protobuf::FieldDescriptor::CPPTYPE_INT64: {
					int64_t value3 = ref->GetInt64(*msg,field);
					root[name] = (int)value3;
					break;
				}
				case google::protobuf::FieldDescriptor::CPPTYPE_UINT64: {
					uint64_t value4 = ref->GetUInt64(*msg,field);
					root[name] = (unsigned int)value4;
					break;
				}
				case google::protobuf::FieldDescriptor::CPPTYPE_INT32: {
					int32_t value5 = ref->GetInt32(*msg,field);
					root[name] = value5;
					break;
				}
				case google::protobuf::FieldDescriptor::CPPTYPE_UINT32: {
					uint32_t value6 = ref->GetUInt32(*msg,field);
					root[name] = value6;
					break;
				}
				case google::protobuf::FieldDescriptor::CPPTYPE_BOOL: {
					bool value7 = ref->GetBool(*msg,field);
					root[name] = value7;
					break;
				}
				case google::protobuf::FieldDescriptor::CPPTYPE_STRING: {
					std::string value8 = ref->GetString(*msg,field);
					root[name] = value8;
					break;
				}
				case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE: {
					const google::protobuf::Message *value9 = &(ref->GetMessage(*msg,field));
					if (value9) {
                        Json::Value obj;
						_parse_msg(value9, obj);
                        root[name] = obj;
                    }
					break;
				}
				case google::protobuf::FieldDescriptor::CPPTYPE_ENUM: {
					const google::protobuf::EnumValueDescriptor *value10 = ref->GetEnum(*msg,field);
					root[name] = value10->number();
					break;
				}
				default:
					break;
			}
		}
	}
	return 0;
}

