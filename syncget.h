#ifndef SYNCGET_H
#define SYNCGET_H

#include "tbinaryprotocol.h"
#include "note.h"
#include <QObject>
#include <QDateTime>
#include <QList>

class EdamProtocol;

class SyncGet : public QObject
{
    Q_OBJECT
public:
    SyncGet(QObject *parent = 0);

    void sync();
private:
    qint64 firstUSN;
    bool canceled;

    QByteArray createGetSyncChunkPost(qint32 afterUSN, qint32 maxEntries, bool fullSyncOnly = false);
    QByteArray createGetFilteredSyncChunkPost(qint32 afterUSN, qint32 maxEntries);
    QByteArray createGetSyncStatePost();
    void GetSyncChunk(qint32 afterUSN, qint32 maxEntries);
    void GetSyncState(qint64 &currentTime, qint64 &fullSyncBefore, qint32 &updateCount, qint64 &uploaded);
    int modificationsCount();
    void writeNoteConflict(QString guid, QString hash, qint64 updated);

public slots:
    void cancelSync();

signals:
    void syncFinished();
    void syncStarted(int count);
    void syncProgress(int value);

private slots:
    void updateProgress();
};

#endif // SYNCGET_H
