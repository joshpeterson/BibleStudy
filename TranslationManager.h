#ifndef __TRANSLATION_MANAGER_H
#define __TRANSLATION_MANAGER_H

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

class Translation;
class VerseTreeItem;

class TranslationManager : private boost::noncopyable
{
public:
    TranslationManager();

    void add_translation(boost::shared_ptr<const Translation> translation);
    boost::shared_ptr<const Translation> at(const std::string& translation_long_name) const;
    boost::shared_ptr<VerseTreeItem> get_verse_item_tree() const;
    std::map<std::string, boost::shared_ptr<const Translation> >::const_iterator begin() const;
    std::map<std::string, boost::shared_ptr<const Translation> >::const_iterator end() const;

private:
    std::map<std::string, boost::shared_ptr<const Translation> > m_translations;
    boost::shared_ptr<VerseTreeItem> m_verse_tree;

    bool contains_translation(const std::string& translation_long_name) const;
};

class TranslationNotFound : std::exception
{
};

#endif // __TRANSLATION_MANAGER_H
