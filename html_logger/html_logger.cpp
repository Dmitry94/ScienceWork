#include <fstream>

#include "html_logger.h"

namespace html_logger {

HTMLLogger::HTMLLogger(const std::list<std::string> &table_headers)
{
    columns_count = table_headers.size();

    // create html head
    std::unique_ptr<HTMLMeta> coding_meta_tag(new HTMLMeta("charset=\"utf - 8\""));
    std::list<std::unique_ptr<HTMLMeta>> meta_tags;
    meta_tags.push_back(std::move(coding_meta_tag));
    std::unique_ptr<HTMLTitle> title(new HTMLTitle("Results"));
    html_head.reset(new HTMLHead(meta_tags, std::move(title)));

    // create html table
    std::unique_ptr<HTMLCaption> table_caption(new HTMLCaption("Results table."));
    html_table.reset(std::move(new HTMLTable(std::move(table_caption))));
    //
    std::unique_ptr<HTMLTableTr> table_tr(new HTMLTableTr());
    for (std::list<std::string>::const_iterator it = table_headers.cbegin();
         it != table_headers.cend(); it++) {
        std::unique_ptr<HTMLTableElement> elem(new HTMLTableTh(*it));
        table_tr->add_element(std::move(elem));
    }
    html_table->add_element(std::move(table_tr));
}

HTMLLogger::~HTMLLogger()
{
    html_table.reset();
    html_head.reset();
}

void HTMLLogger::add_log_line(const std::list<std::string> &table_row)
{
    if (table_row.size() != columns_count)
        throw std::out_of_range("Not enough values inside added row.");

    std::unique_ptr<HTMLTableTr> new_table_tr(new HTMLTableTr());
    for (std::list<std::string>::const_iterator it = table_row.cbegin();
         it != table_row.cend(); it++) {
        std::unique_ptr<HTMLTableElement> elem(new HTMLTableTd(*it));
        new_table_tr->add_element(std::move(elem));
    }
    html_table->add_element(std::move(new_table_tr));
}

std::string HTMLLogger::get_string_repr() const
{
    std::string head_str = html_head->get_string_repr();
    std::string body_str = "<body>\n" + html_table->get_string_repr() + "\n</body>";
    std::string doc_str = "<!DOCTYPE html>\n" + head_str + "\n" + body_str;

    return doc_str;
}


void HTMLLogger::write_to_file(const std::string &file_path) const
{
    std::string file_content = get_string_repr();
    std::ofstream out(file_path);
    out << file_content;
    out.close();
}

} // namespace html_logger
