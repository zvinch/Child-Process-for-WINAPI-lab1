#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <windows.h>
#include <QString>
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(CopyData(QString)), ui->labelWMCOPYDATA, SLOT(setText(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_clicked()
{


        std::cout << ui->lineEdit->text().toUtf8().data();

}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    wchar_t MyMessage [] = L"MESSAGELAB1";
    UINT msg_id = RegisterWindowMessage(MyMessage);
    MSG* msg = static_cast<MSG*>(message);
        if(msg->message ==  msg_id)
        {
            *result = 0;
            LPARAM param = msg->lParam;
            QMessageBox::information(this, "Info", QString::number((int) param));
            return true;
        }
        if(msg->message == WM_COPYDATA)
        {

            COPYDATASTRUCT * data = (COPYDATASTRUCT *) msg->lParam;

            QString str((char*)data->lpData);
             emit CopyData(str);

            *result = 0;
            return true;
        }

        return false;
}

void MainWindow::on_CreateSgaredMemmory_clicked()
{
    if (hFileMap==NULL)
    {
        hFileMap = CreateFileMapping
            (INVALID_HANDLE_VALUE,

            0,
            PAGE_READWRITE,
            0,
            100,
            L"ShareMemory");

        p_SharedMem = static_cast<char*>(
          MapViewOfFile
            (hFileMap,

            FILE_MAP_READ|FILE_MAP_WRITE,
            0,
            0,
            0));

    }


}

void MainWindow::on_ReadSharedMemmory_clicked()
{
    if (hFileMap != NULL)
    {
        char* pp = static_cast<char*>(p_SharedMem);
        QString str = QString::fromUtf8(pp);
        ui->lineEditContentsOfSharedMemmory->setText(str);
    }


}

void MainWindow::on_WriteSharedMemmory_clicked()
{
    if (hFileMap != NULL)
    {
        char* pp = static_cast<char*>(p_SharedMem);
        QString str = ui->AddToSharedMemmoryEdit->text();
        char* tmp = str.toUtf8().data();
        //strcpy(pp, tmp);
        MoveMemory((void*)pp,(void*)tmp, str.length());

        ui->AddToSharedMemmoryEdit-> setText("");
    }

}

void MainWindow::on_CloseSharedMemmory_clicked()
{
    if (hFileMap != NULL)
    {

        UnmapViewOfFile(p_SharedMem);
        CloseHandle(hFileMap);
        hFileMap=NULL;
        p_SharedMem=NULL;

    }

}

void MainWindow::on_CreateSharedFile_clicked()
{
    if (hFileMap2==NULL)
    {
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = 0;
    sa.bInheritHandle = true;
//    hSharedFile = CreateFile(
//                L"C:\\shared_file.txt",
//                GENERIC_READ | GENERIC_WRITE,
//                FILE_SHARE_READ | FILE_SHARE_WRITE,
//                &sa,
//                CREATE_ALWAYS,
//                FILE_ATTRIBUTE_NORMAL,
//                0);

        hFileMap2 = CreateFileMapping
            (INVALID_HANDLE_VALUE,
            0,
            PAGE_READWRITE,
            0,
            100,
            L"SharedFile");

        p_SharedFile = static_cast<char*>(
          MapViewOfFile
            (hFileMap2,

            FILE_MAP_READ|FILE_MAP_WRITE,
            0,
            0,
            0));

    }

}

void MainWindow::on_ReadSharedFile_clicked()
{
    if (hFileMap2 != NULL)
    {
        char* pp = static_cast<char*>(p_SharedFile);
        QString str = QString::fromUtf8(pp);
        ui->lineEdit_FromSharedFile->setText(str);
    }

}

void MainWindow::on_WriteSharedFile_clicked()
{
    if (hFileMap2 != NULL)
    {
        char* pp = static_cast<char*>(p_SharedFile);
        QString str = ui->lineEdit_ToSharedFile->text();
        char* tmp = str.toUtf8().data();
        //strcpy(pp, tmp);

        MoveMemory((void*)pp,(void*)tmp, str.length());
        //ui->lineEdit_ToSharedFile-> setText("");
    }

}

void MainWindow::on_CloseSharedFile_clicked()
{
    if (hFileMap2 != NULL)
    {

        UnmapViewOfFile(p_SharedFile);
        CloseHandle(hFileMap2);
        CloseHandle(hSharedFile);
        hFileMap2=NULL;
        p_SharedFile=NULL;
        hSharedFile=NULL;

    }


}
