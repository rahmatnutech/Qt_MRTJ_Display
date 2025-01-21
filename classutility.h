#ifndef CLASSUTILITY_H
#define CLASSUTILITY_H

#include <QObject>
#include <QWidget>
#include <QDir>
#include <QTextStream>

#include <QMediaPlayer>
#include <QMediaPlaylist>

class ClassUtility
{
public:
    ClassUtility();

    static QMediaPlayer* mediaPlayer;
    void PlayMusicFile(QString);
};

#endif // CLASSUTILITY_H
