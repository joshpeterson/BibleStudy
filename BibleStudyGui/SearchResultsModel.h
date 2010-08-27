#ifndef __SEARCH_RESULTS_MODEL_H
#define __SEARCH_RESULTS_MODEL_H

#include <QAbstractTableModel>
#include "../BibleDatabase/Translation.h"
#include "../BibleDatabase/ISearchResults.h"

namespace BibleDatabase
{
class VerseDisplay;
class TranslationManager;
}

namespace BibleStudyGui
{

//! This class is an implementation of a model from the Qt Model/View framework for a table view which displays the results of a search.
class SearchResultsModel : public QAbstractTableModel
{
public:
    //! Create a new instance of the SearchResultsModel class.
    SearchResultsModel(boost::shared_ptr<const BibleDatabase::TranslationManager> translation_manager, QObject* parent = 0);

    //! Set the ISearchResults object that this model should use to obtain data.
    void SetResults(boost::shared_ptr<const BibleDatabase::ISearchResults> results);

    //! Get a VerseDisplay object corresponding to the verse at the given index.
    boost::shared_ptr<BibleDatabase::VerseDisplay> get_verse_display(const QModelIndex& index);

    //! Get the number of rows for the given parent index.  This should be the number of verses in the results.
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    //! Get the number of columns for the given parent index.  This is always 5.
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    //! Get the data that should be displayed for the given index in the given role DisplayRole, ToolTipRole).
    QVariant data(const QModelIndex &index, int role) const;

    //! Get the header data that should be displayed for the given index.
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    enum ColumnType
    {
        translation_column = 0,
        book_column = 1,
        chapter_column = 2,
        verse_column = 3,
        text_column = 4
    };

private:
    boost::shared_ptr<const BibleDatabase::TranslationManager> m_translation_manager;
    boost::shared_ptr<const BibleDatabase::ISearchResults> m_results;
};

}

#endif // __SEARCH_RESULTS_MODEL_H
