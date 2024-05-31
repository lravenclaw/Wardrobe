#include "app/main_window.h"

MainWindow::MainWindow() {
    init();
}

MainWindow::MainWindow(const QString &fileName)
    : MainWindow() {

    loadFile(fileName);
}

void MainWindow::open() {
    const QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        m_curFileName = fileName;
        loadFile(fileName);
    }
}

void MainWindow::loadFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Aplication"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    m_itemController->loadItems(file); 
}

bool MainWindow::save() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    m_curFileName);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void MainWindow::about()
{
   QMessageBox::about(this, tr("About app"),
            tr("The Wardrobe app is a small application that demonstrates how to "
               "deal with your personal wardrobe data."));
}

void MainWindow::init() {
    m_itemController = ItemController::instance();
    if (m_itemController == nullptr) {
        m_itemController = ItemController::init();
    }

    auto* listView = new QListView;

    listView->setResizeMode(QListView::Adjust);
    listView->setWordWrap(true);
    listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listView->setModel(m_itemController);
    listView->showNormal();

    listView->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                            QAbstractItemView::DoubleClicked);

    setCentralWidget(listView);

    createActions();
    createStatusBar();

    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::createActions() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QToolBar *fileToolBar = addToolBar(tr("File"));

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    QAction *saveAct = new QAction(saveIcon, tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAct);
    fileToolBar->addAction(saveAct);

    fileMenu->addSeparator();

    QAction *closeAct = fileMenu->addAction(tr("&Close"), this, &QWidget::close);
    closeAct->setShortcut(tr("Ctrl+W"));
    closeAct->setStatusTip(tr("Close this window"));

    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), qApp, &QApplication::closeAllWindows);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));

    [[maybe_unused]] QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    [[maybe_unused]] QToolBar *editToolBar = addToolBar(tr("Edit"));

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));

    QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
}

void MainWindow::createStatusBar() {
    statusBar()->showMessage(tr("Ready"));
}

bool MainWindow::saveFile(const QString &fileName) const {
    QString errorMessage;

    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        m_itemController->saveItems(file);
    } else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                       .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(nullptr, tr("Application"), errorMessage);
        return false;
    }
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}