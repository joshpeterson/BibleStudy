#ifndef __UI_TEXT_VIEW_WIDGET_H
#define __UI_TEXT_VIEW_WIDGET_H

#include <QWidget>
#include <boost/shared_ptr.hpp>

class QLabel;
class QTextEdit;
class QToolButton;

namespace BibleDatabase
{
class TranslationManager;
class VerseDisplay;
}

namespace BibleStudyGui
{

class StarredVersesModel;
class ISerializable;

//! This class respresents a text box that displays a collection of verses and allows the user to star, unstar a verse and navigate a translation.
class UITextViewWidget : public QWidget
{
    Q_OBJECT

public:
    //! Create a new instance of the UITextViewWidget class.
    UITextViewWidget(boost::shared_ptr<const BibleDatabase::TranslationManager> translation_manager,
                     boost::shared_ptr<StarredVersesModel> starred_verses_model, QWidget* parent = 0);

signals:
    //! Let other widgets know that the user has starred a verse.
    void verse_starred(boost::shared_ptr<BibleDatabase::VerseDisplay> verse);

    //! Let other widgets know that the user has removed the star from a starred verse.
    void verse_unstarred(boost::shared_ptr<BibleDatabase::VerseDisplay> verse);

    //! Inform other widgets when the persisted parts of the text view have changed.
    void persistence_state_changed(boost::shared_ptr<ISerializable> displayed_verse_state);

public slots:
    //! Display a new verse.
    void display_text(boost::shared_ptr<BibleDatabase::VerseDisplay> verse);

private slots:
    void increase_displayed_context();
    void decrease_displayed_context();
    void display_next_verse();
    void display_prev_verse();
    void change_star_button_icon();
    void change_starred_verse_state();

private:
    boost::shared_ptr<const BibleDatabase::TranslationManager> m_translation_manager;
    boost::shared_ptr<StarredVersesModel> m_starred_verses_model;
    
    boost::shared_ptr<BibleDatabase::VerseDisplay> m_displayed_verse;
    QLabel* m_title;
    QTextEdit* m_text;
    QToolButton* m_more_button;
    QToolButton* m_less_button;
    QToolButton* m_star_button;
    QToolButton* m_prev_button;
    QToolButton* m_next_button;

    bool next_button_should_be_enabled();
    bool prev_button_should_be_enabled();
    bool more_button_should_be_enabled();
    bool less_button_should_be_enabled();
    bool star_button_should_be_enabled();
};

}

#endif // __UI_TEXT_VIEW_WIDGET_H

