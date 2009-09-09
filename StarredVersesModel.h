#ifndef __STARRED_VERSES_MODEL_H
#define __STARRED_VERSES_MODEL_H

#include <QAbstractListModel>
#include <boost/shared_ptr.hpp>
#include <vector>

class TranslationManager;
class VerseDisplay;

class StarredVersesModel : public QAbstractListModel
{
public:
    StarredVersesModel(boost::shared_ptr<const TranslationManager> translation_manager);
    void add_starred_verse(boost::shared_ptr<VerseDisplay> verse);
    void remove_starred_verse(boost::shared_ptr<VerseDisplay> verse);
    bool verse_starred(boost::shared_ptr<VerseDisplay> verse);
    boost::shared_ptr<VerseDisplay> get_verse_display(const QModelIndex& index);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;


private:
    boost::shared_ptr<const TranslationManager> m_translation_manager;
    std::vector<boost::shared_ptr<VerseDisplay> > m_starred_verses;
};

#endif // __STARRED_VERSES_MODEL_H
