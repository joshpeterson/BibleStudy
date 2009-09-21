#ifndef __UI_SEARCH_WIDGET_H
#define __UI_SEARCH_WIDGET_H

#include <QWidget>
#include <boost/shared_ptr.hpp>

class QAbstractItemModel;
class QPushButton;
class QLineEdit;

class TranslationManager;
class ISearchResults;

//! This class represents a collection of widgets which provide a text input field to input a search string and a button to start the search.
class UISearchWidget : public QWidget
{
    Q_OBJECT

public:
    //! Create a new instance of the UISearchWidget class.
    UISearchWidget(boost::shared_ptr<const TranslationManager> translation_manager, QWidget* parent = 0);

signals:
    //! Inform other widgets that a search has finished.
    void search_complete(boost::shared_ptr<ISearchResults> query);

private slots:
    //! Execute the search.  Note that this is a private slot and cannot be used by other widgets.
    void perform_search();

private:
    boost::shared_ptr<const TranslationManager> m_translation_manager;
    QPushButton* m_search_button;
    QLineEdit* m_search_input_field;
};

#endif //__UI_SEARCH_WIDGET_H
