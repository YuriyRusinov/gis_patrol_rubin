/* @brief Класс - делегат для отображения и редактирования локальных настроек приложения на форме.
 * pSettingsDelegate.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QItemDelegate>

class pSettingsDelegate : public QItemDelegate {
public:
    pSettingsDelegate( QObject* parent = nullptr );

    QWidget* createEditor( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData( QWidget* editor, const QModelIndex& index ) const override;
    void setModelData( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index ) const override;
    void updateEditorGeometry( QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index ) const override;

private:
    Q_OBJECT
};
