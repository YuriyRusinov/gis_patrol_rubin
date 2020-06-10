/*
 * @brief Класс описывает тип центра связи
 * pCommCenterType.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QString>

class pCommCenterType {
public:
    enum pCenterTypes {
        MainCenter=0,
        ReserveCenter=1,
        AlternativeCenter=2
    };

    pCommCenterType(int type=0, QString name=QString(), QString shortName=QString());
    pCommCenterType(const pCommCenterType& pct);
    ~pCommCenterType();

    pCenterTypes getType() const;
    void setType(int type);

    QString getName() const;
    void setName( QString name );

    QString getShortName() const;
    void setShortName( QString sName );

private:
    pCenterTypes _type;
    QString _name;
    QString _shortName;
};
