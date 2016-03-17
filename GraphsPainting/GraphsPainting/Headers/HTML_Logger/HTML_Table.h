#ifndef HTML_TABLE_H
#define HTML_TABLE_H

#include <list>
#include "HTML_Tag.h"

/********************************* Table td *********************************/
class HTML_Td : public HTML_Tag
{
public:
	HTML_Td() {}
	HTML_Td(const std::string &td)
	{
		m_Td = td;
	}
	std::string toString() const override
	{
		return "\<td\>" + m_Td + "\<\/td\>";
	}
private:
	std::string m_Td;
};

/********************************* Table th *********************************/
class HTML_Th : public HTML_Tag
{
public:
	HTML_Th() {}
	HTML_Th(const std::string &th)
	{
		m_Th = th;
	}
	std::string toString() const override
	{
		return "\<th\>" + m_Th + "\<\/th\>";
	}
private:
	std::string m_Th;
};

/********************************* Table tr *********************************/
class HTML_Tr : public HTML_Tag
{
public:
	HTML_Tr() {}
	void addTd(const HTML_Td & td)
	{
		m_Tds.push_back(td);
	}
	std::string toString() const override
	{
		std::string answer = "\<tr\>";
		for (std::list<HTML_Td>::const_iterator cIt = m_Tds.cbegin(); cIt != m_Tds.cend(); cIt++)
		{
			answer += cIt->toString();
		}
		answer += "\<\/tr\>\n";
		return answer;
	}
private:
	std::list<HTML_Td> m_Tds;
};

/********************************* Table caption *********************************/
class HTML_Caption : public HTML_Tag
{
public:
	HTML_Caption() {}
	HTML_Caption(const std::string &caption)
	{
		m_Caption = caption;
	}
	std::string toString() const override
	{
		return "\<caption\>" + m_Caption + "\<\/caption\>\n";
	}
private:
	std::string m_Caption;
};

/********************************* Table *********************************/
class HTML_Table : public HTML_Tag
{
public:
	HTML_Table(const HTML_Caption &caption)
	{
		m_Caption = caption;
	}
	void addTr(const HTML_Tr &tr)
	{
		m_Trs.push_back(tr);
	}
	std::string toString() const override
	{
		std::string answer = "\<table\>\n";
		for (std::list<HTML_Tr>::const_iterator cIt = m_Trs.cbegin(); cIt != m_Trs.cend(); cIt++)
		{
			answer += cIt->toString();
		}
		answer += "\<\/table\>\n";
		return answer;
	}
private:
	HTML_Caption m_Caption;
	std::list<HTML_Tr> m_Trs;
};

#endif /* HTML_TABLE_H */
