#ifndef HTML_TAG_H
#define HTML_TAG_H

#include <string>

class HTML_Tag
{
public:
	~HTML_Tag() {}
	virtual std::string toString() const = 0;
};

#endif /* HTML_TAG_H */