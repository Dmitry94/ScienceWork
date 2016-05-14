#ifndef HTML_HEAD
#define HTML_HEAD

#include <list>
#include <string>

#include "HTML_Tag.h"

class HTML_Title : public HTML_Tag
{
public:
	HTML_Title() { m_Title = ""; }
	HTML_Title(const std::string & title)
	{
		m_Title = title;
	}
	std::string toString() const override
	{
		return "<title>" + m_Title + "</title>\n";
	}
private:
	std::string m_Title = "";
};

class HTML_MetaTag : public HTML_Tag
{
public:
	HTML_MetaTag() {}
	HTML_MetaTag(const std::string value)
	{
		m_Value = value;
	}
	std::string toString() const override
	{
		return "<meta " + m_Value + ">\n";
	}
private:
	std::string m_Value;
};

class HTML_Head : public HTML_Tag
{
public:
	HTML_Head() {}
	HTML_Head(const std::list<HTML_MetaTag> &metaTags, const HTML_Title &title)
	{
		m_MetaTags = metaTags;
		m_Title = title;
	}
	std::string toString() const override
	{
		std::string answer = "<head>\n";
		for (std::list<HTML_MetaTag>::const_iterator cIt = m_MetaTags.cbegin(); cIt != m_MetaTags.end(); cIt++)
		{
			answer += cIt->toString();
		}
		answer += m_Title.toString();
		answer += "</head>\n";
		return answer;
	}
private:
	std::list<HTML_MetaTag> m_MetaTags;
	HTML_Title m_Title;
};

#endif /* HTML_HEAD */
