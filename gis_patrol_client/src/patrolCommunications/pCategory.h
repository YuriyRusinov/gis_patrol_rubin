/*
 * @brief Класс, описывающий категорию средств коммуникации
 * pCategory.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QMap>
#include <QMetaType>
#include <QSharedPointer>
#include <QVariant>

class pCategoryType;
class pParameter;
class pCatParameter;

class pCategory {
public:
    pCategory(qint64 id=-1, QString name=QString(), QString code=QString(), QSharedPointer< pCategoryType > pCatType=nullptr);
    pCategory(const pCategory& PCat);
    ~pCategory();

    qint64 getId() const;
    void setId( qint64 id );

    QString getName() const;
    void setName( QString name );

    QString getCode() const;
    void setCode( QString code );

    QString getDesc() const;
    void setDesc( QString desc );

    QSharedPointer< pCategoryType > getType() const;
    void setType( QSharedPointer< pCategoryType > pct );

    QSharedPointer< pCategory > getTableCat() const;
    void setTableCat( QSharedPointer< pCategory > tCat );

    QMap< qint64, QSharedPointer< pCatParameter > >& categoryPars();
    const QMap< qint64, QSharedPointer< pCatParameter > >& categoryPars() const;
    void setCategoryPars( const QMap< qint64, QSharedPointer< pCatParameter > >& cpars );
    QList< qint64 > searchParametersByType(int pType ) const;

    void clearPars();
    void addParam( qint64 idParam, QSharedPointer< pCatParameter > p );
    int removeParam( qint64 idParam );

    bool isMain() const;
    void setMain( bool val );

    bool isSystem() const;
    void setSystem( bool val );
private:
    qint64 _idCat;
    QString _nameCat;
    QString _codeCat;
    QString _descCat;
    QSharedPointer< pCategoryType > _typeCat;

    QSharedPointer< pCategory > _childCat;

    QMap< qint64, QSharedPointer< pCatParameter > > _categoryParams;

    bool _isMainCat;
    bool _isSystemCat;
};

Q_DECLARE_METATYPE (QSharedPointer< const pCategory >);
Q_DECLARE_METATYPE (QSharedPointer< pCategory >);
