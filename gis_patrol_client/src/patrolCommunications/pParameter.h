/*
 * @brief Класс, описывающий параметр узла связи,
 * pParameter.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QString>
#include <QSharedPointer>

#include "pAttribute.h"

class pParamType;
class pParamGroup;

class pParameter : public pAttribute {
public:
    pParameter(qint64 id=-1, QSharedPointer< pParamType > pType=nullptr, QSharedPointer< pParamGroup > pGroup=nullptr, QString pCode=QString(), QString pName=QString(), QString pTitle=QString(), QString tableName=QString(), QString columnName=QString(), bool isSystem=false);
    pParameter(const pParameter& P1);
    ~pParameter();

    qint64 getId() const override;
    void setId( qint64 id );

    QSharedPointer< const pParamType > getParamType() const;
    QSharedPointer< pParamType > getParamType();
    void setParamType( QSharedPointer< pParamType > pType );

    QSharedPointer< const pParamGroup > getParamGroup() const;
    QSharedPointer< pParamGroup > getParamGroup();
    void setParamGroup( QSharedPointer< pParamGroup > pGroup);

    QString getCode() const;
    void setCode( QString code );

    QString getName() const;
    void setName( QString name );

    QString getTitle() const;
    void setTitle( QString title );

    QString getTableName() const;
    void setTableName( QString tableName );

    QString getColumnName() const;
    void setColumnName( QString columnName );

    bool getSystem() const;
    void setSystem( bool isSys );

    int getEntity() const override;

    QSharedPointer< const pParamType > getRefParamType() const;
    QSharedPointer< pParamType > getRefParamType();
    void setRefParamType( QSharedPointer< pParamType > pRefType );

private:
    qint64 _id;
    QSharedPointer< pParamType > _pType;
    QSharedPointer< pParamGroup > _pGroup;
    QString _code;
    QString _name;
    QString _title;
    QString _tableName;
    QString _columnName;
    bool _isSystem;
    QSharedPointer< pParamType > _pRefType;
};

Q_DECLARE_METATYPE( pParameter );
Q_DECLARE_METATYPE( QSharedPointer< pParameter > );
