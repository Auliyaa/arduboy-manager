#pragma once

#include <QWidget>

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

protected slots:
  void install();

signals:
  void installStarted();
  void installDone();

private:
  Ui::GameWidget* _ui;

  QString _bannerPath;
  QString _hexPath;
};
