#include "XELContext.h"

XELContext::XELContext()
	:mOperatorChars("+-*/^><=|&%!~")
{

}

XString XELContext::operatorChars() const
{
	return mOperatorChars;
}

void XELContext::setOperatorChars(const XString& operatorChars)
{
	mOperatorChars = operatorChars;
}

std::unordered_map<XString, UnaryOperatorCreator*>& XELContext::unaryOperatorTable()
{
	return mUnaryOperatorTable;
}

void XELContext::setUnaryOperatorTable(const std::unordered_map<XString, UnaryOperatorCreator*>& unaryOperatorTable)
{
	mUnaryOperatorTable = unaryOperatorTable;
}

std::unordered_map<XString, BinaryOperatorCreator*>& XELContext::binaryOperatorTable()
{
	return mBinaryOperatorTable;
}

void XELContext::setBinaryOperatorTable(const std::unordered_map<XString, BinaryOperatorCreator*>& binaryOperatorTable)
{
	mBinaryOperatorTable = binaryOperatorTable;
}

std::unordered_map<XString, FunctionCreator*>& XELContext::functionTable()
{
	return mFunctionTable;
}

void XELContext::setFunctionTable(const std::unordered_map<XString, FunctionCreator*>& functionTable)
{
	mFunctionTable = functionTable;
}

std::unordered_map<XString, Variant>& XELContext::variableTable()
{
    return mVariableTable;
}

void XELContext::setVariableTable(const std::unordered_map<XString, Variant>& variableTable)
{
    mVariableTable = variableTable;
}
