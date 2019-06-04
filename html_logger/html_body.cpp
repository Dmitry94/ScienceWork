#include "html_body.h"


namespace html_logger {

HTMLBody::HTMLBody() { }

HTMLBody::HTMLBody(std::list<std::unique_ptr<HTMLTag> > &tags)
{
    for (auto it = tags.begin(); it != tags.end(); it++) {
        this->tags.push_back(std::move(*it));
    }
    tags.clear();
}

HTMLBody::~HTMLBody()
{
    for (auto it = tags.begin(); it != tags.end(); it++) {
        it->reset();
    }
    tags.clear();
}

void HTMLBody::add_tag(std::unique_ptr<HTMLTag> tag)
{
    tags.push_back(std::move(tag));
}

std::string HTMLBody::get_string_repr() const
{
    std::string answer = "<body>\n";
    for (auto it = tags.cbegin(); it != tags.cend(); it++) {
        answer += (*it)->get_string_repr();
    }
    answer += "</body>\n";
    return answer;
}

}  // namespace html_logger
