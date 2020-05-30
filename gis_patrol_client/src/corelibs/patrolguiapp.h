/*
 * @brief Класс работы с БД и графикой приложения "Защита-дозор"
 * patrolguiapp.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#pragma once

#include <QObject>

class GISPatrolDatabase;

class PatrolGuiApp : public QObject {
public:
    bool GUIConnect(const QMap<int, QString>& accLevels, QWidget* parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags());

private:
    friend class PatrolSingleton;

    PatrolGuiApp(GISPatrolDatabase* db, QObject* parent=nullptr);
    PatrolGuiApp(const PatrolGuiApp& pga) = delete;
    PatrolGuiApp& operator=(const PatrolGuiApp& pga) = delete;
    virtual ~PatrolGuiApp();

    mutable GISPatrolDatabase* _dataBase;
private:
    Q_OBJECT
};
