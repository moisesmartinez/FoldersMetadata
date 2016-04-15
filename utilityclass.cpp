#include "utilityclass.h"

UtilityClass* UtilityClass::_instance = 0;

UtilityClass::UtilityClass()
{

}

UtilityClass* UtilityClass::getInstance()
{
    if(_instance == 0)
    {
        _instance = new UtilityClass();
    }

    return _instance;
}

void UtilityClass::ShowMessageBox(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}

FolderMetadata* UtilityClass::CreateClassFromJson(QString jsonPath, QJsonObject json)
{
    FolderMetadata *metadata = new FolderMetadata(jsonPath);
    //Set data to the metadata class
    metadata->setComment(json["comment"].toString());
    metadata->setImageUrl(json["imageUrl"].toString());
    metadata->setScore(json["score"].toInt());
    metadata->setWebUrl(json["webUrl"].toString());
    metadata->setName(json["name"].toString());

    //Set genres to the metadata class
    QStringList tags;
    QJsonArray jsonTags = json["genres"].toArray();
    for(int i=0; i<jsonTags.count(); i++)
    {
        tags.append(jsonTags.at(i).toString());
    }
    metadata->setGenres(tags);

    return metadata;
}

QJsonDocument UtilityClass::CreateJsonFromClass(FolderMetadata *jsonData)
{
    //Create array of tags (QJsonArray)
    QStringList genres = jsonData->getGenres();
    QJsonArray jsonGenres;
    for(int i=0; i<genres.count(); i++)
    {
        jsonGenres.append(QJsonValue(genres.at(i)));
    }

    //Now that we have the JsonArray, create the body of the json file (QJsonObject)
    QJsonObject jsonObj;
    jsonObj.insert("name", QJsonValue(jsonData->getName()));
    jsonObj.insert("score", QJsonValue(jsonData->getScore()));
    jsonObj.insert("imageUrl", QJsonValue(jsonData->getImageUrl()));
    jsonObj.insert("webUrl", QJsonValue(jsonData->getWebUrl()));
    jsonObj.insert("comment", QJsonValue(jsonData->getComment()));
    jsonObj.insert("genres", QJsonValue(jsonGenres));//assigning the JsonArray

    //Finally, create the JsonDocument
    QJsonDocument jsonDoc(jsonObj);

    return jsonDoc;
}

FolderMetadata* UtilityClass::ReadJson(QString jsonPath)
{
    FolderMetadata *jsonData = new FolderMetadata(jsonPath);

    //Trying to open the json file::ReadOnly
    QFile jsonFile(jsonPath);
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        qDebug() << "No metadata found: " + jsonPath;
        return jsonData;
    }
    //Read file and then close it
    QByteArray savedata = jsonFile.readAll();
    jsonFile.close();

    //Create the QJsonDocument from the read data..
    QJsonDocument jsonDoc(QJsonDocument::fromJson(savedata));
    //..and then, create a metadata class from the json
    jsonData = this->CreateClassFromJson(jsonPath, jsonDoc.object());

    return jsonData;
}

bool UtilityClass::WriteJson(QString jsonPath, FolderMetadata *jsonData)
{
    //Create a JSonDocument object from the class
    QJsonDocument jsonDoc = this->CreateJsonFromClass(jsonData);

    //Try to open the file::WriteOnly in the selected path
    QFile jsonFile(jsonPath);
    if (!jsonFile.open(QIODevice::WriteOnly)) {
        this->ShowMessageBox("Couldn't open save file. Try again");
        return false;
    }

    //Write and close
    jsonFile.write(jsonDoc.toJson(QJsonDocument::Compact));
    jsonFile.close();
    return true;
}

//Checks if a file exists
bool UtilityClass::FileExists(QString filePath)
{
    bool returnValue = true;

    QFile jsonFile(filePath);
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        returnValue = false;
    }
    else {
        jsonFile.close();
    }

    return returnValue;
}
