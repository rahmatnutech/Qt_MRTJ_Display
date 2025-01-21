#include "classutility.h"
QMediaPlayer* ClassUtility::mediaPlayer;

ClassUtility::ClassUtility()
{
    // Create a QMediaPlayer object
    mediaPlayer = new QMediaPlayer();
}

void ClassUtility::PlayMusicFile(QString filePath)
{
    // Set the audio output to the player
    mediaPlayer->setMedia(QUrl::fromLocalFile(filePath));

    // Set the .wav file to play
    mediaPlayer->play();
}
