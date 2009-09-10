#include <limits.h>
#include <boost/spirit/phoenix/operators.hpp>
#include <boost/spirit/phoenix/primitives.hpp>
#include <boost/spirit/phoenix/special_ops.hpp>
#include "StarredVersesModel.h"
#include "TranslationManager.h"
#include "Translation.h"
#include "VerseDisplay.h"

using namespace phoenix;

StarredVersesModel::StarredVersesModel(boost::shared_ptr<const TranslationManager> translation_manager) :
    m_translation_manager(translation_manager)
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
        boost::shared_ptr<const Translation> translation = m_translation_manager->at(m_starred_verses[index.row()]->get_translation());
        return verse_collection_title(translation->get_entry(m_starred_verses[index.row()]->get_verse_id(), 
                                                             m_starred_verses[index.row()]->get_num_verses_context())).c_str();
    }

    return QVariant();
}

void StarredVersesModel::add_starred_verse(boost::shared_ptr<VerseDisplay> verse)
{
    if (std::find_if(m_starred_verses.begin(), m_starred_verses.end(), *arg1 == *verse) == m_starred_verses.end())
    {
        m_starred_verses.push_back(verse);
        reset();
    }
}

void StarredVersesModel::remove_starred_verse(boost::shared_ptr<VerseDisplay> verse)
{
    std::vector<boost::shared_ptr<VerseDisplay> >::iterator verse_it = std::find_if(m_starred_verses.begin(), 
                                                                                    m_starred_verses.end(), 
                                                                                    *arg1 == *verse);
    if (verse_it != m_starred_verses.end())
    {
        m_starred_verses.erase(verse_it);
        reset();
    }
}

bool StarredVersesModel::verse_starred(boost::shared_ptr<VerseDisplay> verse)
{
    return std::find_if(m_starred_verses.begin(), m_starred_verses.end(), *arg1 == *verse) != m_starred_verses.end();
}

boost::shared_ptr<VerseDisplay> StarredVersesModel::get_verse_display(const QModelIndex &index)
{
    boost::shared_ptr<const Translation> translation = m_translation_manager->at(m_starred_verses[index.row()]->get_translation());
    return boost::shared_ptr<VerseDisplay>(new VerseDisplay(translation->get_long_name(), m_starred_verses.at(index.row())->get_verse_id(), 
                                                            m_starred_verses.at(index.row())->get_num_verses_context()));
}

