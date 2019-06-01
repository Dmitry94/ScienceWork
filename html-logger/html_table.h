#ifndef HTML_TABLE_H
#define HTML_TABLE_H

#include <list>
#include <memory>

#include "html_tag.h"

namespace html_logger {


/**
 * HTML table element class. Just abstract class for define type.
 */
class HTMLTableElement : public HTMLTag { };



/**
 * Class for HTML table <td> tag.
 */
class HTMLTableTd : public HTMLTableElement, HTMLSimpleTag {
public:
    /**
     * Construct tag: set value inside.
     */
    HTMLTableTd(const std::string &tag_value);
};



/**
 * Class for HTML table <th> tag.
 */
class HTMLTableTh : public HTMLTableElement, HTMLSimpleTag {
public:
    /**
     * Construct tag: set value inside.
     */
    HTMLTableTh(const std::string &tag_value);
};



/**
 * Class for HTML table <tr> tag.
 */
class HTMLTableTr : public HTMLTableElement {
public:
    /**
     * Construct table tr tag.
     */
    HTMLTableTr();

    /**
     * Add inside tag some table element.
     *
     * @param table_element HTMLTableElement element, that need to be added.
     *
     * Warning: HTMLTableElement won't be accesable after this op.
     * Element will be owned by HTMLTableTr.
     *
     */
    void add_element(std::unique_ptr<HTMLTableElement> element);

    /**
     * Get HTML <tr>...</tr> string representation.
     *
     * @return string of <tr> tag.
     */
    std::string get_string_repr() const override;

    /**
     * Free resources: all elements, that were added by add_element method.
     */
    virtual ~HTMLTableTr();

private:
    /** list of table elements inside <tr> tag. */
    std::list<std::unique_ptr<HTMLTableElement>> table_elements;
};



/**
 * Class for HTML <caption> tag.
 */
class HTMLCaption : public HTMLSimpleTag {
public:
    /**
     * Construct tag: set value inside.
     */
    HTMLCaption(const std::string &tag_value);
};


/**
 * Class for whole HTML table.
 */
class HTMLTable : public HTMLTag
{
public:
    /**
     * Create empty HTML table.
     *
     * @param caption HTMLCaption element.
     *
     * Warning: HTMLCaption won't be accesable after this op.
     * Element will be owned by HTMLTable.
     *
     */
    HTMLTable(std::unique_ptr<HTMLCaption> caption);

    /**
     * Add tr tag inside table.
     *
     * @param tr HTMLTableTr element, that need to be added.
     */
    void add_element(std::unique_ptr<HTMLTableTr> element);

    /**
     * Get HTML <table>...</table> string representation.
     *
     * @return string of <table> tag.
     *
     * Warning: HTMLTableTr won't be accesable after this op.
     * Element will be owned by HTMLTable.
     *
     */
    std::string get_string_repr() const override;

    /**
     * Free all resources: all elements, that were added by add_element method.
     */
    virtual ~HTMLTable();

private:
    std::unique_ptr<HTMLCaption> caption;
    std::list<std::unique_ptr<HTMLTableTr>> tr_elements;
};

} //namespace html_logger

#endif /* HTML_TABLE_H */
