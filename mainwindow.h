#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtWidgets/qtableview.h"
#include <QMainWindow>
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>
#include "mydelegate.h"

  class QAction;
  class QActionGroup;
  class QLabel;
  class QMenu;

  struct ItemType
  {
      QString name;
      QString url;
      QString link;
      ItemType(QString& n,QString& u,QString& l):name(n),url(u),link(l){
      }
  };


  class MainWindow : public QMainWindow
  {
      Q_OBJECT

  public:
      MainWindow();

      // QStandardItemModel provides a classic
      // item-based approach to working with the model.
      QStandardItemModel *model;

      // Make a member pointer to a new MyDelegate instance
      MyDelegate *myDelegate;

  protected:
  #ifndef QT_NO_CONTEXTMENU
      void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
  #endif // QT_NO_CONTEXTMENU

      void readJson(QString &path);
  private slots:
      void newFile();
      void open();
      void save();
      void about();
      void aboutQt();

  private:
      void createActions();
      void createMenus();

      QMenu *fileMenu;
      QMenu *helpMenu;
      QActionGroup *alignmentGroup;
      QAction *newAct;
      QAction *openAct;
      QAction *saveAct;
      QAction *exitAct;
      QAction *aboutAct;
      QAction *aboutQtAct;
   //   QLabel *infoLabel;

      QTableView *tableView;
  private:
    QString inputJsonFilePath;
    QVector<ItemType> itemsArray;
  };

  #endif
