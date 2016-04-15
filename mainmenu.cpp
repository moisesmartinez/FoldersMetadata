#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    ui->tabFolderData->setEnabled(false);
    ui->tabRootExplorer->setEnabled(false);
}

MainMenu::~MainMenu()
{
    delete ui->wvMetadataURL;
    delete ui;
}

void MainMenu::PrintDebug(QString msg)
{
    qDebug() << msg;
}

void MainMenu::on_btnBrowseForFolder_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, "Select x Folder", "C:\\", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->txtFolderPath->setText(folderPath);
}

void MainMenu::on_btnShowFolderContent_clicked()
{
    QString const selectedFolderPath = ui->txtFolderPath->text().trimmed();

    //If the selected folder path is empty or not valid, end this function
    if(selectedFolderPath.isEmpty())
    {
        UtilityClass::getInstance()->ShowMessageBox("The folder path is empty!");
        return;
    }

    if(!QDir(selectedFolderPath).exists())
    {
        UtilityClass::getInstance()->ShowMessageBox("The folder you selected does not exist!");
        return;
    }

    fileSystemModel = new QFileSystemModel();
    fileSystemModel->setRootPath(selectedFolderPath);
    fileSystemModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden);

    ui->tvFolders->setModel(fileSystemModel);

    ui->tvFolders->hideColumn(1);//hide "Size" column
    ui->tvFolders->hideColumn(2);//hide "Type" column
    ui->tvFolders->hideColumn(3);//hide "Modified Date" column

    QModelIndex index = fileSystemModel->index(selectedFolderPath);
    ui->tvFolders->expand(index);
    ui->tvFolders->setCurrentIndex(index);
    ui->tvFolders->resizeColumnToContents(0);

    ui->tvFolders->setRootIndex(index);

    ui->tabFolderData->setEnabled(true);
    ui->tabRootExplorer->setEnabled(true);

    //Read all metadata on memory
    QStringList metadataList;
    metadataList = GetMetadataListFromTreeView();

    foreach (QString jsonPath, metadataList)
    {
        FolderMetadata *folder = UtilityClass::getInstance()->ReadJson(jsonPath);

        this->rootDirectoryMetadata.append(folder);
    }
    return;
}

void MainMenu::ClearControls()
{
    this->ui->txtComment->clear();
    //this->ui->txtFolderPath->clear();//No need to clear this.
    this->ui->txtImageUrl->clear();
    this->ui->txtName->clear();
    this->ui->txtWebUrl->clear();

    this->ui->cmbGenre->setCurrentText(0);
    this->ui->lwGenres->clear();

    this->ui->spbScore->setValue(0);
    this->ui->lblImage->clear();
}

