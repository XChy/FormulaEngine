#include "Variant.h"

Variant::Variant()
	:mType(VariantType::Null)
{}

Variant::Variant(double value)
{
	reset(value);
}

Variant::Variant(int value)
{
	reset(value);
}

Variant::Variant(const XString& value)
{
	reset(value);
}

Variant::Variant(bool value)
{
	reset(value);
}

Variant::Variant(XELObjectWrapper value)
{
	reset(value);
}

Variant::Variant(const Variant& value)
	:mType(value.type()),
	  mHolder(value.mHolder)
{
}



void Variant::set(double value)
{
	mHolder.doubleValue=value;
}

void Variant::set(int value)
{
	mHolder.intValue=value;
}

void Variant::set(const XString& value)
{
	mHolder.stringValue=value;
}

void Variant::set(bool value)
{
	mHolder.boolValue=value;
}

void Variant::set(XELObjectWrapper value)
{
	mHolder.objectValue=value;
}

void Variant::reset(double value)
{
	mType=VariantType::Double;
	set(value);
}

void Variant::reset(int value)
{
	mType=VariantType::Int;
	set(value);
}

void Variant::reset(const XString& value)
{
	mType=VariantType::String;
	set(value);
}

void Variant::reset(bool value)
{
	mType=VariantType::Bool;
	set(value);
}

void Variant::reset(XELObjectWrapper value)
{
	mType=VariantType::Object;
	set(value);
}

void Variant::clear()
{
	mType=VariantType::Null;
}

double Variant::convertDouble() const
{
	if(mType==VariantType::Double){
		return mHolder.doubleValue;
	}else if(mType==VariantType::Int){
		return double(mHolder.intValue);
	}
	throw XELError("Cannot convert "+Variant::convertString(mType)+" to Double");
}

int Variant::convertInt() const
{
	if(mType==VariantType::Double){
		return int(mHolder.doubleValue);
	}else if(mType==VariantType::Int){
		return mHolder.intValue;
	}
	throw XELError("Cannot convert "+Variant::convertString(mType)+" to Double");
}

XString Variant::convertString() const
{
	if(mType==VariantType::String){
		return mHolder.stringValue;
	}
	throw XELError("Cannot convert "+Variant::convertString(mType)+" to String");
}

bool Variant::convertBool() const
{
	if(mType==VariantType::Bool){
		return mHolder.boolValue;
	}else if(mType==VariantType::Int){
		return mHolder.intValue;
	}
	throw XELError("Cannot convert "+Variant::convertString(mType)+" to Bool");
}

XELObjectWrapper Variant::convertObject() const
{
	if(mType==VariantType::Object){
		return mHolder.objectValue;
	}
	throw XELError("Cannot convert "+Variant::convertString(mType)+" to Object");
}

XString Variant::toString() const
{
	switch (type()) {
		case VariantType::Double:
			return XString::number(mHolder.doubleValue);
		case VariantType::Int:
			return XString::number(mHolder.intValue);
		case VariantType::String:
			return XString("\"").append(mHolder.stringValue).append("\"");
		case VariantType::Bool:
			return mHolder.boolValue?"true":"false";
		case VariantType::Object:
			return mHolder.objectValue.data()->toString();
		case VariantType::Null:
			return "null";
	}
}

double Variant::doubleValue() const
{
	return mHolder.doubleValue;
}

int Variant::intValue() const
{
	return mHolder.intValue;
}

XString Variant::stringValue() const
{
	return mHolder.stringValue;
}

bool Variant::boolValue() const
{
	return mHolder.boolValue;
}

XELObjectWrapper Variant::objectValue() const
{
	return mHolder.objectValue;
}

Variant& Variant::operator=(const Variant& variant)
{
	mType=variant.type();
	mHolder=variant.mHolder;
	return *this;
}

Variant& Variant::operator=(double value)
{
	reset(value);
	return *this;
}

Variant& Variant::operator=(int value)
{
	reset(value);
	return *this;
}

Variant& Variant::operator=(const XString& value)
{
	reset(value);
	return *this;
}

Variant& Variant::operator=(bool value)
{
	reset(value);
	return *this;
}

Variant&Variant::operator=(XELObjectWrapper value)
{
	reset(value);
	return *this;
}

bool Variant::operator==(const Variant& variant) const
{
	if(type()==VariantType::Double){
		if(variant.type()==VariantType::Int){
			return mHolder.doubleValue==double(variant.mHolder.intValue);
		}else if(variant.type()==VariantType::Double){
			return mHolder.doubleValue==variant.mHolder.doubleValue;
		}
	}else if(type()==VariantType::Int){
		if(variant.type()==VariantType::Int){
			return mHolder.intValue==variant.mHolder.intValue;
		}else if(variant.type()==VariantType::Double){
			return double(mHolder.intValue)==variant.mHolder.doubleValue;
		}
	}else if(type()==VariantType::String&&variant.type()==VariantType::String){
		return mHolder.stringValue==variant.mHolder.stringValue;
	}else if(type()==VariantType::Bool&&variant.type()==VariantType::Bool){
		return mHolder.boolValue==variant.mHolder.boolValue;
	}
	return false;
}

VariantType Variant::type() const
{
	return mType;
}

XString Variant::convertString(VariantType type)
{
	switch(type){
		case VariantType::Double:
			return "Double";
		case VariantType::Int:
			return "Int";
		case VariantType::String:
			return "String";
		case VariantType::Bool:
			return "Bool";
		case VariantType::Null:
			return "Null";
	}
}

Variant::operator double() const
{
	return convertDouble();
}

Variant::operator int() const
{
	return convertInt();
}

Variant::operator XString() const
{
	return convertString();
}

Variant::operator bool() const
{
	return convertBool();
}

Variant::operator XELObjectWrapper() const
{
	return convertObject();
}
