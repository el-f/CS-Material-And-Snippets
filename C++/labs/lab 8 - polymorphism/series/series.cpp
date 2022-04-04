#include "series.h"

ostream& operator<<(ostream& os, const Series& s)
{
	os << typeid(s).name() + 6 << " --> a1 = " << s.a1 << ", jump = " << s.jump;
	return os;
}