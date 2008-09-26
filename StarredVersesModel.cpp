#include "StarredVersesModel.h"
#include "Translation.h"

StarredVersesModel::StarredVersesModel(boost::shared_ptr<Translation> translation) :
    m_translation(translation)
{
}

int StarredVersesModel::rowCount(const QModelIndex& parent) const
{
    return m_starred_verses.size();
}

QVariant StarredVersesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= static_cast<int>(m_starred_verses.size()))
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return verse_collection_title(m_translation->get_entry(m_starred_verses[index.row()].first, 
                                                               m_starred_verses[index.row()].second)).c_str();
    }

    return QVariant();
}

void StarredVersesModel::add_starred_verse(int verse_id, int num_verses_context)
{
    if (std::find_if(m_starred_verses.begin(), m_starred_verses.end(), MatchVerse(verse_id)) == m_starred_verses.end())
    {
        std::pair<int, int> starred_verse;
        starred_verse.first = verse_id;
        starred_verse.second = num_verses_context;
        m_starred_verses.push_back(starred_verse);
        reset();
    }
}

void StarredVersesModel::remove_starred_verse(int verse_id)
{
    std::vector<std::pair<int, int> >::iterator verse_it = std::find_if(m_starred_verses.begin(), 
                                                                        m_starred_verses.end(), 
                                                                        MatchVerse(verse_id));
    if (verse_it != m_starred_verses.end())
    {
        m_starred_verses.erase(verse_it);
        reset();
    }
}