void MainMenu::on_tvFolders_clicked(const QModelIndex &index)
{
    this->ClearControls();

    QString selectedFolderPath = fileSystemModel->filePath(index);
    QString jsonPath = selectedFolderPath + "/save.json";

    FolderMetadata *metadata = UtilityClass::getInstance()->ReadJson(jsonPath);
    this->ui->txtComment->setText(metadata->getComment());
    this->ui->txtImageUrl->setText(metadata->getImageUrl());
    this->ui->txtName->setText(metadata->getName());
    this->ui->txtWebUrl->setText(metadata->getWebUrl());
    this->ui->spbScore->setValue(metadata->getScore());
    QStringList tmp = metadata->getGenres();
    for(int i=0; i<tmp.count(); i++)
    {
        this->ui->lwGenres->addItem(tmp[i]);
    }

    this->GetImageFromUrl(metadata->getImageUrl());

    //this->PrintDebug("Created metadata in memory.");

    this->selectedFolderMetadata = metadata;




    //TEST: WRITE JSON

//    QString selectedFolderPath = fileSystemModel->filePath(index);

//    QString jsonpath = selectedFolderPath + "/save.json";

//    FolderMetadata *foldi = UtilityClass::getInstance()->ReadJson(jsonpath);
//    qDebug() << foldi->getComment();
//    qDebug() << foldi->getScore();
//    qDebug() << foldi->getGenres();
//    qDebug() << foldi->getImageUrl();
//    qDebug() << foldi->getWebUrl();

//    foldi->setComment("Ayy Lmao");
//    foldi->setScore(9);

//    UtilityClass::getInstance()->WriteJson(jsonpath, foldi);

//    UtilityClass::getInstance()->ShowMessageBox("tempo");
//    return;












    //TEST: READ .JSON
//    QFile wallet(jsonpath);
//    wallet.open(QIODevice::ReadOnly);
//    if (!wallet.open(QIODevice::ReadOnly)) {
//        UtilityClass::getInstance()->ShowMessageBox("Couldn't open save file.");
//        return;
//    }
//    QByteArray savedata = wallet.readAll();
//    wallet.close();

//    QJsonDocument jsondoc(QJsonDocument::fromJson(savedata));

//    QString strjson2(jsondoc.toJson(QJsonDocument::Compact));
//    qDebug() << strjson2 ;
//    UtilityClass::getInstance()->ShowMessageBox(strjson2);

//    return;










    //TEST: CREATE JSON ARRAY MANUALLY
//    QJsonArray arrayto;
//    arrayto.insert(0, QJsonValue("accion"));
//    arrayto.insert(1, QJsonValue("seinen"));

//    //CREATE JSON DOCUMENT (it has the json array inside)
//    QJsonObject objeto;
//    objeto.insert("nombre", QJsonValue("pedro"));
//    objeto.insert("score", QJsonValue(5));
//    objeto.insert("tags", QJsonValue(arrayto));

//    //FINALLY, CREATE THE JSON DOCUMENT
//    QJsonDocument doc2(objeto);


//    //SAVE .JSON
//    QFile wallet(jsonpath);
//    if (!wallet.open(QIODevice::WriteOnly)) {
//        UtilityClass::getInstance()->ShowMessageBox("Couldn't open save file. Try again");
//        return;
//    }
//    wallet.write(doc2.toJson());
//    wallet.close();
//    return;













    //TEST "QFileInfo" CLASS
//    UtilityClass::getInstance()->ShowMessageBox(selectedFolderPath);

//    UtilityClass::getInstance()->ShowMessageBox(selectedFolderPath + "/save.json");
//    qDebug() << selectedFolderPath + "/save.json";

//    QFileInfo loadFile(selectedFolderPath + "/save.json");
//    qDebug() << loadFile.exists();
//    qDebug() << loadFile.exists();
//    if (!loadFile.exists()) {
//        UtilityClass::getInstance()->ShowMessageBox("Couldn't open save file.");
//        return ;
//    }












    //CREATE JSON ARRAY
//    QJsonArray tmpo;
//    tmpo.insert(0, QJsonValue("accion"));
//    tmpo.insert(1, QJsonValue("seinen"));

//    //CREATE JSON DOCUMENT (it has the json array inside)
//    QJsonObject tmp;
//    tmp.insert("nombre", QJsonValue("pedro"));
//    tmp.insert("score", QJsonValue(5));
//    tmp.insert("tags", QJsonValue(tmpo));

//    //FINALLY, CREATE THE JSON DOCUMENT
//    QJsonDocument doc(tmp);

//    //SAVE/PRINT THE QJSON DOCUMENT
//    QString strjson(doc.toJson(QJsonDocument::Compact));
//    qDebug() << strjson ;

//    UtilityClass::getInstance()->ShowMessageBox(strjson);

//    return;








//    ui->tvFolders->selectionModel()->selectedIndexes();
//    ((QFileSystemModel)ui->tvFolders->model()).filePath(ui->tvFolders->selectionModel()->selectedIndexes().at(0));

//    QFileSystemModel *model = new QFileSystemModel();
//    model->setRootPath(ui->txtFolderPath->text());
//    model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden);

    //    this->ShowMessageBox(model->filePath(index));
}

void MainMenu::nmFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Error in" << reply->url() << ":" << reply->errorString();
        return;
    }

    QByteArray jpegData = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(jpegData);
    this->ui->lblImage->setPixmap(pixmap); // or whatever your labels name is
}

void MainMenu::GetImageFromUrl(QString httpUrl)
{
    if(httpUrl.trimmed() == "")
    {
        return;
    }

    QNetworkAccessManager *m_netwManager = new QNetworkAccessManager(this);
    connect(m_netwManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(nmFinished(QNetworkReply*)));

    QUrl url(httpUrl);
    QNetworkRequest request(url);
    m_netwManager->get(request);
}




