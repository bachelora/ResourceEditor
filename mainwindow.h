#ifndef MAINWINDOW_H
#define MAINWINDOW_H

  #include <QMainWindow>

  class QAction;
  class QActionGroup;
  class QLabel;
  class QMenu;

  class MainWindow : public QMainWindow
  {
      Q_OBJECT

  public:
      MainWindow();

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
      QLabel *infoLabel;
  };

  #endif
