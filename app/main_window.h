#pragma once

#include <QDebug>
#include <QLabel>
#include <QLocale>
#include <QMainWindow>
#include <QThread>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListView>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStylePainter>

#include "core/model/client_info.h"
#include "core/controller/client_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
   private slots:
    //void on_listView_clicked(const QModelIndex &index);
    
   private:
    Ui::MainWindow *ui;
};