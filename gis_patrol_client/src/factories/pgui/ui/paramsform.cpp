/*
 * @brief Форма добавления/редактирования параметра приложения "Защита-дозор"
 * paramsgroupform.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QRegExpValidator>
#include <pParamType.h>
#include "paramsform.h"
#include "ui_params_form.h"

ParamsForm::ParamsForm( qint64 id, const QMap< qint64, QSharedPointer< pParamType> >& pTypes, QWidget* parent, Qt::WindowFlags flags )
    : QDialog( parent, flags),
    _UI( new Ui::params_form ),
    _pTypes( pTypes ) {
    _UI->setupUi(this);
    _UI->lEId->setText( QString::number( id ) );
    for (QMap< qint64, QSharedPointer< pParamType > >::const_iterator pt = pTypes.constBegin();
         pt != pTypes.constEnd();
         pt++) {
        _UI->cbType->addItem( pt.value()->getName(), pt.key() );
    }
    QObject::connect(_UI->cbType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, QOverload<int>::of(&ParamsForm::cbTypeActivated) );
    if (id < 0)
        _UI->cbType->setCurrentIndex( -1 );
    else
        _UI->cbType->setEnabled( false );
    QRegExp cRegExp(QString("[A-Za-z0-9_]*"));
    QValidator* codeVal = new QRegExpValidator(cRegExp, this);
    _UI->lECode->setValidator( codeVal );
}

ParamsForm::~ParamsForm() {
    delete _UI;
}

qint64 ParamsForm::getId() const {
    return _UI->lEId->text().toLongLong();
}

void ParamsForm::setId( qint64 id ) {
    _UI->lEId->setText( QString::number (id) );
    _UI->cbType->setEnabled( id<= 0 );
}

QString ParamsForm::getName() const {
    return _UI->lEName->text();
}

void ParamsForm::setName( QString pName ) {
    _UI->lEName->setText( pName );
}

QString ParamsForm::getCode() const {
    return _UI->lECode->text();
}

void ParamsForm::setCode( QString code ) {
    _UI->lECode->setText( code );
    QRegExp cRegExp(QString("[A-Za-z0-9]*"));
    QValidator* codeVal = new QRegExpValidator(cRegExp, this);
    _UI->lECode->setValidator( codeVal );
}

QString ParamsForm::getTitle() const {
    return _UI->lETitle->text();
}

void ParamsForm::setTitle( QString title ) {
    _UI->lETitle->setText( title );
}

qint64 ParamsForm::getType() const {
    return _UI->cbType->currentData().toLongLong();
}

QString ParamsForm::getTableName() const {
    if (getType() == pParamType::atList || getType() == pParamType::atCheckListEx)
        return _UI->lETableName->text();

    return QString();
}

void ParamsForm::setTableName( QString tName ) {
    _UI->lETableName->setText( tName );
}

QString ParamsForm::getColumnName() const {
    if (getType() == pParamType::atList || getType() == pParamType::atCheckListEx)
        return _UI->lEColumnName->text();

    return QString();
}

void ParamsForm::setColumnName( QString colName ) {
    _UI->lEColumnName->setText( colName );
}

void ParamsForm::cbTypeActivated(int index) {
    bool isEnable = _UI->cbType->itemData(index).toInt() == pParamType::atList || 
                    _UI->cbType->itemData(index).toInt() == pParamType::atCheckListEx;
    _UI->gbTable->setEnabled( isEnable );
}

void ParamsForm::setParamType( qint64 idType ) {
    QMap< qint64, QSharedPointer< pParamType > >::const_iterator ppt = _pTypes.constFind( idType );
    if (ppt == _pTypes.constEnd())
        return;
    int ind = 0;
    for (QMap< qint64, QSharedPointer< pParamType > >::const_iterator wppt = _pTypes.constBegin();
            wppt != ppt;
            wppt++)
        ind++;
    _UI->cbType->setCurrentIndex( ind );
}

QSharedPointer< pParamType > ParamsForm::getParamType() const {
    QMap< qint64, QSharedPointer< pParamType > >::const_iterator ppt = _pTypes.constFind( _UI->cbType->currentData().toLongLong() );
    return ppt.value();
}
