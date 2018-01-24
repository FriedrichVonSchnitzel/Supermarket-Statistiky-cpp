#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemWatcher>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

	static const QString filePath;
	QMessageBox msgBox;
	int lines;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void handleFileChange(const QString & path);

private:
    Ui::MainWindow *ui;
    QFileSystemWatcher *watcher;
};

#endif // MAINWINDOW_H
