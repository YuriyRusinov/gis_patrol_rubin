/*
 * @brief Синглтон работы с БД и графикой приложения "Защита-дозор"
 * patrolsingleton.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>
#include "patrolsingleton.h"

PatrolSingleton* PatrolSingleton::_instance = nullptr;

PatrolSingleton* PatrolSingleton::getPatrolS( QObject* parent ) {
    if (!_instance) {
        _instance = new PatrolSingleton( parent );
    }

    return _instance;
}

PatrolSingleton::PatrolSingleton( QObject* parent )
    : QObject( parent ) {

    if (_instance) {
        qFatal("There should be only one PatrolSingleton object");
    }
    _instance = this;
}

PatrolSingleton::~PatrolSingleton() {
    _instance = nullptr;
}
