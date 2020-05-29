/*
 * @brief Синглтон работы с БД и графикой приложения "Защита-дозор"
 * patrolsingleton.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#pragma once

#include <QObject>

class PatrolSingleton : public QObject {
public:
    static PatrolSingleton* getPatrolS( QObject* parent=nullptr );

private:
    PatrolSingleton(QObject* parent=nullptr);
    PatrolSingleton(const PatrolSingleton& ps) = delete;
    PatrolSingleton& operator=(const PatrolSingleton& ps) = delete;
    ~PatrolSingleton();

    static PatrolSingleton* _instance;
private:
    Q_OBJECT
};
