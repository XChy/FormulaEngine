#ifndef XSTRING_H
#define XSTRING_H

#include <xel_global.h>

template<typename T>
class XEL_EXPORT Ref{
public:
	Ref(T* ptr)
		:mPointer(ptr),
		  mRefCount(1)
	{}
	Ref(const Ref<T>& ref)
		:mRefCount(1)
	{
		mPointer=new T(*ref.pointer());
	}
	int ref(){
		return ++mRefCount;
	}
	int unref(){
		return --mRefCount;
	}
	~Ref()
	{
		delete mPointer;
	}

	T* pointer() const
	{
		return mPointer;
	}
	int refCount() const
	{
		return mRefCount;
	}
private:
	T* mPointer;
	int mRefCount;
};

class XEL_EXPORT StringData{
public:
	StringData(const StringData& other);
	StringData(uint size=1);
	void allocate(uint allocSize);
	void reallocate(uint allocSize);
	~StringData();
	char16_t* data;
	uint size;
	uint allocSize;
};

template<typename T>
class XEL_EXPORT SharedData{
public:
	SharedData(){}
	SharedData(T* p)
		:ref(new Ref<T>(p))
	{}
	SharedData(const SharedData& d)
		:ref(d.ref)
	{
		ref->ref();
	}
	SharedData& operator=(const SharedData& d)
	{
		if(this==&d){
			return *this;
		}
		if(ref->unref()==0){
			delete ref;
		}
		ref=d.ref;
		ref->ref();
		return *this;
	}
	T* data() const
	{
		return ref->pointer();
	}
	~SharedData()
	{
		if(ref->unref()==0)
		{
			delete ref;
		}
	}

	Ref<T>* ref;
};

class XEL_EXPORT XChar{
	friend class XString;
public:
	XChar(const XChar& other):ucs(other.ucs){}
	XChar(char ucs):ucs(uchar(ucs)){}
	XChar(uchar ucs):ucs(ucs){}
	XChar(short ucs):ucs(ushort(ucs)){}
	XChar(ushort ucs):ucs(ucs){}
	XChar(int ucs4):ucs(ushort(ucs4|0xFFFF)){}
	XChar(uint ucs4):ucs(ushort(ucs4|0xFFFF)){}
	bool isDigit() const;
	bool isSpace() const;
	bool isLetter() const;
	bool isLetterOrDigit() const;

	int digitValue() const;
	XChar operator-(const XChar& other) const;
	bool operator==(XChar other) const;
	bool operator!=(XChar other) const;
	bool operator>(XChar other) const;
	bool operator<(XChar other) const;
	bool operator>=(XChar other) const;
	bool operator<=(XChar other) const;
private:
	char16_t ucs;
};

//XString
// Encoding:UCS2
// Copy on write

class XEL_EXPORT XString{
public:
	XString();
	XString(const XString& other);
	XString(const char* utf8);
	XString(const wchar_t* wstr);
	XString(const char16_t* ustr);

	const XChar* data() const;
	XChar* data();

	int size() const;

	XString& operator=(const char* utf8);
	XString& operator=(const wchar_t* wstr);
	XString& operator=(const char16_t* ustr);

	XString& append(const char* ascii);
	XString& append(const wchar_t* wstr);
	XString& append(const XString& other);
	XString& append(const char16_t* ustr);
	XString& append(XChar xc);

	XString& reverse();

	XString operator+(const char* cstr) const;
	XString operator+(const wchar_t* wstr) const;
	XString operator+(const XString& other) const;
	XString operator+(const char16_t* ustr) const;
	XString operator+(XChar xc) const;

	XChar operator[](int index) const;
	XChar& operator[](int index);

	bool operator==(const XString& other) const;

	bool contains(XChar xc) const;

	void removeAt(int pos);
	void remove(int pos,int len);
	void removeLast();

	std::string toStdString() const;
	std::u16string toUtf16String() const;

	const XChar* unicode() const;

	int toInt(int base=10) const;
	double toDouble() const;

	static XString fromUtf8(const char* data);

	static XString number(int v, int base=10);
	static XString number(double v);

	typedef XChar* iterator;
	iterator begin();
	iterator end();

	typedef const XChar* const_iterator;
	const_iterator begin() const;
	const_iterator end() const;

	bool isDetach();
	void detach();


private:
	SharedData<StringData> d;
};

XString operator+(const char* utf8,const XString& xstr);

class XStringHasher
{
public:
	size_t operator()(const XString& xstr) const
	{
		int base=131;
		unsigned long long ans=0;
		for(auto it=xstr.begin();it!=xstr.begin();++it)
			ans=ans*base+(unsigned long long)(*(ushort*)it);
		return ans&0x7fffffff;
	}
};

namespace std {

template<>
struct hash<XString>
{
	size_t operator()(const XString& xstr) const{
		return XStringHasher()(xstr);
	}
};

}

#endif // XSTRING_H
