/* @brief Класс - делегат для отображения и редактирования локальных настроек приложения на форме.
 * pSettingsDelegate.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QLineEdit>
#include "pSettingsDelegate.h"

pSettingsDelegate::pSettingsDelegate( QObject* parent )
    : QItemDelegate( parent ) {
}

QWidget* pSettingsDelegate::createEditor( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    switch( index.column() ) {
        case 0: default: return nullptr;
        case 1: { 
                  QLineEdit* lE = new QLineEdit( parent );
                  lE->resize( option.rect.size() );
                  return lE;
                  break;
                }
    }
}

void pSettingsDelegate::setEditorData( QWidget* editor, const QModelIndex& index ) const {
    switch( index.column() ) {
        case 0: default: return; break;
        case 1: {
                    QLineEdit* lE = qobject_cast< QLineEdit* >(editor);
                    lE->setText( index.data( Qt::DisplayRole ).toString() );
                    break;
                }
    }
}

void pSettingsDelegate::setModelData( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index ) const {
    switch( index.column() ) {
        case 0: default: return; break;
        case 1: {
                    QLineEdit* lE = qobject_cast< QLineEdit* >(editor);
                    QString wText = lE->text();
                    model->setData( index, wText, Qt::EditRole );
                    break;
                }
    }
}

void pSettingsDelegate::updateEditorGeometry( QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index ) const {
    if( editor && index.column() == 1 )
        editor->setGeometry( option.rect );
}
