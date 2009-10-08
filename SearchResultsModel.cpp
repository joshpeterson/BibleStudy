#include <vector>
#include <boost/shared_ptr.hpp>
#include "SearchResultsModel.h"
#include "TranslationManager.h"
#include "Verse.h"
#include "VerseDisplay.h"

using namespace BibleStudy;

SearchResultsModel::SearchResultsModel(boost::shared_ptr<const TranslationManager> translation_manager, 
                                       QObject* parent) :
    QAbstractTableModel(parent),
    m_translation_manager(translation_manager)
{
}

void SearchResultsModel::SetResults(boost::shared_ptr<const ISearchResults> results)
{
    m_results = results;
    this->reset();
}

 int SearchResultsModel::rowCount(const QModelIndex &/*parent*/) const
 {
    if (m_results)
        return m_results->num_results();
    else
       return 0;
 }

 int SearchResultsModel::columnCount(const QModelIndex &/*parent*/) const
 {
    return 3;
 }

 QVariant SearchResultsModel::data(const QModelIndex &index, int role) const
 {
    if (!m_results)
        return QVariant();

    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_results->num_results())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        int column = index.column();
        if (column == translation_column)
        {
            boost::shared_ptr<const Translation> translation = m_translation_manager->at(m_results->translation_at(index.row()));
            return translation->get_short_name().c_str();
        }
        else if (column == location_column)
        {
            boost::shared_ptr<const Translation> translation = m_translation_manager->at(m_results->translation_at(index.row()));
            QString location(translation->get_entry(m_results->at(index.row()))->get_book().c_str());
            location += " ";
            location += QString::number(translation->get_entry(m_results->at(index.row()))->get_chapter());
            location += ":";
            location += QString::number(translation->get_entry(m_results->at(index.row()))->get_verse());
            return location;
        }
        else if (column == text_column)
        {
            boost::shared_ptr<const Translation> translation = m_translation_manager->at(m_results->translation_at(index.row()));
            return translation->get_entry(m_results->at(index.row()))->get_text().c_str();
        }
        else
        {
            return QVariant();
        }
    }
    else if (role == Qt::ToolTipRole)
    {
        boost::shared_ptr<const Translation> translation;
        int column = index.column();
        if (column == translation_column)
        {
            boost::shared_ptr<const Translation> translation = m_translation_manager->at(m_results->translation_at(index.row()));
            return translation->get_long_name().c_str();
        }
        else if (column == text_column)
        {
            translation = m_translation_manager->at(m_results->translation_at(index.row()));
            return verse_collection_to_title_and_string_wrapped(translation->get_entry(m_results->at(index.row()), 2), translation).c_str();
        }
        else
        {
            return QVariant();
        }
    }
    else
    {
        return QVariant();
    }
 }

 QVariant SearchResultsModel::headerData(int section, Qt::Orientation orientation,
                                         int role) const
 {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        switch (section)
        {
            case translation_column:
                return tr("Translation");
            
            case location_column:
                return tr("Location");

            case text_column:
                return tr("Text");

            default:
                return QVariant();
        }
    else
        return QString("%1").arg(section);
 }

 boost::shared_ptr<VerseDisplay> SearchResultsModel::get_verse_display(const QModelIndex &index)
 {
     if (index.column() == text_column)
         return boost::shared_ptr<VerseDisplay>(new VerseDisplay(m_results->translation_at(index.row()), m_results->at(index.row()), 2));
     else
         return boost::shared_ptr<VerseDisplay>(new VerseDisplay(m_results->translation_at(index.row()), -1, -1));
 }
