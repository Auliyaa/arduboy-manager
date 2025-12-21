#pragma once

#include <QMainWindow>

namespace Ui
{
  class MainWindow;
}

class MainWindow: public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget* parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
  virtual ~MainWindow();

protected slots:
  void refreshCOM();
  void installStarted();
  void installDone();
  void logInfo(QString);
  void logError(QString);
  void log(const QString&, const QColor&);
  void comPortChanged();
  void filter(QString);

private:
  Ui::MainWindow* _ui;
};
