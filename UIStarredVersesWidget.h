#ifndef __UI_STARRED_VERSES_WIDGET_H
#define __UI_STARRED_VERSES_WIDGET_H

#include <QWidget>
#include <boost/shared_ptr.hpp>

class QListView;
class Translation;
class StarredVersesModel;

class UIStarredVersesWidget : public QWidget
{
    Q_OBJECT

public:
    UIStarredVersesWidget(boost::shared_ptr<Translation> translation, QWidget* parent = 0);

private:
    boost::shared_ptr<Translation> m_translation;
    QListView* m_starred_verses_view;
    boost::shared_ptr<StarredVersesModel> m_starred_verses_model;
};

#endif // __UI_STARRED_VERSES_WIDGET_H
