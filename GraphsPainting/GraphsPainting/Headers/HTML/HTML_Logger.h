#ifndef HTML_LOGGER_H
#define HTML_LOGGER_H

#include <string>
#include <list>
#include <fstream>

#include "HTML.h"
#include "HTML_Table.h"

class HTML_Logger
{
public:
	HTML_Logger(std::list<std::string> headers)
	{
		tableSize = headers.size();
		// html head
		HTML_MetaTag tag("charset=\"utf - 8\"");
		std::list<HTML_MetaTag> metaTags(1, tag);
		HTML_Title title("Results");
		HTML_Head *head = new HTML_Head(metaTags, title);

		// create html table
		HTML_Caption tableCaption("Result Table");
		HTML_Tr *tr = new HTML_Tr();
		for (std::list<std::string>::const_iterator cIt = headers.cbegin(); cIt != headers.cend(); cIt++)
		{
			HTML_TableElem *curElem = new HTML_Th(*cIt);
			tr->addElem(curElem);
		}
		m_Tab = new HTML_Table(tableCaption);
		m_Tab->addTr(*tr);

		// create body
		std::list<const HTML_Tag *> bodyTags;
		HTML_Body *body = new HTML_Body(bodyTags);

		// create document
		m_Html = new HTML(head, body);
	}

	void addLogLine(std::list<std::string> headers)
	{
		if (headers.size() != tableSize)
			throw std::out_of_range("Not enough parametres for table");

		HTML_Tr *tr = new HTML_Tr();
		for (std::list<std::string>::const_iterator cIt = headers.cbegin(); cIt != headers.cend(); cIt++)
		{
			HTML_TableElem *curElem = new HTML_Td(*cIt);
			tr->addElem(curElem);
		}
		
		m_Tab->addTr(*tr);
	}
	std::string toString() const
	{
		m_Html->Body->addTag(m_Tab);
		return "<!DOCTYPE html>\n" + m_Html->toString();
	}

	void createFile(const std::string &fname)
	{
		m_Html->Body->addTag(m_Tab);
		std::ofstream out(fname);
		out << "<!DOCTYPE html>\n" + m_Html->toString();
		out.close();
		m_Html->Body->clear();
	}

	~HTML_Logger()
	{
		delete m_Html;
	}
private:
	HTML *m_Html;
	HTML_Table *m_Tab;
	int tableSize;
};

#endif /* HTML_LOGGER_H */