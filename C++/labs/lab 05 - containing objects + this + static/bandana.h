#ifndef __BANDANA_H
#define __BANDANA_H

class Bandana
{
	static constexpr int MAX_COLOR_LEN = 20;
	char color[MAX_COLOR_LEN];
	int length;

public:
	Bandana(const char* color, int length);

	void print() const;
};

#endif // __BANDANA_H
