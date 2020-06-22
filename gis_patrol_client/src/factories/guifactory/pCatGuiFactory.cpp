/*
 * @brief Класс-фабрика, управляющий визуальным отображением категорий
 * pCatGuiFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <patroldbloader.h>
#include <patroldbwriter.h>

#include "pCatGuiFactory.h"

pCatGuiFactory::pCatGuiFactory( pDBLoader* dbLoader, pDBWriter* dbWriter, QObject* parent )
    : QObject( parent ), _dbLoader( dbLoader), _dbWriter( dbWriter ) {
}

pCatGuiFactory::~pCatGuiFactory() {
}

QWidget* pCatGuiFactory::GUICatView( QWidget* parent, Qt::WindowFlags flags ) {
    Q_UNUSED( parent );
    Q_UNUSED( flags );
    return nullptr;
}
