#include "foldermetadata.h"

FolderMetadata::FolderMetadata(QString metadataPath)
{
    this->metadataPath = metadataPath;
}

void FolderMetadata::addGenre(QString genre)
{
    this->genres.append(genre);
}

void FolderMetadata::removeGenre(QString genre)
{
    this->genres.removeOne(genre);
}

QString FolderMetadata::getWebUrl() const
{
    return webUrl;
}

void FolderMetadata::setWebUrl(const QString &value)
{
    webUrl = value;
}

int FolderMetadata::getScore() const
{
    return score;
}

void FolderMetadata::setScore(const int &value)
{
    score = value;
}

QString FolderMetadata::getComment() const
{
    return comment;
}

void FolderMetadata::setComment(const QString &value)
{
    comment = value;
}

QStringList FolderMetadata::getGenres() const
{
    return genres;
}

void FolderMetadata::setGenres(const QStringList &value)
{
    genres = value;
}

QString FolderMetadata::getImageUrl() const
{
    return imageUrl;
}

void FolderMetadata::setImageUrl(const QString &value)
{
    imageUrl = value;
}

QString FolderMetadata::getMetadataPath() const
{
    return metadataPath;
}

QString FolderMetadata::getName() const
{
    return name;
}

void FolderMetadata::setName(const QString &value)
{
    name = value;
}
