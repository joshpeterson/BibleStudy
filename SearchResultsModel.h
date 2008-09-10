#include <QAbstractTableModel>
#include "IEntry.h"
#include "Translation.h"
#include "ISearchResults.h"

class SearchResultsModel : public QAbstractTableModel
{
public:
    SearchResultsModel(const Translation* translation, ISearchResults* results, QObject* parent = 0);
    void SetResults(const IEntry::ISearchResultsPtr results);


    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
private:
    const Translation* m_translation;
    IEntry::ISearchResultsPtr m_results;

    enum ColumnType
    {
        translation_column = 0,
        book_column = 1,
        chapter_column = 2,
        verse_column = 3,
        text_column = 4
    };
};