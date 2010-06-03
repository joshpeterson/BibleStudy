#ifndef __STARRED_VERSES_MODEL_H
#define __STARRED_VERSES_MODEL_H

#include <QAbstractListModel>
#include <boost/shared_ptr.hpp>
#include <vector>

class BibleDatase::TranslationManager;
class BibleDatase::VerseDisplay;

namespace BibleStudy
{

//! This class is an implementation of a model from the Qt Model/View framework for a list view which represents the verses the user has starred.
class StarredVersesModel : public QAbstractListModel
{
public:
    //! Create a new instance of the StarredVersesModel class.
    StarredVersesModel(boost::shared_ptr<const BibleDatase::TranslationManager> translation_manager);

    //! Add a verse to the collection of starred verses.
    void add_starred_verse(boost::shared_ptr<BibleDatase::VerseDisplay> verse);

    //! Remove a verse from the collection of starred verses.
    void remove_starred_verse(boost::shared_ptr<BibleDatase::VerseDisplay> verse);

    //! Determine whether or not the given verse has been starred.
    bool verse_starred(boost::shared_ptr<BibleDatase::VerseDisplay> verse);

    //! Get the VerseDisplay object for the verse at the given index.
    boost::shared_ptr<BibleDatase::VerseDisplay> get_verse_display(const QModelIndex& index);
    
    //! Get the number of rows for the given parent index.  This is the number of starred verses.
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    //! Get the data for a given index.
    QVariant data(const QModelIndex &index, int role) const;

private:
    boost::shared_ptr<const BibleDatase::TranslationManager> m_translation_manager;
    std::vector<boost::shared_ptr<BibleDatase::VerseDisplay> > m_starred_verses;
};

}

#endif // __STARRED_VERSES_MODEL_H
