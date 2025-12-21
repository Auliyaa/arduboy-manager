#include <QApplication>

#include <utils.h>
#include <MainWindow.h>

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  SoundEffects::init();
  
  MainWindow w;
  w.show();

  return app.exec();
}