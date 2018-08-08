#ifndef EVALUATENODE_H
#define EVALUATENODE_H

#include <xel_global.h>
#include <Variant.h>

class XELSHARED_EXPORT EvaluateNode
{
public:
	EvaluateNode();
	virtual Variant evaluate() const=0;
	virtual ~EvaluateNode();
};

class XELSHARED_EXPORT ValueNode:public EvaluateNode{
public:
	ValueNode();
	virtual Variant evaluate() const;

	Variant value() const;

	void setValue(const Variant& value);
private:
	Variant mValue;
};

class XELSHARED_EXPORT VariableNode:public EvaluateNode{
public:
	VariableNode();
	virtual Variant evaluate() const;

	QString variableName() const;
	QHash<QString, Variant>* variableTable() const;

	void setVariableName(const QString& variableName);
	void setVariableTable(QHash<QString, Variant>* variableTable);
private:
	QString mVariableName;
	QHash<QString, Variant>* mVariableTable;
};

class XELSHARED_EXPORT UnaryOperatorNode:public EvaluateNode{
public:
	UnaryOperatorNode();
	virtual Variant evaluate() const=0;

	EvaluateNode* operand() const;
	void setOperand(EvaluateNode* operand);

	virtual ~UnaryOperatorNode();
private:
	EvaluateNode* mOperand;
};

class XELSHARED_EXPORT BinaryOperatorNode:public EvaluateNode{
public:
	BinaryOperatorNode();
	virtual Variant evaluate() const=0;

	EvaluateNode* leftOperand() const;
	void setLeftOperand(EvaluateNode* leftOperand);

	EvaluateNode* rightOperand() const;
	void setRightOperand(EvaluateNode* rightOperand);

	virtual ~BinaryOperatorNode();
private:
	EvaluateNode* mLeftOperand;
	EvaluateNode* mRightOperand;
};

class XELSHARED_EXPORT FunctionNode:public EvaluateNode{
public:
	FunctionNode();
	virtual Variant evaluate() const=0;

	QList<EvaluateNode*> parameters() const;
	void setParameters(const QList<EvaluateNode*>& parameters);

	virtual ~FunctionNode();
private:
	QList<EvaluateNode*> mParameters;
};


#endif // EVALUATENODE_H
