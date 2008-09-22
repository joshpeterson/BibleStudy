#ifndef __UI_TEXT_VIEW_WIDGET_H
#define __UI_TEXT_VIEW_WIDGET_H

#include <QWidget>
#include <boost/shared_ptr.hpp>

class QLabel;
class QPushButton;
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

private:
    int m_displayed_id;
    int m_displayed_context;
    boost::shared_ptr<Translation> m_translation;
    QLabel* m_title;
    QLabel* m_text;
    QPushButton* m_more_button;
    QPushButton* m_less_button;
    QPushButton* m_star_button;
    QPushButton* m_prev_button;
    QPushButton* m_next_button;
};

#endif // __UI_TEXT_VIEW_WIDGET_H

