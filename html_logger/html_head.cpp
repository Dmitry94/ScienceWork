#include "html_head.h"

namespace html_logger {

/** HTMLTitle class definitions. **/

HTMLTitle::HTMLTitle(const std::string &tag_value) : HTMLSimpleTag("title", tag_value)
{ }

/** HTMLMeta class definitions. **/
HTMLMeta::HTMLMeta(const std::string &tag_value) : HTMLSimpleTag("meta", tag_value)
{ }

/** HTMLHead class definitions. **/
HTMLHead::HTMLHead(std::list<std::unique_ptr<HTMLMeta>> &meta_tags,
                   std::unique_ptr<HTMLTitle> title)
{
    for (auto it = meta_tags.begin(); it != meta_tags.end(); it++) {
        this->meta_tags.push_back(std::move(*it));
    }
    meta_tags.clear();

    this->title = std::move(title);
}

std::string HTMLHead::get_string_repr() const
{
    std::string answer = "<head>\n";
    for (auto it = meta_tags.cbegin(); it != meta_tags.end(); it++) {
        answer += (*it)->get_string_repr();
    }
    answer += title->get_string_repr();
    answer += "</head>\n";
    return answer;
}

HTMLHead::~HTMLHead()
{
    for (auto it = meta_tags.begin(); it != meta_tags.end(); it++) {
        it->reset();
    }
    meta_tags.clear();

    title.reset();
}

}  // namespace html_logger
