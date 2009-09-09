#ifndef __UI_SEARCH_WIDGET_H
#define __UI_SEARCH_WIDGET_H

#include <QWidget>
#include <boost/shared_ptr.hpp>

class QAbstractItemModel;
class QPushButton;
class QLineEdit;

class TranslationManager;
class ISearchResults;

class UISearchWidget : public QWidget
{
    Q_OBJECT

public:
    UISearchWidget(boost::shared_ptr<const TranslationManager> translation_manager, QWidget* parent = 0);

signals:
    void search_complete(boost::shared_ptr<ISearchResults> query);

private slots:
    void perform_search();

private:
    boost::shared_ptr<const TranslationManager> m_translation_manager;
    QPushButton* m_search_button;
    QLineEdit* m_search_input_field;
};

#endif //__UI_SEARCH_WIDGET_H
