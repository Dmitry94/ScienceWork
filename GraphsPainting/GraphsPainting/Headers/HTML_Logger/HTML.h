#ifndef HTML_H
#define HTML_H

#include "HTML_Tag.h"
#include "HTML_Head.h"
#include "HTML_Body.h"


class HTML : public HTML_Tag
{
public:
	HTML(const HTML_Head &head, const HTML_Body &body)
	{
		m_Head = head;
		m_Body = body;
	}
	std::string toString() const override
	{
		return m_Head.toString() + m_Body.toString();
	}
private:
	HTML_Head m_Head;
	HTML_Body m_Body;
};

#endif HTML_H
