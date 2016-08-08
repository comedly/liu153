#pragma once

//���������ͱ�
struct InputIteratorTag{ };
struct OutputIteratorTag{ };
struct ForwardIteratorTag:public InputIteratorTag{ };
struct BidirectionalIteratorTag:public ForwardIteratorTag { };
struct RandomAccessIteratorTag:public BidirectionalIteratorTag{ };

template<class T,class Distance>
struct InputIterator
{
	typedef InputIteratorTag IteratorCategory;
	typedef T    ValueType;
	typedef Distance  DifferenceType;
	typedef T*  Pointer;
	typedef T&  Reference;
};

struct OutputIterator
{
	typedef OutputIteratorTag IteratorCategroy;
	typedef void ValueType;
	typedef void DifferenceType;
	typedef void Pointer;
	typedef void Reference;
};

template<class T,class Distance>
struct ForwardIterator
{
	typedef ForwardIteratorTag IteratorCategroy;
	typedef T   ValueType;
	typedef Distance  DifferenceType;
	typedef T* Pointer;
	typedef T& Reference;
};

template<class T,class Distance>
struct BidirectionalIterator
{
	typedef BidirectionalIteratorTag IteratorCategroy;
	typedef T ValueType;
	typedef Distance DifferenceType;
	typedef T* Pointer;
	typedef T& Reference;
};

template<class T,class Distance>
struct RandomAccessIterator
{
	typedef RandomAccessIteratorTag IteratorCategroy;
	typedef T   ValueType;
	typedef Distance DifferenceType;
	typedef T* Pointer;
	typedef T& Reference;
};

//��������Ƕ����������Ӧ���ͱ�
//Iterator Category��Value Type��Difference Type��Pointer��Reference
//������Ƕ���ͱ��壬ȷ�����ܹ�������ĸ�STL�ں�
//�ҷ���Iterator Traits��������ȡ

template<class Category,class T,class Distance = ptrdiff_t,class Pointer = T*,class Reference = T&>
struct Iterator
{
	typedef Category IteratorCategory;//����������
	typedef T ValueType;//��������ָ��������
	typedef Distance DifferenceType;//����������֮��ľ���
	typedef Pointer Pointer;//��������ָ�����ָ��
	typedef Reference Reference;//��������ָ���������
};

//Traits����һ̨��������ȡ������եȡ����������������

template<class Iterator>
struct IteratorTraits
{
	typedef typename Iterator::IteratorCagetory IteratorCategory;
	typedef typename Iterator::ValueType  ValueType;
	typedef typename Iterator::DifferenceType DifferenceType;
	typedef typename Iterator::Pointer Pointer;
	typedef typename Iterator::Reference Reference;
};

//ƫ�ػ�ԭ��ָ��
template<class T>
struct IteratorTraits<T*>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T               ValueType;
	typedef ptrdiff_t       DifferenceType;
	typedef T*              Pointer;
	typedef T&              Reference;
};

//ƫ�ػ�constԭ��ָ��

template<class T>
struct IteratorTraits<const T*>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T ValueType;
	typedef ptrdiff_t  DifferenceType;
	typedef const T* Pointer;
	typedef const T& Reference;
};

//Distance��ʵ��

template<class InputIterator>
inline typename IteratorTraits<InputIterator>::DifferenceType 
 __Distance(InputIterator first,InputIterator last,InputIteratorTag)
{
	IteratorTraits<InputIterator>::DifferenceType n= 0;
	while(first != last)
	{
		++first;
		++n;
	}
	return n;
}

template<class RandomAccessIterator>
inline typename IteratorTraits<RandomAccessIterator>::DifferenceType
	__Distance(RandomAccessIterator first,RandomAccessIterator last,RandomAccessIteratorTag)
{
	return last - first;
}

template<class InputIterator> 
inline typename IteratorTraits<InputIterator>::DifferenceType
	Distance(InputIterator first,InputIterator last)
{
	return __Distance(first,last,IteratorTraits<InputIterator>::IteratorCategory());
}

//Advance��ʵ��

template<class InputIterator,class Distance>
inline void __Advance(InputIterator& i,Distance n,InputIteratorTag)
{
	while (n--)
	{
		++i;
	}
}

template<class BidirectionalIterator,class Distance>
inline void __Advance(BidirectionalIterator& i,Distance n,BidirectionalIteratorTag)
{
	if(n >= 0)
	{
		while (n--)
		{
			++i;
		}
	}
	else
	{
		while (n++)
		{
			--i;
		}
	}
}

template<class RandomAccessIterator ,class Distance>
inline void __Advance(RandomAccessIterator& i,Distance n,RandomAccessIteratorTag)
{
	i += n;
}

template<class InputIterator,class Distance>
inline void Advance(InputIterator& i,Distance n)
{
	__Advance(i,n,IteratorTraits<InputIterator>::IteratorCategory());
}

template<class T,class Distance>
inline T* ValueType(const InputIterator<T,Distance>&)
{
	return (T*)(0);
}

template<class T,class Distance>
inline T* ValueType(const ForwardIterator<T,Distance>&)
{
	return (T*)(0);
}

template<class T,class Distance>
inline T* ValueType(const BidirectionalIterator<T,Distance>&)
{
	return (T*)(0);
}

template<class T,class Distance>
inline T* ValueType(const RandomAccessIterator<T,Distance>&)
{
	return (T*)(0);
}

template<class T>
inline T* ValueType(const T*)
{
	return (T*)(0);
}

//���������
template<class Iterator>
class ReverseIterator
{
public:
	//ͨ����������ȡ������ȡ������������еĻ�������
	typedef typename IteratorTraits<Iterator>::IteratorCategory IteratorCategory;
	typedef typename IteratorTraits<Iterator>::ValueType ValueType;
	typedef typename IteratorTraits<Iterator>::DifferenceType DifferenceType;
	typedef typename IteratorTraits<Iterator>::Pointer Pointer;
	typedef typename IteratorTraits<Iterator>::Reference Reference;

	typedef Iterator IteratorType;
	typedef ReverseIterator<Iterator> Self;
	
public:
	ReverseIterator()
	{ }

/*	explicit*/ ReverseIterator(IteratorType x)
		:_current(x)
	{ }

	Reference operator*() const
	{
		//ע�����������ʱȡ���ǵ�ǰλ�õ�ǰһ�����ݡ�
		//��ΪRBegin���� == End���� REnd() = Begin()
		Iterator temp = _current;
		return *--temp;
	}

	Pointer operator ->()const
	{
		return &(operator*());
	}

	Self operator++()
	{
		--_current;
		return *this;
	}

	Self operator++(int)
	{
		Self temp = *this;
		--_current;
		return temp;
	}

	Self operator--()
	{
		++_current;
		return *this;
	}

	Self operator--(int)
	{
		Self temp = _current;
		++_current;
		return temp;
	}

	bool operator == (const Self& x)
	{
		return _current == x._current;
	}

	bool operator != (const Self& x)
	{
		return _current != x._current;
	}
protected:
	Iterator _current;
};


