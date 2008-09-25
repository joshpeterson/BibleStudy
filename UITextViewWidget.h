#ifndef __UI_TEXT_VIEW_WIDGET_H
#define __UI_TEXT_VIEW_WIDGET_H

#include <QWidget>
#include <boost/shared_ptr.hpp>

class QLabel;
class QTextEdit;
class QPushButton;
class QToolButton;
class Translation;

class UITextViewWidget : public QWidget
{
    Q_OBJECT

public:
    UITextViewWidget(boost::shared_ptr<Translation> translation, QWidget* parent = 0);

public slots:
    void display_text(int unique_id, int num_entries_context);
    void increase_displayed_context();
    void decrease_displayed_context();
    void display_next_verse();
    void display_prev_verse();

private:
    int m_displayed_id;
    int m_displayed_context;
    boost::shared_ptr<Translation> m_translation;
    QLabel* m_title;
    QTextEdit* m_text;
    QToolButton* m_more_button;
    QToolButton* m_less_button;
    QPushButton* m_star_button;
    QPushButton* m_prev_button;
    QPushButton* m_next_button;

    bool next_button_should_be_enabled();
    bool prev_button_should_be_enabled();
    bool more_button_should_be_enabled();
    bool less_button_should_be_enabled();
    bool star_button_should_be_enabled();
};

#endif // __UI_TEXT_VIEW_WIDGET_H

