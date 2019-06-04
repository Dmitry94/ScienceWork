#ifndef HTML_BODY_H
#define HTML_BODY_H

#include <list>
#include <string>
#include <memory>

#include "html_tag.h"


namespace html_logger {

/** Class for html body representing. **/
class HTMLBody: public HTMLTag {
public:
    /**
     * Create empty html body.
     */
    HTMLBody();

    /**
     * Create html body from list of tags.
     *
     * @param tags collection of html tags.
     *
     * Warning: all HTMLTag objects won't be accesable after creation.
     * They will be owned by HTMLBody. Passed collection will empty.
     *
     */
    HTMLBody(std::list<std::unique_ptr<HTMLTag>> &tags);

    /**
     * Free all resources: list of html tags.
     */
    virtual ~HTMLBody();

    /**
     * Add html tag into html body.
     *
     * @param tag some HTML tag.
     *
     * Warning: after this op tag won't be accesable.
     * It will be owned by HTMLBody.
     *
     */
    void add_tag(std::unique_ptr<HTMLTag> tag);

    /**
     * Get HTML tag string representation.
     *
     * @return string of HTML tag.
     */
    std::string get_string_repr() const override;

private:
    std::list<std::unique_ptr<HTMLTag>> tags;
};

} // namespace html_logger


#endif /* HTML_BODY_H */
