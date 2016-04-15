#ifndef UTILITYCLASS_H
#define UTILITYCLASS_H
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QFile>
#include "foldermetadata.h"
#include <QDebug>

class UtilityClass
{
public:
    static UtilityClass* getInstance();
    void ShowMessageBox(QString text);
    FolderMetadata* ReadJson(QString jsonPath);
    bool WriteJson(QString jsonPath, FolderMetadata* jsonData);
    bool FileExists(QString filePath);

private:
    UtilityClass();//Singleton
    static UtilityClass *_instance;
    FolderMetadata* CreateClassFromJson(QString jsonPath, QJsonObject json);
    QJsonDocument CreateJsonFromClass(FolderMetadata *jsonData);
    // C++ 03
    // ========
    // Dont forget to declare these two. You want to make sure they
    // are unacceptable otherwise you may accidentally get copies of
    // your singleton appearing.
    UtilityClass(UtilityClass const&);              // Don't Implement
    void operator=(UtilityClass const&); // Don't implement
};

#endif // UTILITYCLASS_H
