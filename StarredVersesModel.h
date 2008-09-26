#ifndef __STARRED_VERSES_MODEL_H
#define __STARRED_VERSES_MODEL_H

#include <QAbstractListModel>
#include <boost/shared_ptr.hpp>
#include <vector>

class Translation;

class StarredVersesModel : public QAbstractListModel
{
public:
    StarredVersesModel(boost::shared_ptr<Translation> translation);
    void add_starred_verse(int verse_id, int num_verses_context);
    void remove_starred_verse(int verse_id);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;


private:
    boost::shared_ptr<Translation> m_translation;
    std::vector<std::pair<int, int> > m_starred_verses;
};

class MatchVerse
{
public:
    MatchVerse(int verse_id) : m_verse_id(verse_id){}
    bool operator()(const std::pair<int, int> &verse)
    {
        return (verse.first == m_verse_id);
    }

private:
    int m_verse_id;
};

#endif // __STARRED_VERSES_MODEL_H
