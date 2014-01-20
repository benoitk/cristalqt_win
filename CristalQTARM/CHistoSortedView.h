#ifndef HISTO_SORTED_VIEW
#define HISTO_SORTED_VIEW

#include <QWidget>

class QLabel;
class QLineEdit;
class QListView;
class QHBoxLayout;
class QAbstractItemModel;
class CHistoSortFilterProxyModel;
class QPushButton;
class CDialogHistorique;

class CHistoSortedView : public QWidget
{
    Q_OBJECT

public:
    explicit CHistoSortedView( CDialogHistorique *parent = 0 );
    ~CHistoSortedView();

    void setModel( QAbstractItemModel* model );
public slots:
    void slotChangePage();
    void slotNextPage();
    void slotPrevPage();

private:
    CDialogHistorique* m_parent;
    CHistoSortFilterProxyModel *m_filter;
    QHBoxLayout *m_layout;
    QListView  *m_listView;
    /*QPushButton * m_btNext;
    QPushButton * m_btPrev;*/

    int m_nbPage;
    int m_numPage;

};


#endif //HISTO_SORTED_VIEW