/*
 * @brief Класс, описывающий параметры центра управления связью,
 * pCommCenter.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QString>
#include <memory>

using std::shared_ptr;

class pCommCenterType;

class pCommCenter {
public:
    pCommCenter(QString name=QString(), pCommCenterType* pType=nullptr);
    pCommCenter(const pCommCenter& PC);
    ~pCommCenter();

    QString getName() const;
    void setName(QString name);

    shared_ptr< pCommCenterType > getType() const;
    void setType( shared_ptr< pCommCenterType > pType );

private:
    QString _name;
    shared_ptr< pCommCenterType > _pType;
};
