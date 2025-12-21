#include <GameWidget.h>

#include <QDir>
#include <QImage>
#include <QSerialPort>

#include <utils.h>

#include "ui_GameWidget.h"

GameWidget::GameWidget(QString id, QWidget* parent, Qt::WindowFlags f)
  : QWidget(parent, f),
  _ui{new Ui::GameWidget}
{
  _ui->setupUi(this);

  _bannerPath = joinPath({
    appPath(id),
    "banner.png"
  });

  _hexPath = joinPath({
    appPath(id),
    "app.hex"
  });

  if (QFile(_bannerPath).exists())
  {
    QPixmap px(_bannerPath);
    _ui->banner->setPixmap(px);
  }
  _ui->title->setText(id);

  connect(_ui->installButton, &QPushButton::clicked, SoundEffects::HONK, &QSoundEffect::play);
}

GameWidget::~GameWidget()
{
  delete _ui;
}

void GameWidget::setCOMPort(QString p)
{
  _comPort = p;
}

void GameWidget::install()
{
  emit installStarted();
  
  SoundEffects::WAIT->play();

  const auto& oldCOM = detectCOMPorts();

  emit logInfo("Selected " + _comPort + " as upload port.");
  emit logInfo("Starting avrdude..");
  QStringList args = {
    "-v",
    "-patmega32u4",
    "-cavr109",
    "-P" + _comPort,
    "-b57600",
    "-D",
    "-Uflash:w:" + _hexPath + ":i"
  };

  if (_avrdude) _avrdude->deleteLater();
  _avrdude = new QProcess(this);
  _avrdude->setProcessChannelMode(QProcess::SeparateChannels);
  _avrdude->setWorkingDirectory(avrdudeDirPath());
  connect(_avrdude, &QProcess::readyReadStandardOutput, this, &GameWidget::avrdudeStdout);
  connect(_avrdude, &QProcess::readyReadStandardError, this, &GameWidget::avrdudeStderr);
  connect(_avrdude, &QProcess::finished, this, &GameWidget::avrdudeFinished);

  emit logInfo(avrdudePath() + " " + args.join(" "));
  _avrdude->start(avrdudePath(), args);
}

void GameWidget::avrdudeStdout()
{
  const QByteArray data = _avrdude->readAllStandardOutput();
  if (!data.isEmpty())
  {
    emit logInfo(QString::fromLocal8Bit(data));
  }
}

void GameWidget::avrdudeStderr()
{
  const QByteArray data = _avrdude->readAllStandardError();
  if (!data.isEmpty())
  {
    emit logError(QString::fromLocal8Bit(data));
  }
}

void GameWidget::avrdudeFinished(int code, QProcess::ExitStatus status)
{
  SoundEffects::WAIT->stop();
  if (code != 0)
  {
    SoundEffects::FAIL->play();
    emit logError("process failed with code " + QString::number(code));
  }
  else
  {
    SoundEffects::SUCCESS->play();
    emit logInfo("process exited with code " + QString::number(code));
  }
  emit installDone();
}