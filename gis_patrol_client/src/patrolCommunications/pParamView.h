/*
 * @brief Класс управляющий порядком просмотра-редактирования значения параметра узла связи,
 * в зависимости от его типа
 * pParamView.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QString>

class pParamView {
public:
    pParamView( qint64 id=-1, QString name=QString() );
    pParamView( const pParamView& PV );
    ~pParamView();

    qint64 getId() const;
    void setId( qint64 id );

    QString getName() const;
    void setName( QString name );

private:
    qint64 _id;
    QString _name;
};
