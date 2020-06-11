/*
 * @brief Класс, описывающий параметры узла связи,
 * pCommNode.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QDomDocument>

class pCommNode {
public:
    pCommNode(QString name=QString(),                          // Наименование
              QString call_sign=QString(),                     // Позывной
              qint64 identification_number=-1,                 // Условный номер
              const QDomDocument& scheme_order=QDomDocument(), // Схема-приказ
              const QDomDocument& scheme_node=QDomDocument(),  // Схема узла
              const QDomDocument& equipment_layout=QDomDocument()  // План размещения оборудования
            );
    pCommNode(const pCommNode& pcn);
    ~pCommNode();

    QString getName() const;
    void setName( QString name );

    QString getCallSign() const;
    void setCallSign( QString cs );

    qint64 getIdentNumber() const;
    void setIdentNumber( qint64 num );

    const QDomDocument& getSchemeOrder() const;
    void setSchemeOrder( const QDomDocument& scheme_order );

    const QDomDocument& getSchemeNode() const;
    void setSchemeNode( const QDomDocument& scheme_node );

    const QDomDocument& getLayout() const;
    void setLayout (const QDomDocument& el);

private:
    QString _name;
    QString _call_sign;
    qint64 _identification_number;
    QDomDocument _scheme_order;
    QDomDocument _scheme_node;
    QDomDocument _equipment_layout;
};
