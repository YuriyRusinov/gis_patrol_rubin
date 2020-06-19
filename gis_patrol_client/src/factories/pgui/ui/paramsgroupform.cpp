/*
 * @brief Форма добавления/редактирования группы параметров приложения "Защита-дозор"
 * paramsgroupform.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "paramsgroupform.h"
#include "ui_params_group_form.h"

ParamsGroupForm::ParamsGroupForm( qint64 id, QString name, QString parentName, QWidget* parent, Qt::WindowFlags flags )
    : QDialog( parent, flags ),
    _UI( new Ui::params_group_form ) {
    _UI->setupUi( this );
    _UI->lEId->setText( QString::number( id ) );
    _UI->lEName->setText( name );
    _UI->lEParent->setText( parentName );
    QObject::connect( _UI->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept );
    QObject::connect( _UI->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject );
}

ParamsGroupForm::~ParamsGroupForm() {
    delete _UI;
}

qint64 ParamsGroupForm::getId() const {
    return _UI->lEId->text().toLongLong();
}

QString ParamsGroupForm::getName() const {
    return _UI->lEName->text();
}

QString ParamsGroupForm::getParentName() const {
    return _UI->lEParent->text();
}
