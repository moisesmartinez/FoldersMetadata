#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QWebView>
#include <QTreeWidget>
//LOAD IMAGE FROM HTTP URL
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDirModel>
//MA CLASSES
#include "utilityclass.h"


namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

private slots:
    void PrintDebug(QString msg);
    void on_btnBrowseForFolder_clicked();

    void on_btnShowFolderContent_clicked();

    void on_tvFolders_clicked(const QModelIndex &index);

    //Slot for the Network Access Manager
    void nmFinished(QNetworkReply*);

    void on_btnViewUrl_clicked();

    void on_btnSaveData_clicked();

    void on_btnAddGenre_clicked();

    void on_btnRemoveGenre_clicked();

    void on_btnAddGenreFilter_clicked();

    void on_btnRemoveGenreFilter_clicked();

    void on_btnShowResults_clicked();

private:
    Ui::MainMenu *ui;
    QList<FolderMetadata*> rootDirectoryMetadata;//List of metadata found in the main directory of the tree view. Used by the FilterDirectory tab.
    QFileSystemModel *fileSystemModel;//Used by the QTreeView
    FolderMetadata *selectedFolderMetadata;//Current metadata from the selected folder in the QTreeView
    //QStringList metadataList;//Deprecated
    void ClearControls();
    void GetImageFromUrl(QString httpUrl);
    QStringList GetMetadataListFromTreeView();
};

#endif // MAINMENU_H
