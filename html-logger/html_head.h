#ifndef HTML_HEAD
#define HTML_HEAD

#include <list>
#include <string>
#include <memory>

#include "html_tag.h"

namespace html_logger {

/** Class for html title tag **/
class HTMLTitle: public HTMLSimpleTag {
public:
    /**
     * Construct tag: set value inside.
     */
    HTMLTitle(const std::string &tag_value);
};


/** Class for html meta tag **/
class HTMLMeta: public HTMLSimpleTag {
public:
    /**
     * Construct tag: set value inside.
     */
    HTMLMeta(const std::string &tag_value);
};


/** Class for html head tag **/
class HTMLHead: public HTMLTag {
public:
    /**
     * Create html <head>.
     *
     * @param meta_tags collection of meta tags.
     * @param title html title tag.
     *
     * Warning: all meta tags, collection object and title tag won't be accesable after creation.
     * All data will be owned by HTMLHead. Passed collection will empty.
     *
     */
    HTMLHead(std::list<std::unique_ptr<HTMLMeta>> &meta_tags, std::unique_ptr<HTMLTitle> title);

    /**
     * Free all resources: meta tags and title.
     */
    virtual ~HTMLHead();
private:
    std::list<std::unique_ptr<HTMLMeta>> meta_tags;
    std::unique_ptr<HTMLTitle> title;
};

}


#endif /* HTML_HEAD */
