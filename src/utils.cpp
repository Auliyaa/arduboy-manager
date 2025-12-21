#include <utils.h>

#include <QApplication>
#include <QDir>

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