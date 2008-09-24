#ifndef __STARRED_VERSES_MODEL_H
#define __STARRED_VERSES_MODEL_H

#include <QAbstractListModel>
#include <boost/shared_ptr.hpp>
#include <list>
#include <pair>

class Translation;

class StarredVersesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    StarredVersesModel(boost::shared_ptr<Translation> translation);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

public slots:
    void add_starred_verse(int verse_id, int num_verses_context);

private:
    boost::shared_ptr<Translation> m_translation;
    std::list<std::pair<int, int> > m_starred_verses;
};

#endif // __STARRED_VERSES_MODEL_H
