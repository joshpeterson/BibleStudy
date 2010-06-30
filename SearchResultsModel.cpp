#include <vector>
#include <boost/shared_ptr.hpp>
#include "SearchResultsModel.h"
#include "BibleDatabase/TranslationManager.h"
#include "BibleDatabase/Verse.h"
#include "BibleDatabase/VerseDisplay.h"

using namespace BibleStudy;
using namespace BibleDatabase;

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
    return 5;
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
        else if (column == book_column)
        {
            boost::shared_ptr<const Translation> translation = m_translation_manager->at(m_results->translation_at(index.row()));
            return translation->get_verse(m_results->at(index.row()))->get_book().c_str();;
        }
        else if (column == chapter_column)
        {
            boost::shared_ptr<const Translation> translation = m_translation_manager->at(m_results->translation_at(index.row()));
            return translation->get_verse(m_results->at(index.row()))->get_chapter();
        }
        else if (column == verse_column)
        {
            boost::shared_ptr<const Translation> translation = m_translation_manager->at(m_results->translation_at(index.row()));
            return translation->get_verse(m_results->at(index.row()))->get_verse();
        }
        else if (column == text_column)
        {
            boost::shared_ptr<const Translation> translation = m_translation_manager->at(m_results->translation_at(index.row()));
            return translation->get_verse(m_results->at(index.row()))->get_text().c_str();
        }
        else
        {
            return QVariant();
        }
    }
    else if (role == Qt::ToolTipRole)
    {
        int column = index.column();
        if (column == translation_column)
        {
            boost::shared_ptr<const Translation> translation = m_translation_manager->at(m_results->translation_at(index.row()));
            return translation->get_long_name().c_str();
        }
        else if (column == text_column)
        {
            boost::shared_ptr<const Translation> translation = m_translation_manager->at(m_results->translation_at(index.row()));
            translation = m_translation_manager->at(m_results->translation_at(index.row()));
            return verse_collection_to_title_and_string_wrapped(translation->get_verse(m_results->at(index.row()), 0), translation).c_str();
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
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            switch (section)
            {
                case translation_column:
                    return tr("T");
                
                case book_column:
                    return tr("Book");
                
                case chapter_column:
                    return tr("Ch");

                case verse_column:
                    return tr("V");

                case text_column:
                    return tr("Verse Text");

                default:
                    return QVariant();
            }
        else
            return QString("%1").arg(section);
    }
    else if (role == Qt::ToolTipRole)
    {
        if (orientation == Qt::Horizontal)
            switch (section)
            {
                case translation_column:
                    return tr("Translation");
                
                case chapter_column:
                    return tr("Chapter");

                case verse_column:
                    return tr("Verse");

                default:
                    return QVariant();
            }
    }

    return QVariant();
 }

 boost::shared_ptr<VerseDisplay> SearchResultsModel::get_verse_display(const QModelIndex &index)
 {
     if (index.column() == text_column)
         return boost::shared_ptr<VerseDisplay>(new VerseDisplay(m_results->translation_at(index.row()), m_results->at(index.row()), 2));
     else
         return boost::shared_ptr<VerseDisplay>(new VerseDisplay(m_results->translation_at(index.row()), -1, -1));
 }
