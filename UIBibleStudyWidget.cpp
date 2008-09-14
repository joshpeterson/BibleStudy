#include <boost/shared_ptr.hpp>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include "UIBibleStudyWidget.h"
#include "UISearchWidget.h"
#include "UISearchResultsWidget.h"
#include "IEntry.h"
#include "SearchResultsSerial.h"
#include "Translation.h"
#include "SearchResultsModel.h"

UIBibleStudyWidget::UIBibleStudyWidget(boost::shared_ptr<Translation> translation, QWidget *parent) :
    QWidget(parent),
    m_search(new UISearchWidget(translation)),
    m_results_view(new QTableView),
    m_layout(new QVBoxLayout),
    m_results_model(new SearchResultsModel(translation.get(), NULL))
{
    QObject::connect(m_search, SIGNAL(search_complete(IEntry::ISearchResultsPtr)),
                     this, SLOT(display_search_results(IEntry::ISearchResultsPtr)));
    
    //QObject::connect(m_results_view, SIGNAL(search_results_updated()), this, SLOT(refresh_search_results()));

    m_results_view->setSortingEnabled(true);
    m_results_view->setShowGrid(false);
    QHeaderView* header = m_results_view->horizontalHeader();
    header->setResizeMode(QHeaderView::ResizeToContents);
    header->setStretchLastSection(true);

    m_results_view->setModel(m_results_model.get());

    m_layout->addWidget(m_search);
    m_layout->addWidget(m_results_view);

    m_results_view->hide();

    setLayout(m_layout);
}

void UIBibleStudyWidget::display_search_results(IEntry::ISearchResultsPtr query)
{
    m_results_model->SetResults(query);
    m_results_view->show();

    //emit search_results_updated();
}

void UIBibleStudyWidget::refresh_search_results()
{
    //m_results_view->updateGeometry();
    //m_results_view->show();
}

