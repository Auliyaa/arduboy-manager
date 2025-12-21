#pragma once

#include <QWidget>
#include <QProcess>

namespace Ui
{
  class GameWidget;
}

class GameWidget: public QWidget
{
  Q_OBJECT;
public:
  explicit GameWidget(QString id, QWidget* parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
  virtual ~GameWidget();
  void setCOMPort(QString);
  QString id() const;

protected slots:
  void install();
  void avrdudeStdout();
  void avrdudeStderr();
  void avrdudeFinished(int, QProcess::ExitStatus);

signals:
  void installStarted();
  void installDone();
  void logInfo(QString);
  void logError(QString);

private:
  Ui::GameWidget* _ui;

  QString _id;
  QProcess* _avrdude{nullptr};
  QString _bannerPath;
  QString _hexPath;
  QString _comPort;
};
