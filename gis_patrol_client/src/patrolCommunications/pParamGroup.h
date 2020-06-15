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
#include <memory>

using std::shared_ptr;

class pParamGroup {
public:
    pParamGroup(qint64 id=-1, QString name=QString(), pParamGroup* parent=nullptr );
    pParamGroup(const pParamGroup& PG);
    ~pParamGroup();

    qint64 getId() const;
    void setId( qint64 id );

    QString getName() const;
    void setName( QString name );

    shared_ptr< pParamGroup > getParent() const;
    void setParent( shared_ptr< pParamGroup > parent );

private:
    qint64 _id;
    QString _name;
    shared_ptr< pParamGroup > _parentGroup;
};
