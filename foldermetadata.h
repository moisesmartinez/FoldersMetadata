#ifndef FOLDERMETADATA_H
#define FOLDERMETADATA_H
#include <QString>
#include <QStringList>

class FolderMetadata
{
public:
    FolderMetadata(QString metadataPath);
    void addGenre(QString genre);
    void removeGenre(QString genre);

    QString getWebUrl() const;
    void setWebUrl(const QString &value);

    int getScore() const;
    void setScore(const int &value);

    QString getComment() const;
    void setComment(const QString &value);

    QStringList getGenres() const;
    void setGenres(const QStringList &value);

    QString getImageUrl() const;
    void setImageUrl(const QString &value);

    QString getMetadataPath() const;

    QString getName() const;
    void setName(const QString &value);

private:
    QString metadataPath;

    //Data stored in the metadata file (save.json)
    QString name;
    QString webUrl;
    int score;
    QString comment;
    QStringList genres;
    QString imageUrl;
};

#endif // FOLDERMETADATA_H
