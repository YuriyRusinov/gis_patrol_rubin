/*
 * @brief Класс фильтрации событий на форме
 * pEventFilter.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QEvent>
#include <QMouseEvent>
#include <QTreeView>
#include "pEventFilter.h"

pEventFilter::pEventFilter( QObject *parent )
    : QObject( parent ) {
}

pEventFilter::~pEventFilter( ) {
}

bool pEventFilter::eventFilter( QObject *obj, QEvent *event ) {
    if( obj->parent() && obj->parent()->inherits ("QTreeView") && event->type() == QEvent::MouseButtonPress ) {
        QMouseEvent * mEvent = dynamic_cast<QMouseEvent *> (event);

        if( mEvent && mEvent->button() != Qt::LeftButton )
            return QObject::eventFilter( obj, event );

        QTreeView * treeObj = qobject_cast<QTreeView *>( obj->parent() );
        QPoint p (mEvent->x(), mEvent->y());
        QModelIndex index = treeObj->indexAt (p);
        if( index.isValid() )
            return false;
        else {
            if( treeObj )
                if( treeObj->selectionModel() ) 
                    treeObj->selectionModel()->setCurrentIndex( index, QItemSelectionModel::Clear );
            
            return true;
        }
    }
    else
        return QObject::eventFilter( obj, event );
}
