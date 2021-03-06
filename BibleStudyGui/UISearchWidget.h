#ifndef __UI_SEARCH_WIDGET_H
#define __UI_SEARCH_WIDGET_H

#include <vector>
#include <QWidget>
#include <boost/shared_ptr.hpp>

class QAbstractItemModel;
class QPushButton;
class QLineEdit;
class QHBoxLayout;
class QCheckBox;

namespace BibleDatabase
{
class TranslationManager;
class ISearchResults;
class Translation;
class ICommand;
}

namespace BibleStudyGui
{

class BackgroundWorker;

//! This class represents a collection of widgets which provide a text input field to input a search string and a button to start the search.
class UISearchWidget : public QWidget
{
    Q_OBJECT

public:
    //! Create a new instance of the UISearchWidget class.
    UISearchWidget(boost::shared_ptr<const BibleDatabase::TranslationManager> translation_manager, QWidget* parent = 0);

public slots:
    //! Display the translation check boxes in the UI
    void display_translation_check_boxes();

signals:
    //! Inform other widegst that a searcg has started.
    void search_started(QString search_text);

    //! Inform other widgets that a search has finished.
    void search_complete(boost::shared_ptr<BibleDatabase::ISearchResults> query);

private slots:
    //! Execute the search.  Note that this is a private slot and cannot be used by other widgets.
    void perform_search();

    //! Get the search results when the background worker that performs the search has finished.
    void search_worker_finished();

private:
    boost::shared_ptr<const BibleDatabase::TranslationManager> m_translation_manager;
    QPushButton* m_search_button;
    QLineEdit* m_search_input_field;
    QHBoxLayout* m_translation_selection_row;
    QCheckBox* m_match_case_checkbox;
    QCheckBox* m_match_whole_word_checkbox;
    std::vector<QCheckBox*> m_translation_checkboxes;
    boost::shared_ptr<BibleDatabase::ICommand> m_command_perform_search;
    boost::shared_ptr<BackgroundWorker> m_search_worker;

    void add_translation_check_box(boost::shared_ptr<const BibleDatabase::Translation> translation);
};

}

#endif //__UI_SEARCH_WIDGET_H
