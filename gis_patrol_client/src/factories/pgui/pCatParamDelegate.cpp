/*
 * @brief Класс, описывает делегат для отображения-редактирования параметров категории.
 * pCatParamDelegate.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QLineEdit>
#include <QCheckBox>
#include <QIntValidator>

#include "pCatParamDelegate.h"

pCatParamDelegate::pCatParamDelegate( QObject* parent )
    : QItemDelegate( parent )
{
}

QWidget* pCatParamDelegate::createEditor( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    switch( index.column() ) {
        case 1: { 
                  QLineEdit* lE = new QLineEdit( parent );
                  lE->resize( option.rect.size() );
                  return lE;
                  break;
                }
        case 2: case 3: { QCheckBox* cBox = new QCheckBox( parent );
                          //cBox->resize( option.rect.size() );
                          cBox->repaint( option.rect );
                          return cBox;
                          break;
                        }
        case 4: {
                  QLineEdit* lE = new QLineEdit( parent );
                  QValidator* val = new QIntValidator( 1, 100 );
                  lE->setValidator( val );
                  lE->resize( option.rect.size() );
                  return lE;
                  break;
                }
        default: return nullptr;
    }
}

void pCatParamDelegate::setEditorData( QWidget* editor, const QModelIndex& index ) const {
    switch( index.column() ) {
        case 1: {
                    QLineEdit* lE = qobject_cast< QLineEdit* >(editor);
                    lE->setText( index.data( Qt::DisplayRole ).toString() );
                    break;
                }
        case 2: case 3: {
                            QCheckBox* cBox = qobject_cast< QCheckBox* >(editor);
                            Qt::CheckState cs = (Qt::CheckState)index.data( Qt::CheckStateRole ).toInt();
                            cBox->setCheckState ( cs ); break;
                        }
        case 4: {
                    QLineEdit* lE = qobject_cast< QLineEdit* >(editor);
                    lE->setText( QString::number( index.data( Qt::DisplayRole ).toInt() ) );
                    break;
                }
        default: return; break;
    }
}

void pCatParamDelegate::setModelData( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index ) const {
    switch( index.column() ) {
        case 1: {
                    QLineEdit* lE = qobject_cast< QLineEdit* >(editor);
                    QString wText = lE->text();
                    model->setData( index, wText, Qt::EditRole );
                    break;
                }
        case 2: case 3: {
                            QCheckBox* cBox = qobject_cast< QCheckBox* >(editor);
                            Qt::CheckState val = cBox->checkState ( );
                            model->setData( index, val, Qt::CheckStateRole );
                            break;
                        }
        case 4: {
                    QLineEdit* lE = qobject_cast< QLineEdit* >(editor);
                    int order = lE->text().toInt();
                    model->setData( index, order, Qt::UserRole+2 );
                    break;
                }
        default: return; break;
    }
}

void pCatParamDelegate::updateEditorGeometry( QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index ) const {
    if( editor && index.column() < 5)
        editor->setGeometry( option.rect );
}
