#include "SearchResultsModel.h"
#include "IVerse.h"

SearchResultsModel::SearchResultsModel(const Translation* translation, 
                                       ISearchResults* results,
                                       QObject* parent) :
    QAbstractTableModel(parent),
    m_translation(translation),
    m_results(results)
{
}

void SearchResultsModel::SetResults(const IEntry::ISearchResultsPtr results)
{
    m_results = results;
    this->reset();
}

 int SearchResultsModel::rowCount(const QModelIndex &parent) const
 {
     if (m_results)
        return m_results->num_results();
     else
         return 0;
 }

 int SearchResultsModel::columnCount(const QModelIndex &parent) const
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

    if (role != Qt::DisplayRole)
        return QVariant();
    else
    {
        switch (index.column())
        {
            case translation_column:
                return QString("Douay-Rheims");
            
            case book_column:
                return m_translation->get_entry(m_results->at(index.row()))->get_book().c_str();

            case chapter_column:
                return m_translation->get_entry(m_results->at(index.row()))->get_chapter();

            case verse_column:
                return m_translation->get_entry(m_results->at(index.row()))->get_verse();

            case text_column:
                return m_translation->get_entry(m_results->at(index.row()))->get_text().c_str();
            
            default:
                return QVariant();
        }
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
            
            case book_column:
                return tr("Book");

            case chapter_column:
                return tr("Chapter");

            case verse_column:
                return tr("Verse");

            case text_column:
                return tr("Text");

            default:
                return QVariant();
        }
    else
        return QString("%1").arg(section);
 }

