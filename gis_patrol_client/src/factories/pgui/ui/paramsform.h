/*
 * @brief Форма добавления/редактирования параметра приложения "Защита-дозор"
 * paramsgroupform.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#pragma once

#include <QDialog>
#include <QMap>
#include <QSharedPointer>

namespace Ui {
    class params_form;
}

class pParamType;

class ParamsForm : public QDialog {
public:
    ParamsForm( qint64 id, const QMap< qint64, QSharedPointer< pParamType > >& pTypes, QWidget* parent = nullptr, Qt::WindowFlags flags=Qt::WindowFlags() );
    ~ParamsForm();

    qint64 getId() const;
    void setId( qint64 id );

    QString getName() const;
    void setName( QString pName );

    QString getCode() const;
    void setCode( QString code );

    QString getTitle() const;
    void setTitle( QString title );

    qint64 getType() const;
    QSharedPointer< pParamType > getParamType() const;
    void setParamType( qint64 idType );

    QString getTableName() const;
    void setTableName( QString tName );

    QString getColumnName() const;
    void setColumnName( QString colName );

private slots:
    void cbTypeActivated(int index);

private:
    Ui::params_form* _UI;
    QMap< qint64, QSharedPointer< pParamType > > _pTypes;

private:
    Q_OBJECT
};
