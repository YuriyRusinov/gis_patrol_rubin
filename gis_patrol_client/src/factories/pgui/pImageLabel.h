/*
 * @brief Класс-виджет для параметров изображений
 * pImageLabel.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include "pAbstractParamWidget.h"

#include <QPixmap>

class QLabel;
class QToolButton;

class pParamValue;

class pImageLabel : public pAbstractParamWidget {
public:
    pImageLabel( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pImageLabel();
    
    void setReadOnly( bool value ) override;

    const QPixmap & pixmap() const;
    QByteArray save();

public slots:
    
    void setVal( const QString& newJpg );
    void openFile( );
    void setPixmap( const QString& contents );

private slots:
    void setImagePrivate( );
    void clearImage();

private:
    void setup( ) override;

private:
    QLabel* _lParam;
    QPixmap _px;
    QLabel* _lImage;
    QToolButton* _tbParam;
    QToolButton* _tbClear;

private:
    Q_OBJECT
};
