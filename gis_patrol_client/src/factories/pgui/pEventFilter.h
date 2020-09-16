/*
 * @brief Класс фильтрации событий на форме
 * pEventFilter.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QObject>

class pEventFilter : public QObject
{
public:
    pEventFilter( QObject *parent = nullptr );
    ~pEventFilter( );

protected:
    bool eventFilter( QObject *obj, QEvent *event ) override;

private:
    Q_OBJECT
};
