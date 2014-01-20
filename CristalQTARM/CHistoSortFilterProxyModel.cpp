#include "CHistoSortFilterProxyModel.h"

#include "header_qt.h"

CHistoSortFilterProxyModel::CHistoSortFilterProxyModel(const int& arg_rowPerPage)
    :m_rowPerPage(arg_rowPerPage), m_numPage(0), QSortFilterProxyModel()
{
    qDebug() << "m_rowPerPage(arg_rowPerPage)" << m_rowPerPage;
    this->setDynamicSortFilter(true);
}


bool CHistoSortFilterProxyModel::filterAcceptsRow(int source_row,const QModelIndex & source_parent ) const
{
    if(    source_row > (m_rowPerPage*m_numPage) -1 
        && source_row < (m_rowPerPage* (m_numPage+1))  )
        return true;
    return false;
    
}

void CHistoSortFilterProxyModel::slotNextPage()
{
    int nbRow = sourceModel()->rowCount();
    m_nbPage = nbRow/m_rowPerPage;
    if(m_numPage < m_nbPage)
        ++m_numPage;   
    emit filterChanged();
    emit pageChanged();
}

void CHistoSortFilterProxyModel::slotPrevPage()
{
    int nbRow = sourceModel()->rowCount();
    m_nbPage = nbRow/m_rowPerPage;
    if(m_numPage > 0)
        --m_numPage;
    emit filterChanged();
    emit pageChanged();
}

int CHistoSortFilterProxyModel::getNbPage()
{
    if(sourceModel())
    {
        int nbPage = sourceModel()->rowCount()/m_rowPerPage;
        ++nbPage;
        return (nbPage);
    }
    return 3;
}
