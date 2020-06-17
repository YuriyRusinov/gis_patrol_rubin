/*
 * @brief Класс, описывающий визуальную модель параметров, сгруппированных по подходящим пользовательским группам
 * pParamModel.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <pParamGroup.h>
#include <pParameter.h>
#include "pParamModel.h"

ParametersModel::ParametersModel( const QMap< qint64, QSharedPointer< pParamGroup > >& paramGroups, QObject* parent )
    : QAbstractItemModel( parent ),
    _paramGroups( paramGroups ) {
}

ParametersModel::~ParametersModel() {}

int ParametersModel::columnCount( const QModelIndex& parent) const {
    Q_UNUSED( parent );
    return 8;
}

int ParametersModel::rowCount( const QModelIndex& parent) const {
    if (!parent.isValid()) {
        return _paramGroups.size();
    }
    void* par = parent.internalPointer();
    pParamGroup* pgr = static_cast<pParamGroup*>(par);
    if (!pgr)
        return 0;
    QMap< qint64, QSharedPointer<pParamGroup> > childGroups = pgr->getChildGroups();
    QMap< qint64, QSharedPointer<pParameter> > pParams = pgr->getParameters();
    int nchild = childGroups.size();
    int npar = pParams.size();

    return nchild+npar;
}

QModelIndex ParametersModel::index(int row, int column, const QModelIndex& parent) const {
    if (parent.isValid()) {
        void* par = parent.internalPointer();
        pParamGroup* pgr = static_cast<pParamGroup*>(par);
        if (pgr == nullptr)
            return QModelIndex();
        QMap< qint64, QSharedPointer<pParamGroup> > childGroups = pgr->getChildGroups();
        int nchild = childGroups.size();
        QMap< qint64, QSharedPointer<pParameter> > pParams = pgr->getParameters();
        if (row < nchild ) {
            //
            // Дочерняя подгруппа
            //
            QMap< qint64, QSharedPointer<pParamGroup> >::const_iterator pch = childGroups.constBegin()+row;
            return createIndex(row, column, pch.value().get());
        }
        else if (row < nchild + pParams.size()) {
            //
            // Параметр
            //
            int rowParam = row - nchild;
            QMap< qint64, QSharedPointer<pParameter> >::const_iterator ppar = pParams.constBegin()+rowParam;
            return createIndex(row, column, ppar.value().get());
        }
        else
            return QModelIndex();
    }
    else {
        //
        // Для верхнего уровня у нас есть только группы
        //
        QMap< qint64, QSharedPointer<pParamGroup> >::const_iterator pch = _paramGroups.constBegin()+row;
        return createIndex(row, column, pch.value().get());
    }
}

QModelIndex ParametersModel::parent(const QModelIndex& index) const {
    void* par = index.internalPointer();
    pParamGroup* pgr = static_cast<pParamGroup*>(par);
    if (pgr == nullptr) {
        pParameter* ppar = static_cast<pParameter>(par);
        if (ppar == nullptr)
            return QModelIndex();
    }
}

QVariant ParametersModel::data(const QModelIndex& index, int role) const {
}

QVariant ParametersModel::headerData(int section, Qt::Orientation orientation, int role) const {
}
