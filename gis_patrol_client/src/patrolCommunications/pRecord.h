/*
 * @brief Класс описывает запись в БД 
 * pRecord.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QIcon>
#include <QColor>
#include <QSharedPointer>
#include <QString>

class pRecord {
public:
    pRecord();
    pRecord( qint64 id, const QString& name, const QString& desc=QString(), const QString& code = QString() );
    pRecord( const pRecord& r );
    ~pRecord();

    qint64 getId() const;
    void setId( qint64 id );

    const QString& getUUID() const;
    void setUUID( const QString& u );

    const QIcon& getIcon() const;
    void setIcon( const QIcon& i );

    const QColor& getFillColor() const;
    void setFillColor( const QColor& fc );

    const QColor& getTextColor() const;
    void setTextColor( const QColor& tc );

    const QString& getName() const;
    void setName( const QString& name );

    const QString& getCode() const;
    void setCode( const QString& code );

    const QString& getDesc() const;
    void setDesc( const QString& desc );

    virtual void setParent( QSharedPointer< pRecord > p );
    QSharedPointer< pRecord > getParent() const;

private:
    qint64 _id;// рабочий идентификатор записи, который используется в системе поддержания ссылочной целостности (первичный ключ)
    QString _uuid; // уникальый идентификатор записи в системе генерации уникальных идентификаторов uuid-ossp
    QIcon _icon;// иконка для каждой записи из несистемного справочника. Для системных справочников, а также для тех, где иконка не задана приобретает значение null

    QColor _recordFillColor;// цвет фона при отображении записи в табличном виде
    QColor _recordTextColor;// цвет текста при отображении записи в табличном виде

    QString _name;
    QString _code;
    QString _description;

    QSharedPointer< pRecord > _parent;
};
