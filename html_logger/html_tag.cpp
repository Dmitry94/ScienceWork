#include "html_tag.h"

namespace html_logger {

HTMLSimpleTag::HTMLSimpleTag(const std::string &tag_name, const std::string &tag_value) :
    tag_name(tag_name), tag_value(tag_value)
{ }

std::string HTMLSimpleTag::get_string_repr() const
{
    return "<" + tag_name + ">" + tag_value + "</" + tag_name + ">";
}

} // namespace html_logger
