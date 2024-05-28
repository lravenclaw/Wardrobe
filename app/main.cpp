#include <QDebug>
#include <QLabel>
#include <QLocale>
#include <QThread>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListView>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStylePainter>

#include "core/model/item_info.h"
#include "app/main_window.h"
#include "core/controller/item_controller.h"


int main(int argc, char** argv) {
	QApplication app(argc, argv);

    MainWindow window;
    window.show();
	
    return app.exec();
}
