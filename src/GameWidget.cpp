#include <GameWidget.h>

#include <QDir>
#include <QImage>

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

  QPixmap px(_bannerPath);
  _ui->banner->setPixmap(px);
}

GameWidget::~GameWidget()
{
  delete _ui;
}

void GameWidget::install()
{
  emit installStarted();
  // TODO: avrdude shenanigans
  emit installDone();
}