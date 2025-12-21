#include <MainWindow.h>

#include <QSerialPortInfo>
#include <QDir>

#include <utils.h>
#include <GameWidget.h>

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags f)
  : QMainWindow(parent, f),
  _ui{new Ui::MainWindow}
{
  _ui->setupUi(this);
  refreshCOM();

  for (const auto& id : QDir(appsPath()).entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name))
  {
    auto gw = new GameWidget(id, _ui->gameWidgets);
    _ui->gameWidgets->layout()->addWidget(gw);
    connect(gw, SIGNAL(installStarted()), this, SLOT(installStarted()));
    connect(gw, SIGNAL(installDone()), this, SLOT(installDone()));
  }
}

MainWindow::~MainWindow()
{
  delete _ui;
}

void MainWindow::refreshCOM()
{
  _ui->comPort->blockSignals(true);
  _ui->comPort->clear();
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
        _ui->comPort->addItem(info.portName());
      }
    }
  }
  _ui->comPort->blockSignals(false);
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

}