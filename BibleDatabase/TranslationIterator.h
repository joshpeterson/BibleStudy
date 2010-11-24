#ifndef __TRANSLATION_ITERATOR_H
#define __TRANSLATION_ITERATOR_H

#include <map>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/shared_ptr.hpp>

namespace BibleDatabase
{
class Translation;

//! This class represents an iterator which is used to iterate the translations in the translation manager.
class TranslationIterator : public boost::iterator_facade<TranslationIterator, boost::shared_ptr<const Translation>, boost::bidirectional_traversal_tag, boost::shared_ptr<const Translation> >
{
public:
    //! Create a new instance of the TranslationIterator class.
    TranslationIterator(std::map<std::string, boost::shared_ptr<const Translation> >::const_iterator translation_iterator) : m_translation_iterator(translation_iterator)
    {
    }

private:
    friend class boost::iterator_core_access;

    void increment()
    {
        ++m_translation_iterator;
    }

    void decrement()
    {
        --m_translation_iterator;
    }

    bool equal(TranslationIterator const& other) const
    {
        return this->m_translation_iterator == other.m_translation_iterator;
    }
    
    boost::shared_ptr<const Translation> dereference() const
    {
        return (*m_translation_iterator).second;
    }

    std::map<std::string, boost::shared_ptr<const Translation> >::const_iterator m_translation_iterator;
};

}
#endif // __TRANSLATION_ITERATOR_H
