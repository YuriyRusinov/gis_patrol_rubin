/*
 * @brief Класс описывает информационный объект, являющийся справочником или документом
 * pIObject.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QDateTime>
#include <QColor>
#include <QSharedPointer>

class pCategory;

class pIObject
{
public:
    pIObject( );
    pIObject( qint64 id,
              QSharedPointer< pCategory > pCat,
              QString name,
              QString description = QString());
    pIObject( const pIObject& io );
    ~pIObject( );

private:
    qint64 _id;
    QSharedPointer< pCategory > _pCategory;
    QString _name;
    QString _description;
    QString _tableName;

    QDateTime _insertTime;
    /* Определает происхождение ИО.
     * Если ИО является системным, то он существует в системе изначально 
     * при ее установке, если не является системным, то он создается 
     * пользователями во время их работы.
     * Как правило, системные ИО являются контейнерными, т.е. справочниками.
     * Системные ИО удалить нельзя. Можно только модифицировать 
     * (добавлять, удалять, изменять) их экземпляры ИО. */
    bool _isSystem;
    qint64 _idUser;
    int _idMaclabel;

}; /* -----  end of class PIObject  ----- */

