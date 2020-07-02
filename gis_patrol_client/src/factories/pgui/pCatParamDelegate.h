/*
 * @brief Класс, описывает делегат для отображения-редактирования параметров категории.
 * pCatParamDelegate.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once			/*  */

#include <QItemDelegate>

class pCatParamDelegate : public QItemDelegate {
public:
    pCatParamDelegate( QObject* parent = nullptr );

    QWidget* createEditor( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData( QWidget* editor, const QModelIndex& index ) const override;
    void setModelData( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index ) const override;
    void updateEditorGeometry( QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index ) const override;

private:
    Q_OBJECT
};
