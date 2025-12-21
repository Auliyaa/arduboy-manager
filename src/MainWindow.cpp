#include <MainWindow.h>

#include <QDir>

#include <utils.h>
#include <GameWidget.h>

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags f)
  : QMainWindow(parent, f),
  _ui{new Ui::MainWindow}
{
  _ui->setupUi(this);
  
  for (const auto& id : QDir(appsPath()).entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name))
  {
    auto gw = new GameWidget(id, _ui->gameWidgets);
    _ui->gameWidgets->layout()->addWidget(gw);
    connect(gw, &GameWidget::installStarted, this, &MainWindow::installStarted);
    connect(gw, &GameWidget::installDone, this, &MainWindow::installDone);
    connect(gw, &GameWidget::logInfo, this, &MainWindow::logInfo);
    connect(gw, &GameWidget::logError, this, &MainWindow::logError);
  }

  refreshCOM();
}

MainWindow::~MainWindow()
{
  delete _ui;
}

void MainWindow::refreshCOM()
{
  _ui->comPort->blockSignals(true);
  _ui->comPort->clear();
  const auto ports = detectCOMPorts();
  for (const auto& port : ports)
  {
    _ui->comPort->addItem(port);
  }
  _ui->comPort->blockSignals(false);
  comPortChanged();
}

void MainWindow::comPortChanged()
{
  for (auto* gw : _ui->gameWidgets->findChildren<GameWidget*>())
  {
    gw->setCOMPort(_ui->comPort->currentText());
  }
}

void MainWindow::installStarted()
{
  for (auto* gw : _ui->gameWidgets->findChildren<GameWidget*>())
  {
    gw->setEnabled(false);
  }
}

void MainWindow::installDone()
{
  for (auto* gw : _ui->gameWidgets->findChildren<GameWidget*>())
  {
    gw->setEnabled(true);
  }
}

void MainWindow::logInfo(QString s)
{
  log(s, QColor("white"));
}

void MainWindow::logError(QString s)
{
  log(s, QColor("red"));
}

void MainWindow::log(const QString& s, const QColor& c)
{
  QTextCursor cursor = _ui->log->textCursor();
  cursor.movePosition(QTextCursor::End);

  QTextCharFormat format;
  format.setForeground(c);

  cursor.insertText(s + '\n', format);
  _ui->log->setTextCursor(cursor);
}
