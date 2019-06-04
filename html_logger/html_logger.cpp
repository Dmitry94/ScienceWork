#include <fstream>

#include "html_logger.h"

namespace html_logger {

HTMLLogger::HTMLLogger(const std::list<std::string> &table_headers)
{
    columns_count = table_headers.size();

    // create html head
    std::list<std::unique_ptr<HTMLMeta>> meta_tags {
        std::unique_ptr<HTMLMeta>(new HTMLMeta("charset=\"utf - 8\""))};
    std::unique_ptr<HTMLTitle> title(new HTMLTitle("Results"));
    html_head = std::move(new HTMLHead(meta_tags, title));

    // create html table
    std::unique_ptr<HTMLCaption> table_caption(new HTMLCaption("Results table."));
    html_table = std::move(new HTMLTable(table_caption));
    //
    std::unique_ptr<HTMLTableTr> table_tr(new HTMLTableTr());
    for (std::list<std::string>::const_iterator it = table_headers.cbegin();
         it != table_headers.cend(); it++) {
        std::unique_ptr<HTMLTableElement> elem(new HTMLTableTh(*it));
        table_tr->add_element(elem);
    }
    html_table->add_element(table_tr);
}

void HTMLLogger::~HTMLLogger()
{
    html_table.reset();
    html_head.reset();
}



}
