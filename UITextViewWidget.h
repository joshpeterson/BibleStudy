#ifndef __UI_TEXT_VIEW_WIDGET_H
#define __UI_TEXT_VIEW_WIDGET_H

#include <QWidget>
#include <boost/shared_ptr.hpp>

class QLabel;
class QTextEdit;
class QToolButton;
class Translation;
class VerseDisplay;
class StarredVersesModel;

class UITextViewWidget : public QWidget
{
    Q_OBJECT

public:
    UITextViewWidget(boost::shared_ptr<Translation> translation,
                     boost::shared_ptr<StarredVersesModel> starred_verses_model, QWidget* parent = 0);

signals:
    void verse_starred(boost::shared_ptr<VerseDisplay> verse);
    void verse_unstarred(boost::shared_ptr<VerseDisplay> verse);

public slots:
    void display_text(boost::shared_ptr<VerseDisplay> verse);

private slots:
    void increase_displayed_context();
    void decrease_displayed_context();
    void display_next_verse();
    void display_prev_verse();
    void change_star_button_icon();
    void change_starred_verse_state();

private:
    boost::shared_ptr<StarredVersesModel> m_starred_verses_model;
    
    boost::shared_ptr<VerseDisplay> m_displayed_verse;
    boost::shared_ptr<Translation> m_translation;
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

#endif // __UI_TEXT_VIEW_WIDGET_H