void MainMenu::on_btnViewUrl_clicked()
{
    if(this->ui->txtWebUrl->text().trimmed() != "" && (this->ui->txtWebUrl->text().contains("http") || this->ui->txtWebUrl->text().contains("www.")))
    {
        ui->wvMetadataURL->load(QUrl(this->ui->txtWebUrl->text()));
        ui->twFolderMetadata->setCurrentIndex(1);
    }
}

void MainMenu::on_btnSaveData_clicked()
{
    if(this->selectedFolderMetadata  == 0)
    {
        return;
    }
    QString metadataPath = this->selectedFolderMetadata ->getMetadataPath();
    this->PrintDebug(metadataPath);
    if(metadataPath.trimmed() != "")
    {
        //Set information
        this->selectedFolderMetadata ->setComment(this->ui->txtComment->toPlainText());
        this->selectedFolderMetadata ->setImageUrl(this->ui->txtImageUrl->text());
        this->selectedFolderMetadata ->setName(this->ui->txtName->text());
        this->selectedFolderMetadata ->setScore(this->ui->spbScore->value());
        this->selectedFolderMetadata ->setWebUrl(this->ui->txtWebUrl->text());

        //Set genres
        this->selectedFolderMetadata ->setGenres(QStringList());
        for(int i =0; i<this->ui->lwGenres->count(); i++)
        {
            this->selectedFolderMetadata ->addGenre(this->ui->lwGenres->item(i)->text());
        }

        UtilityClass::getInstance()->WriteJson(metadataPath, this->selectedFolderMetadata );
    }
}

void MainMenu::on_btnAddGenre_clicked()
{
    QString genre = this->ui->cmbGenre->currentText().trimmed();
    if(genre != "" && this->ui->lwGenres->findItems(genre,Qt::MatchExactly).count() == 0)
    {
        this->ui->lwGenres->addItem(genre);
    }
    else
    {
        //UtilityClass::getInstance()->ShowMessageBox("Duplicated genres are not allowed.");
    }
}

void MainMenu::on_btnRemoveGenre_clicked()
{
    if(this->ui->lwGenres->currentRow() >= 0)
    {
        this->ui->lwGenres->takeItem(this->ui->lwGenres->currentRow());
    }
    else
    {
        //UtilityClass::getInstance()->ShowMessageBox("Genre X is already added.");
    }
}

QStringList MainMenu::GetMetadataListFromTreeView()
{

    //QDirModel *model = (QDirModel *)ui->tvFolders->model();

    /*int tempi = model->rowCount();
    tempi = ui->tvFolders->children().count();
    qDebug() << tempi;
    UtilityClass::getInstance()->ShowMessageBox("SWAG");
    for(int i=0; i < tempi; i++)
    {

    }*/

    QStringList jsonPaths;

    QDirIterator it(ui->txtFolderPath->text(), QStringList() << "save.json", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        jsonPaths.append(it.next());
    }

    return jsonPaths;


//    foreach (QModelIndex index, model)




    //The following commented code only applies to QTreeWidgets!
//    if(item == 0)
//        return;

//    this->metadataList.append(item->text(0));

//    for(int i = 0; i < item->childCount(); i++)
//    {
//        this->GetMetadataListFromTreeWidget(item->child(i));
//    }
}

void MainMenu::on_btnAddGenreFilter_clicked()
{
    QString genre = this->ui->cmbGenreFilter->currentText().trimmed();
    if(genre != "" && this->ui->lwGenresFilter->findItems(genre,Qt::MatchExactly).count() == 0)
    {
        this->ui->lwGenresFilter->addItem(genre);
    }
    else
    {
        UtilityClass::getInstance()->ShowMessageBox("Duplicated genres are not allowed.");
    }
}

void MainMenu::on_btnRemoveGenreFilter_clicked()
{
    if(this->ui->lwGenresFilter->currentRow() >= 0)
    {
        this->ui->lwGenresFilter->takeItem(this->ui->lwGenresFilter->currentRow());
    }
}

void MainMenu::on_btnShowResults_clicked()
{
    this->ui->lwResults->clear();
    foreach(FolderMetadata *metadata, this->rootDirectoryMetadata)
    {
        for(int i = 0; i < this->ui->lwGenresFilter->count(); i++)
        {
            if(metadata->getGenres().contains(ui->lwGenresFilter->item(i)->text()))
            {
                //ui->lwResults->addItem(metadata->getName());
                QString path = metadata->getMetadataPath();
                ui->lwResults->addItem(path.left(path.length() - 10));
                break;
            }
        }
    }
}
