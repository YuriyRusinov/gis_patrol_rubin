/*
 * @brief Данный класс унаследован от QItemDelegate и предназначен для управления визуальным отображением
 * pItemDelegate.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once			/*  */

#include <QItemDelegate>

class pItemDelegate : public QItemDelegate {
public:
    pItemDelegate( QObject* parent=nullptr );
    ~pItemDelegate();

    QWidget* createEditor( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index ) const override;

private:
    Q_OBJECT
};
