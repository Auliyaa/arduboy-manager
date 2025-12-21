#include <utils.h>

#include <QApplication>
#include <QDir>
#include <QSerialPortInfo>

QString joinPath(const QStringList& elts)
{
  QString res;
  for (const auto& elt : elts)
  {
    if (res.isEmpty()) res = elt;
    else
    {
      res += QDir::separator() + elt;
    }
  }
  return res;
}

QString appsPath()
{
  return joinPath({
    QApplication::applicationDirPath(),
    "..",
    "share",
    "apps"
  });
}

QString appPath(const QString& id)
{
  return joinPath({
    appsPath(),
    id
  });
}

QStringList detectCOMPorts()
{
  QStringList res;

  for (const auto& info : QSerialPortInfo::availablePorts())
  {
    if (!info.hasVendorIdentifier() || !info.hasProductIdentifier())
    {
      continue;
    }

    if (info.vendorIdentifier() == VENDOR_ID)
    {
      if (info.productIdentifier() == PRODUCT_ID1 || info.productIdentifier() == PRODUCT_ID2)
      {
        res.append(info.portName());
      }
    }
  }

  return res;
}

void qSleep(int delay)
{
  QTime dieTime= QTime::currentTime().addMSecs(delay);
  while (QTime::currentTime() < dieTime)
  {
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
  }
}

QString avrdudeDirPath()
{
  return joinPath({
    QApplication::applicationDirPath(),
    "..",
    "share",
    "avrdude",
  });
}

QString avrdudePath()
{
   return avrdudeDirPath() + QDir::separator() + "avrdude.exe";
}

QString iconPath()
{
  return joinPath({
    QApplication::applicationDirPath(),
    "..",
    "share",
    "icon.bmp"
  });
}

QSoundEffect* SoundEffects::HONK = nullptr;
QSoundEffect* SoundEffects::MOO = nullptr;
QSoundEffect* SoundEffects::SUCCESS = nullptr;
QSoundEffect* SoundEffects::FAIL = nullptr;
QSoundEffect* SoundEffects::WAIT = nullptr;

void SoundEffects::init()
{
  const auto soundsPath = joinPath({
    QApplication::applicationDirPath(),
    "..",
    "share",
    "audio"
  });

  HONK = new QSoundEffect();
  MOO = new QSoundEffect();
  SUCCESS = new QSoundEffect();
  FAIL = new QSoundEffect();
  WAIT = new QSoundEffect();

  HONK->setSource(QUrl::fromLocalFile(joinPath({soundsPath,"honk.wav"})));
  MOO->setSource(QUrl::fromLocalFile(joinPath({soundsPath,"moo.wav"})));
  SUCCESS->setSource(QUrl::fromLocalFile(joinPath({soundsPath,"success.wav"})));
  FAIL->setSource(QUrl::fromLocalFile(joinPath({soundsPath,"fail.wav"})));
  WAIT->setSource(QUrl::fromLocalFile(joinPath({soundsPath,"wait.wav"})));
  WAIT->setLoopCount(std::numeric_limits<int>::max());

  HONK->setVolume(1.0);
  MOO->setVolume(1.0);
  SUCCESS->setVolume(1.0);
  FAIL->setVolume(1.0);
  WAIT->setVolume(1.0);
}