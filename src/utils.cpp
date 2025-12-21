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