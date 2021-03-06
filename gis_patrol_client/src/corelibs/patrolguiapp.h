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
class pSettings;

class PatrolGuiApp : public QObject {
public:
    bool GUIConnect(const QMap<int, QString>& accLevels, QWidget* parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags());
    void disconnectFromDb();
    virtual pSettings* getPatrolSettings();

private slots:
    void dbDisconnected();

signals:
    void disconnected();

private:
    friend class PatrolSingleton;

    PatrolGuiApp(GISPatrolDatabase* db, QObject* parent=nullptr);
    PatrolGuiApp(const PatrolGuiApp& pga) = delete;
    PatrolGuiApp& operator=(const PatrolGuiApp& pga) = delete;
    virtual ~PatrolGuiApp();

    mutable GISPatrolDatabase* _dataBase;
    mutable pSettings* _patrolSettings;
private:
    Q_OBJECT
};
