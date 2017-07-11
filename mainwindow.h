#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
private slots:
    void on_pushButton_clicked();

    void on_CreateSgaredMemmory_clicked();

    void on_ReadSharedMemmory_clicked();

    void on_WriteSharedMemmory_clicked();

    void on_CloseSharedMemmory_clicked();

    void on_CreateSharedFile_clicked();

    void on_ReadSharedFile_clicked();

    void on_WriteSharedFile_clicked();

    void on_CloseSharedFile_clicked();

private:
    Ui::MainWindow *ui;

    PVOID p_SharedMem = NULL;
    HANDLE hFileMap = NULL;
    PVOID p_SharedFile = NULL;
    HANDLE hFileMap2 = NULL;
    HANDLE hSharedFile = NULL;
signals:
     void CopyData(QString str);
};

#endif // MAINWINDOW_H
