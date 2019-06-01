#include "html_doc.h"

namespace html_logger {

HTMLDoc::HTMLDoc(std::unique_ptr<HTMLHead> head, std::unique_ptr<HTMLBody> body)
{
    this->head = std::move(head);
    this->body = std::move(body);
}

HTMLDoc::~HTMLDoc()
{
    head.reset();
    body.reset();
}

HTMLDoc::get_string_repr()
{
    return head->get_string_repr() + body->get_string_repr();
}

}
