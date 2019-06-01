#include "html_tag.h"

namespace html_logger {

HTMLSimpleTag::HTMLSimpleTag(const std::string &tag_name, const std::string &tag_value)
{
    this->tag_name = tag_name;
    this->tag_value = tag_value;
}

HTMLSimpleTag::get_string_repr()
{
    return "<" + tag_name + ">" + tag_value + "</" + tag_name + ">";
}

}
