#include "mydelegate.h"

MyDelegate::MyDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

// TableView need to create an Editor
// Create Editor when we construct MyDelegate
// and return the Editor
QWidget* MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    QSpinBox *editor = new QSpinBox(parent);
    editor->setMinimum(0);
    editor->setMaximum(100);
    return editor;
}

// Then, we set the Editor
// Gets the data from Model and feeds the data to delegate Editor
void MyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    // Get the value via index of the Model
    int value = index.model()->data(index, Qt::EditRole).toInt();

    // Put the value into the SpinBox
    QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
    spinbox->setValue(value);
}

// When we modify data, this model reflect the change
// Data from the delegate to the model
void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
    spinbox->interpretText();
    int value = spinbox->value();
    model->setData(index, value, Qt::EditRole);
}

// Give the SpinBox the info on size and location
void MyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

