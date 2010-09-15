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
class ISerializable;

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
    //! Inform other widgets that a search has started.
    void search_started(QString search_text);

	//! Inform other widgets of the persistence state when a search starts.
	void search_started(boost::shared_ptr<ISerializable> current_search_state);

    //! Inform other widgets that a search has finished.
    void search_complete(boost::shared_ptr<BibleDatabase::ISearchResults> query);
	
	//! Inform other widgets when the persisted parts of the search widget have changed.
	void persistence_state_changed(boost::shared_ptr<ISerializable> current_search_state);

private slots:
    //! Execute the search.  Note that this is a private slot and cannot be used by other widgets.
    void on_perform_search();

    //! Get the search results when the background worker that performs the search has finished.
    void on_search_worker_finished();

	//! Determine when a widget whose state is persisted changes and act accordingly.
	void on_persisted_widget_state_changed();

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
	boost::shared_ptr<ISerializable> get_persisted_state() const;
};

}

#endif //__UI_SEARCH_WIDGET_H
