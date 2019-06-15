#ifndef HTML_LOGGER_H
#define HTML_LOGGER_H

#include <string>
#include <list>

#include "html_head.h"
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
    void write_to_file(const std::string &file_path) const;

private:
    // html document head
    std::unique_ptr<HTMLHead> html_head;

    // html table with data
    std::unique_ptr<HTMLTable> html_table;

    // count of columns of table
    uint columns_count;
};

} // namepspace html_logger

#endif /* HTML_LOGGER_H */
