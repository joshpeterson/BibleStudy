#ifndef __BROWSE_VERSES_MODEL_H
#define __BROWSE_VERSES_MODEL_H

#include <boost/shared_ptr.hpp>
#include <QAbstractItemModel>

class TranslationManager;
class VerseDisplay;

//! This class is an implementation of a model from the Qt Model/View framework for a tree view that is used to browse the verses of multiple translations.
class BrowseVersesModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    //! Create a new instance of the BrowseVerseModel, using a given TranslationManager.
    BrowseVersesModel(boost::shared_ptr<const TranslationManager> translation_manager, QObject *parent = 0);

    //! Get the data that should be displayed in the view for the given index.
    QVariant data(const QModelIndex &index, int role) const;

    //! This method is required by the Qt Model/View framework, although I'm not certain what it does.
    Qt::ItemFlags flags(const QModelIndex &index) const;

    //! Get the data for the view header that should be displayed in the view for the given index.
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    //! Get the index of for the given row and column.
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    //! Get the parent of the given index.
    QModelIndex parent(const QModelIndex &index) const;

    //! Get the number of rows directly under the current parent index.
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    //! Get the number of columns for the given parent index.  Note that this is always 1.
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    //! Get the VerseDisplay object corresponding to the given index in the model.
    boost::shared_ptr<VerseDisplay> get_verse_display(const QModelIndex &index) const;

private:
    boost::shared_ptr<const TranslationManager> m_translation_manager;
};

#endif //__BROWSE_VERSES_MODEL_H
