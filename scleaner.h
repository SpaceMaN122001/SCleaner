#ifndef SCLEANER_H
#define SCLEANER_H

#include <QMainWindow>
#include <QToolButton>
#include <QDirIterator>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <Windows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class SCleaner; }
QT_END_NAMESPACE

class SCleaner : public QMainWindow
{
    Q_OBJECT

public:
    SCleaner(QWidget *parent = nullptr);
    ~SCleaner();
private slots:
    void on_quitToolButton_clicked();

    void on_scanToolButton_clicked();

    void on_clearToolButton_clicked();

private:
    Ui::SCleaner *ui;
    QString _pathToAppData;
    UINT _filesCount;
private:
    VOID setCustomButtonStyle(QToolButton& button, QString imagePath, QString toolTip);
    UINT getNumberOfIterations(QString path);
};
#endif // SCLEANER_H
