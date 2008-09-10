#ifndef __UI_SEARCH_WIDGET_H
#define __UI_SEARCH_WIDGET_H

#include <QWidget>
#include <boost/shared_ptr.hpp>
#include "IEntry.h"

class QAbstractItemModel;
class QPushButton;
class QLineEdit;

class Translation;

class UISearchWidget : public QWidget
{
    Q_OBJECT

public:
    UISearchWidget(boost::shared_ptr<Translation> translation, QWidget* parent = 0);

signals:
    void search_complete(IEntry::ISearchResultsPtr query);

private slots:
    void perform_search();

private:
    boost::shared_ptr<Translation> m_translation;
    QPushButton* m_search_button;
    QLineEdit* m_search_input_field;
};

#endif //__UI_SEARCH_WIDGET_H
