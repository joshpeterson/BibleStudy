#include "UIStarredVersesWidget.h"

UIStarredVersesWidget::UIStarredVersesWidget(boost::shared_ptr<Translation> translation, QWidget* parent) :
    QWidget(parent),
    m_translation(translation)
{
}