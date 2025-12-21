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

private:
  Ui::MainWindow* _ui;
};
