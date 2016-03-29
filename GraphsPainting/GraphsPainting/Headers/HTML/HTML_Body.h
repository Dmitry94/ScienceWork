#ifndef HTML_BODY_H
#define HTML_BODY_H

#include <string>
#include "HTML_Tag.h"

class HTML_Body : public HTML_Tag
{
public:
	HTML_Body() {}
	HTML_Body(const std::list<const HTML_Tag *> & tags) 
	{
		m_Tags = tags;
	}
	void addTag(const HTML_Tag * tag)
	{
		m_Tags.push_back(tag);
	}
	void clear()
	{
		m_Tags.clear();
	}
	std::string toString() const override
	{
		std::string answer = "<body>\n";
		for (std::list<const HTML_Tag *>::const_iterator cIt = m_Tags.cbegin(); cIt != m_Tags.cend(); cIt++)
		{
			answer += (*cIt)->toString();
		}
		answer += "</body>\n";
		return answer;
	}
	~HTML_Body()
	{
		for (std::list<const HTML_Tag *>::const_iterator cIt = m_Tags.cbegin(); cIt != m_Tags.cend(); cIt++)
		{
			delete (*cIt);
		}
	}
private:
	std::list<const HTML_Tag *> m_Tags;
};



#endif /* HTML_BODY_H */
