#ifndef HTML_LOGGER_H
#define HTML_LOGGER_H

#include <string>
#include <list>

#include "html_doc.h"
#include "html_table.h"

namespace html_logger {

/**
 * Class for logging information into html file.
 * HTML file contains only table with content, no other information to dump supports.
 */
class HTMLLogger {
public:
    /**
     * Logger constructor. Table in html file must contain colums names.
     *
     * @param table_headers List of table columns names.
     */
    HTMLLogger(const std::list<std::string> &table_headers);

    /**
     * Logger destructor.
     */
    virtual ~HTMLLogger();

    /**
     * Method adds some information into table.
     *
     * @param table_row List of row data. Must correspond to columns count.
     */
    void add_log_line(const std::list<std::string> &table_row);

    /**
     * Represent all data into html file string.
     *
     * @return HTML file string
     */
    std::string get_string_repr() const;

    /**
     * Represent all data into html file and dump into FS.
     *
     * @param file_path Path to out file.
     */
    void write_to_file(const std::string &file_path);

private:
    // html document head
    std::unique_ptr<HTMLHead> html_head;

    // html table with data
    std::unique_ptr<HTMLTable> html_table;

    // count of columns of table
    uint columns_count;
};

}

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
