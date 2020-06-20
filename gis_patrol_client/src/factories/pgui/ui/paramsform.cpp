/*
 * @brief Форма добавления/редактирования параметра приложения "Защита-дозор"
 * paramsgroupform.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "paramsform.h"
#include "ui_params_form.h"

ParamsForm::ParamsForm( qint64 id, const QMap<int, QString>& pTypes, QWidget* parent, Qt::WindowFlags flags )
    : QDialog( parent, flags),
    _UI( new Ui::params_form ) {
    _UI->setupUi(this);
    _UI->lEId->setText( QString::number( id ) );
    for (QMap<int, QString>::const_iterator pt = pTypes.constBegin();
         pt != pTypes.constEnd();
         pt++) {
        _UI->cbType->addItem( pt.value(), pt.key() );
    }
    QObject::connect(_UI->cbType, QOverload<int>::of(&QComboBox::activated), this, QOverload<int>::of(&ParamsForm::cbTypeActivated) );
}

ParamsForm::~ParamsForm() {
    delete _UI;
}

qint64 ParamsForm::getId() const {
    return _UI->lEId->text().toLongLong();
}

QString ParamsForm::getName() const {
    return _UI->lEName->text();
}

QString ParamsForm::getCode() const {
    return _UI->lECode->text();
}

QString ParamsForm::getTitle() const {
    return _UI->lETitle->text();
}

int ParamsForm::getType() const {
    return _UI->cbType->currentData().toInt();
}

QString ParamsForm::getTableName() const {
   if (getType() != 2 && getType() != 17)
       return QString();

   return _UI->lETableName->text();
}

QString ParamsForm::getColumnName() const {
   if (getType() != 2 && getType() != 17)
       return QString();

   return _UI->lEColumnName->text();
}

void ParamsForm::cbTypeActivated(int index) {
    bool isEnable = _UI->cbType->itemData(index).toInt() == 2 || 
                    _UI->cbType->itemData(index).toInt() == 17;
    _UI->gbTable->setEnabled( isEnable );
}
