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
#include <memory>

using std::shared_ptr;

class pParamType;
class pParamGroup;

class pParameter {
public:
    pParameter(qint64 id=-1, pParamType* pType=nullptr, pParamGroup* pGroup=nullptr, QString pCode=QString(), QString pName=QString(), QString pTitle=QString(), QString tableName=QString(), QString columnName=QString(), bool isSystem=false);
    pParameter(const pParameter& P1);
    ~pParameter();

    qint64 getId() const;
    void setId( qint64 id );

    shared_ptr< pParamType > getParamType() const;
    void setParamType( shared_ptr< pParamType > pType );

    shared_ptr< pParamGroup > getParamGroup() const;
    void setParamGroup( shared_ptr< pParamGroup > pGroup );

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

private:
    qint64 _id;
    shared_ptr< pParamType > _pType;
    shared_ptr< pParamGroup > _pGroup;
    QString _code;
    QString _name;
    QString _title;
    QString _tableName;
    QString _columnName;
    bool _isSystem;
};
