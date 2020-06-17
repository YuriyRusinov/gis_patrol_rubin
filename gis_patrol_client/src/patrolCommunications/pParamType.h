/*
 * @brief Класс, описывающий тип параметра узла связи,
 * pParamType.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QString>
#include <memory>

using std::shared_ptr;

class pParamView;

class pParamType {
public:
    enum PatrolParamTypes : qint64 {
        atUndef = -1,               // не задан
        atBool = 1,                 // логический
        atList = 2,                 // элемент справочника
        atParent = 3,               // родитель (ссылка на элемент того же справочника)
        atDate = 4,                 // дата
        atDateTime = 5,             // дата-время без указания временной зоны
        atDateTimeWithOffset = 6,   // дата-время с указанием временной зоны
        atDouble = 7,               // вещественное значение
        atInt = 8,                  // целочисленное значение
        atString = 9,               // строка
        atInterval = 10,            // Временной интервал (сутки)
        atText = 13,                // Текст
        atFixString = 14,           // Строка фиксированной длины
        atImage = 15,               // Изображение
        atCheckListEx = 17,         // Набор элементов справочника
        atRecordColor = 18,         // Цвет записи в справочнике (фон) при отображении в списке
        atRecordColorRef = 19,      // Ссылка на цвет фона записи (при отображении в списке)
        atXML = 20,                 // xml-документ
        atIntervalH = 21,           // временной интервал (часов, минут, секунд)
        atSVG = 23,                 // Объект SVG
        atVideo = 24,               // Видео-ролик
        atRecordTextColor = 25,     // Цветовая гамма текста записи справочника (при отображении в списке)
        atRecordTextColorRef = 26,  // Ссылка на цвет текста записи (при отображении в списке)
        atTime = 27,                // Время
        atGeometry = 28,            // ГИС-объект
        atGeography = 29,           // ГИС-объект (geography)
        atInt64 = 30,               // Целочисленное значение (64 бита)
        atUUID = 31,                // Уникальный идентификатор (UUID)
        atComplex = 32,             // Составной атрибут
        atHistogram = 33,           // Гистограмма
        atGISMap = 36,              // ГИС-объект (карта)
        atJSON = 37,                // Объект JSON
        atJSONb = 38,               // Бинарный объект JSON
        atDateTimeEx = 39,          // Дата-время (с миллисекундами)
        atBinary = 40,              // Бинарные данные
        atSysChildCategoryRef = 41, // Служебный атрибут. Ссылка на категорию таблицы справочника. 
                                    // Добавляется автоматически. Работать с ним запрещено
        atUserDef = 42              // Пользовательский ( for the future use )
    };

    pParamType( qint64 id=-1, QString name=QString(), QString code=QString(), pParamView* pView=nullptr );
    pParamType( const pParamType& PT );
    ~pParamType();

    PatrolParamTypes getId() const;
    void setId( qint64 id );

    shared_ptr< pParamView > getView() const;
    void setView( shared_ptr< pParamView > pView );

    QString getName() const;
    void setName( QString name );

    QString getCode() const;
    void setCode( QString code );

private:
    PatrolParamTypes _id;
    QString _name;
    QString _code;
    shared_ptr< pParamView > _pView;
};
