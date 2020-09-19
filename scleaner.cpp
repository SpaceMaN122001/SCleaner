#include "scleaner.h"
#include "ui_scleaner.h"

SCleaner::SCleaner(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SCleaner)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/res/cleaner.png"));
    setCustomButtonStyle(*ui->clearToolButton, ":/res/cleaner.png", "Очистить");
    setCustomButtonStyle(*ui->quitToolButton, ":/res/exit.png", "Выход");
    setCustomButtonStyle(*ui->scanToolButton, ":/res/scan.png", "Сканировать");
    ui->mainTabWidget->setTabIcon(0, QIcon(":/res/cleaning.png"));
    ui->mainTabWidget->setTabVisible(1, false);
    ui->mainTabWidget->setTabVisible(2, false);
    ui->clearToolButton->hide();
    ui->progressLineLabel->hide();
    ui->progressBar->hide();
    ui->cleaningParametersGroupBox->hide();
    ui->tempoparyFilesGroupBox->hide();
    ui->filesCountLabel->setText("");
    ui->filesSizeLabel->setText("");
    ui->regeditCheckBox->hide();

    ui->cleaningInforListWidget->addItem(new QListWidgetItem(QIcon(""),"Привет " + QDir::home().dirName() + "!"));
    _pathToAppData = "C:\\Users\\" + QDir::home().dirName() + "\\AppData\\Local\\Temp";
}

SCleaner::~SCleaner()
{
    delete ui;
}

VOID SCleaner::setCustomButtonStyle(QToolButton& button, QString imagePath, QString toolTip)
{
    QSize iconSize(38, 38);
    QPixmap map(imagePath);
    QIcon icon(map);
    button.setIcon(icon);
    button.setIconSize(iconSize);
    button.setStyleSheet("QToolButton { background-color: transparent; }");
    button.setToolTip(toolTip);
}


void SCleaner::on_quitToolButton_clicked()
{
    QApplication::quit();
}

void SCleaner::on_scanToolButton_clicked()
{
    _filesCount = getNumberOfIterations(_pathToAppData);

    ui->cleaningInforListWidget->clear();
    ui->progressLineLabel->show();
    ui->progressLineLabel->setText("");
    ui->progressBar->show();
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(_filesCount);

    UINT filesSize = 0;

    QDirIterator it(_pathToAppData, QDirIterator::Subdirectories);

    while(it.hasNext()) {

        QFileInfo file(it.next());

        if(file.fileName() != '.' && file.fileName() != "..") {

            filesSize += file.size();

            ui->progressLineLabel->setText(file.absoluteFilePath());
            ui->progressLineLabel->repaint();
            ui->cleaningInforListWidget->addItem(new QListWidgetItem(QIcon(""),file.absoluteFilePath()));
            ui->progressBar->setValue(ui->progressBar->value() + 1);
        }
    }

    ui->progressLineLabel->hide();
    ui->progressLineLabel->setText("");
    ui->progressBar->hide();
    ui->progressBar->setValue(0);
    ui->scanToolButton->hide();
    ui->clearToolButton->show();
    ui->cleaningParametersGroupBox->show();
    ui->tempoparyFilesGroupBox->show();
    ui->filesSizeLabel->setText(QString::number(filesSize / 1024 / 1024));
    ui->filesCountLabel->setText(QString::number(_filesCount));
}

UINT SCleaner::getNumberOfIterations(QString path)
{
    UINT i = 0;

    QDirIterator it(path, QDirIterator::Subdirectories);

    while(it.hasNext()) {
        QFileInfo file(it.next());

        if(file.fileName() != '.' && file.fileName() != "..") i++;
    }

    return i;
}

void SCleaner::on_clearToolButton_clicked()
{
    ui->cleaningParametersGroupBox->hide();
    ui->clearToolButton->hide();
    ui->cleaningInforListWidget->clear();
    ui->clearToolButton->hide();
    ui->tempoparyFilesGroupBox->hide();

    if(ui->tempoparyFilesCheckBox->checkState() == Qt::Unchecked && ui->trashCheckBox->checkState() == Qt::Unchecked && ui->regeditCheckBox->checkState() == Qt::Unchecked) {

        ui->scanToolButton->show();
    }

    if(ui->trashCheckBox->checkState() == Qt::Checked) if(SUCCEEDED(SHEmptyRecycleBin(NULL, NULL, SHERB_NOCONFIRMATION + SHERB_NOPROGRESSUI + SHERB_NOSOUND)));

    if(ui->tempoparyFilesCheckBox->checkState() == Qt::Checked) {

        ui->progressLineLabel->show();
        ui->progressLineLabel->setText("");
        ui->progressBar->show();
        ui->progressBar->setMinimum(0);
        ui->progressBar->setMaximum(getNumberOfIterations(_pathToAppData));

        QDirIterator it(_pathToAppData, QDirIterator::Subdirectories);

        while(it.hasNext()) {

            QFileInfo file(it.next());

            if(file.fileName() != '.' && file.fileName() != "..") {

                ui->progressLineLabel->setText(file.absoluteFilePath());
                ui->progressLineLabel->repaint();
                ui->progressBar->setValue(ui->progressBar->value() + 1);
            }
        }

        ui->progressLineLabel->hide();
        ui->progressLineLabel->setText("");
        ui->progressBar->hide();
        ui->progressBar->setValue(0);
        ui->scanToolButton->show();
    }
}
