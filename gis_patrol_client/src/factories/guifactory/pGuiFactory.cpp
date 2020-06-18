/*
 * @brief Класс-фабрика, управляющий визуальным отображением записей
 * pGuiFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QWidget>
#include <QtDebug>
#include <patroldbloader.h>
#include <pParamListForm.h>
#include <pParamModel.h>
#include "pGuiFactory.h"

PGUIFactory::PGUIFactory(pDBLoader* dbLoader, QObject* parent )
    : QObject( parent ), _dbLoader ( dbLoader ) {
}

PGUIFactory::~PGUIFactory () {
}

QWidget* PGUIFactory::GUIView(QWidget* parent, Qt::WindowFlags flags) {
    QWidget* w = new QWidget( parent, flags );
    emit viewWidget( w );
    return w;
}

QWidget* PGUIFactory::GUIViewParams(bool mode, QWidget* parent, Qt::WindowFlags flags) {
    ParamListForm* plf = new ParamListForm( mode, parent, flags );
    QMap< qint64, QSharedPointer< pParamGroup > > pGroups = _dbLoader->loadGroupedParameters();
    ParametersModel* pMod = new ParametersModel( pGroups );
    plf->setParamsModel( pMod );
    qDebug() << __PRETTY_FUNCTION__ << pGroups.size();
    if (!mode)
        emit viewWidget( plf );
    return plf;
}
