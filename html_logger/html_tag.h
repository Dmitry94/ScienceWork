#ifndef HTML_TAG_H
#define HTML_TAG_H

#include <string>

namespace html_logger {

/**
 * General class for any HTML tag.
 */
class HTMLTag {
public:
    /**
     * Virtual destructor.
     */
    virtual ~HTMLTag();

    /**
     * Get HTML tag string representation.
     *
     * @return string of HTML tag.
     */
    virtual std::string get_string_repr() const = 0;
};


/**
 * General class for simple tag.
 * Simple tag: <tag> tag_value </tag>.
 */
class HTMLSimpleTag : public HTMLTag {
public:

    /**
     * Create simple tag.
     *
     * @param tag_name string that will be inside <>
     * @param tag_value string that will be inside tag
     */
    HTMLSimpleTag(const std::string &tag_name, const std::string &tag_value);

    /**
     * Get HTML tag string representation.
     *
     * @return string of HTML tag.
     */
    virtual std::string get_string_repr() const override;

private:
    const std::string tag_name;
    const std::string tag_value;
};

} // namespace html_logger

#endif /* HTML_TAG_H */
