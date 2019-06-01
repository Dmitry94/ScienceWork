#include <list>

#include "html_table.h"
#include "html_tag.h"


namespace html_logger {



HTMLTableTd::HTMLTableTd(const std::string &tag_value)
{
    this->HTMLSimpleTag("td", tag_value);
}

HTMLTableTh::HTMLTableTh(const std::string &tag_value)
{
    this->HTMLSimpleTag("th", tag_value);
}


/** HTMLTableTr class **/


HTMLTableTr::HTMLTableTr() : table_elements() { }


HTMLTableTr::add_element(std::unique_ptr<HTMLTableElement> element)
{
    table_elements.push_back(std::move(element));
    element.reset();
}

HTMLTableTr::get_string_repr()
{
    std::string answer = "<tr>";
    for (auto it = table_elements.cbegin(); it != table_elements.cend(); it++) {
        answer += it->get_string_repr();
    }
    answer += "</tr>\n";
    return answer;
}

HTMLTableTr::~HTMLTableTr() {
    for (auto it = table_elements.begin(); it != table_elements.end(); it++) {
        it->reset();
    }
    table_elements.clear();
}


/** HTMLCaption class **/


HTMLCaption::HTMLCaption(const std::string &tag_value)
{
    this->HTMLSimpleTag("caption", tag_value);
}


/** HTMLTable class **/


HTMLTable::HTMLTable(std::unique_ptr<HTMLCaption> caption)
{
    this->caption = std::move(caption);
}

HTMLTable::add_element(std::unique_ptr<HTMLTableTr> element)
{
    tr_elements.push_back(std::move(element));
}

HTMLTable::get_string_repr()
{
    std::string answer = "<table  border=\"1\"> \n";
    for (auto it = tr_elements.cbegin(); it != tr_elements.cend(); it++)
    {
        answer += it->get_string_repr();
    }
    answer += "</table>\n";
    return answer;
}

HTMLTable::~HTML_Table()
{
    for (auto it = tr_elements.begin(); it != tr_elements.end(); it++) {
        it->reset();
    }
    tr_elements.clear();
    caption.reset();
}
