/*
 * @brief Класс, описывающий группу, содержащую параметр узла связи,
 * pParamGroup.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QString>
#include <QSharedPointer>
#include <QMap>

#include "pAttribute.h"

class pParameter;

class pParamGroup : public pAttribute {
public:
    pParamGroup(qint64 id=-1, QString name=QString(), QSharedPointer< pParamGroup > parent=nullptr );
    pParamGroup(const pParamGroup& PG);
    ~pParamGroup();

    qint64 getId() const override;
    void setId( qint64 id );

    QString getName() const;
    void setName( QString name );

    QSharedPointer< pParamGroup > getParent() const;
    void setParent( QSharedPointer< pParamGroup > parent );

    const QMap< qint64, QSharedPointer< pParamGroup > >& getChildGroups() const;
    void setChildGroups( const QMap< qint64, QSharedPointer< pParamGroup > >& childGroups );

    void clearChildGroups();
    void addChildGroup( qint64 id, QSharedPointer< pParamGroup > pChildG );

    const QMap< qint64, QSharedPointer< pParameter > >& getParameters() const;
    void setParameters( const QMap< qint64, QSharedPointer< pParameter > >& params );

    void clearParameters();
    void addParameter( pParameter* param );

    QSharedPointer< const pParamGroup > childGroupForId (qint64 id, bool recursive=true) const;
    QSharedPointer< pParamGroup > childGroupForId (qint64 id, bool recursive=true);

    int getEntity() const override;
private:
    qint64 _id;
    QString _name;
    QSharedPointer< pParamGroup > _parentGroup;
    QMap< qint64, QSharedPointer< pParamGroup > > _childGroups;

    QMap< qint64, QSharedPointer< pParameter > > _parameters;
};

Q_DECLARE_METATYPE( pParamGroup );
Q_DECLARE_METATYPE( QSharedPointer< pParamGroup > );
