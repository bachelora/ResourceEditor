#include "mainwindow.h"
#include <QFile>
#include <QtWidgets>

MainWindow::MainWindow()
  {
      QWidget *widget = new QWidget;
      setCentralWidget(widget);

      QWidget *topFiller = new QWidget;
      topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

      infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                                "invoke a context menu</i>"));
      infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
      infoLabel->setAlignment(Qt::AlignCenter);

      QWidget *bottomFiller = new QWidget;
      bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

      QVBoxLayout *layout = new QVBoxLayout;
      //layout->setCanvasMargin(5);
      layout->addWidget(topFiller);
      layout->addWidget(infoLabel);
      layout->addWidget(bottomFiller);
      widget->setLayout(layout);

      createActions();
      createMenus();

      QString message = tr("A context menu is available by right-clicking");
      statusBar()->showMessage(message);

      setWindowTitle(tr("Menus"));
      setMinimumSize(160, 160);
      resize(480, 320);
  }

  #ifndef QT_NO_CONTEXTMENU
  void MainWindow::contextMenuEvent(QContextMenuEvent *event)
  {
      QMenu menu(this);
//      menu.addAction(cutAct);
//      menu.addAction(copyAct);
//      menu.addAction(pasteAct);
      menu.exec(event->globalPos());
  }
  #endif // QT_NO_CONTEXTMENU

  void MainWindow::newFile()
  {
      infoLabel->setText(tr("Invoked <b>File|New</b>"));
  }

  void MainWindow::open()
  {
     // infoLabel->setText(tr("Invoked <b>File|Open</b>"));
      qDebug()<<"open file...";

      //定义文件对话框类
      QFileDialog *fileDialog = new QFileDialog(this);

        //定义文件对话框标题
      fileDialog->setWindowTitle(tr("打开Json文件"));

      //设置默认文件路径
      fileDialog->setDirectory(".");

      //设置文件过滤器
     fileDialog->setNameFilter(tr("Json(*.json)"));

      //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
      fileDialog->setFileMode(QFileDialog::ExistingFiles);

     //设置视图模式
     fileDialog->setViewMode(QFileDialog::Detail);

     //打印所有选择的文件的路径
     QStringList fileNames;

     if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
     }

     for (auto tmp : fileNames){
          inputJsonFilePath = tmp;
          qDebug() << inputJsonFilePath ;//<< QT::endl;
          readJson(inputJsonFilePath);
          break;
      }
  }

  void MainWindow::save()
  {
      infoLabel->setText(tr("Invoked <b>File|Save</b>"));
  }

  void MainWindow::about()
  {
      infoLabel->setText(tr("Invoked <b>Help|About</b>"));
      QMessageBox::about(this, tr("About Menu"),
              tr("The <b>Menu</b> example shows how to create "
                 "menu-bar menus and context menus."));
  }

  void MainWindow::aboutQt()
  {
      infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
  }

  void MainWindow::createActions()
  {
      newAct = new QAction(tr("&New"), this);
      newAct->setShortcuts(QKeySequence::New);
      newAct->setStatusTip(tr("Create a new file"));
      connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

      openAct = new QAction(tr("&Open..."), this);
      openAct->setShortcuts(QKeySequence::Open);
      openAct->setStatusTip(tr("Open an existing file"));
      connect(openAct, &QAction::triggered, this, &MainWindow::open);

      saveAct = new QAction(tr("&Save as"), this);
      saveAct->setShortcuts(QKeySequence::Save);
      saveAct->setStatusTip(tr("Save the document to disk"));
      connect(saveAct, &QAction::triggered, this, &MainWindow::save);


      exitAct = new QAction(tr("E&xit"), this);
      exitAct->setShortcuts(QKeySequence::Quit);
      exitAct->setStatusTip(tr("Exit the application"));
      connect(exitAct, &QAction::triggered, this, &QWidget::close);

      aboutAct = new QAction(tr("&About"), this);
      aboutAct->setStatusTip(tr("Show the application's About box"));
      connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

      aboutQtAct = new QAction(tr("About &Qt"), this);
      aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
      connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
      connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);

  }

  void MainWindow::createMenus()
  {
      fileMenu = menuBar()->addMenu(tr("&File"));
      fileMenu->addAction(newAct);
      fileMenu->addAction(openAct);
      fileMenu->addAction(saveAct);
      fileMenu->addSeparator();
      fileMenu->addAction(exitAct);



      helpMenu = menuBar()->addMenu(tr("&Help"));
      helpMenu->addAction(aboutAct);
      helpMenu->addAction(aboutQtAct);

  }

void MainWindow::readJson(QString &path){
    QFile file(path);//参数就是文件的路径
   //设置打开方式
   file.open(QIODevice::ReadOnly);
   //用QTextStream类去读取文本信息
    QTextStream QS(&file);

   //用QString类去接收读取的信息
    QString array=QS.readAll();
         //将读取到的数据放入textEdit中
      //   ui->textEdit->setText(array);
         //关闭文件对象
   file.close();

   qDebug() << array ;
//    QFile file(path);

//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;

//    QTextStream in(&file);

//    while (!in.atEnd()) {
//        QString line = in.readLine();
//        qDebug() << line ;
//    }
}

