#ifndef HTML_H
#define HTML_H

#include "HTML_Tag.h"
#include "HTML_Head.h"
#include "HTML_Body.h"


class HTML : public HTML_Tag
{
public:
	HTML() {}
	HTML(HTML_Head *head, HTML_Body *body)
	{
		Head = head;
		Body = body;
	}
	std::string toString() const override
	{
		return Head->toString() + Body->toString();
	}
	~HTML()
	{
		delete Head;
		delete Body;
	}
	HTML_Head *Head;
	HTML_Body *Body;
};

#endif HTML_H
