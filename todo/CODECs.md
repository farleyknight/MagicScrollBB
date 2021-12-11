
## Simple Use 

```c++
#include <iostream>
using namespace std;

class Car
{
    public:
    int speed;
};

int main()
{
    int Car::*pSpeed = &Car::speed;

    Car c1;
    c1.speed = 1;       // direct access
    cout << "speed is " << c1.speed << endl;
    c1.*pSpeed = 2;     // access via pointer to member
    cout << "speed is " << c1.speed << endl;
    return 0;
}
```
https://stackoverflow.com/questions/670734/pointer-to-class-data-member

## Advanced Use

Another example where member-pointers are useful:

```c++
#include <iostream>
#include <string>
#include <list>
using namespace std;
 
namespace szn
{
 
// istream/ostream is a substiture for actual streaming media
 
template<class C>
class able_base
{
public:
	virtual void marshall ( ostream&, const C& ) const = 0;
	virtual void unmarshall ( C&, istream& ) const = 0;
};
 
template<class T,class C> class generic_member_wrapper : public able_base<C>
{
	T C::*_m;
public:
	generic_member_wrapper ( T C::*member_ptr ) : _m(member_ptr) {}
	void marshall ( ostream& s, const C& c ) const override { s << c.*_m << ';'; }
	void unmarshall ( C& c, istream& s ) const override { s >> c.*_m; }    
};
 
template<class T,class C> 
able_base<C>* able_member ( T C::*member_ptr )
{
	return new generic_member_wrapper<T,C> ( member_ptr );
}
 
 
template<class C>
class marshaller 
{
	list<szn::able_base<C>*> _smembers;
public:
	marshaller ( initializer_list<able_base<C>*> il ) : _smembers(il) {}
 
	void marshall ( ostream& s, const C& c ) const
	{
		for ( auto smember: _smembers )
			smember->marshall ( s, c );
	}
	void unmarshall ( C& c, istream& s ) const 
	{
		for ( auto smember: _smembers )
			smember->unmarshall ( c, s );
	}
};
 
}
 
// USE
 
struct Data1
{
	int _m1;
	bool _m2;
	string _m3;
 
	static szn::marshaller<Data1> s_mr;
};
 
szn::marshaller<Data1> Data1::s_mr ( {
    szn::able_member(&Data1::_m1),
    szn::able_member(&Data1::_m2),
    szn::able_member(&Data1::_m3)
} );
 
//Data1::s_serializer = Serializer ( {Data1::_m1, Data1::_m2, Data1::_m3} );
 
int main() 
{
	Data1 d1 = { 31415, true, "the big red fox" };
	Data1::s_mr.marshall ( cout, d1 );
	return 0;
}
```

The result of `stdout` will be:

```
31415;1;the big red fox;
```
