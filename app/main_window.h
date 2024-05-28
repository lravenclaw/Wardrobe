#pragma once

#include <QDebug>
#include <QLabel>
#include <QLocale>
#include <QMainWindow>
#include <QThread>
#include <QtCore/QVariant>
#include <QtWidgets>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListView>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStylePainter>

#include "core/model/item_info.h"
#include "core/controller/item_controller.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QTextEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow();
    explicit MainWindow(const QString &fileName);

    void tile();

   private slots:
    void open();
    bool save();
    void about();

   private:
    void init();
    void createActions();
    void createStatusBar();
    void openFile(const QString &fileName);
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName) const;
    static QString strippedName(const QString &fullFileName);
    MainWindow *findMainWindow(const QString &fileName) const;

    QString m_curFileName;
    ItemController* m_itemController = nullptr;
};