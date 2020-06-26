/*
 * @brief Класс описывает тип категории средств коммуникации
 * pCategoryType.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QMetaType>
#include <QSharedPointer>
#include <QString>

class pCategoryType {
public:
    pCategoryType( qint64 id=-1, QString name=QString(), QString desc=QString(), bool isRef=false );
    pCategoryType( const pCategoryType& pct );
    ~pCategoryType();

    qint64 getId() const;
    void setId( qint64 id );

    QString getName() const;
    void setName( QString name );

    QString getDesc() const;
    void setDesc( QString desc );

    bool isReference() const;
    void setReference( bool value );

private:
    qint64 _idCatType;
    QString _name;
    QString _description;
    bool _isReference;
};

Q_DECLARE_METATYPE( QSharedPointer< pCategoryType > );
Q_DECLARE_METATYPE( QSharedPointer< const pCategoryType > );
