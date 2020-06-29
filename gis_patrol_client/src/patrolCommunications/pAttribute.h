/*
 * @brief Абстрактный класс, описывающий параметры/группу параметров узла связи,
 * pAttribute.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

class pAttribute {
public:
    virtual int getEntity() const=0;
    virtual qint64 getId() const=0;
};
