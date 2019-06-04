#ifndef HTML_H
#define HTML_H

#include "html_tag.h"
#include "html_head.h"
#include "html_body.h"


namespace html_logger {

/** Class for html document representation. **/
class HTMLDoc: public HTMLTag {
public:
    /**
     * Create html document from body and head.
     *
     * @param head document's head
     * @param body document's body
     *
     * Warning: after creation, head and body won't be accesable.
     * Ownership will transfer.
     *
     */
    HTMLDoc(std::unique_ptr<HTMLHead> head, std::unique_ptr<HTMLBody> body);

    /**
     * Free all resources: body and head of document will be freed.
     */
    virtual ~HTMLDoc();

    /**
     * Get HTML <html>...</html> string representation.
     *
     * @return string of <html> tag.
     */
    std::string get_string_repr() const;
private:
    std::unique_ptr<HTMLHead> head;
    std::unique_ptr<HTMLBody> body;
};

} // namespace html_logger

#endif /* HTML_H */
