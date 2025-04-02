#include <QApplication>
#include <QMainWindow>

#include "qtermwidget.h"

int main(int argc, char *argv[]) {
  // Создаем окно и приложение
  QApplication app(argc, argv);
  QMainWindow *mainWindow = new QMainWindow();

  // Создаем объект консоли
  QTermWidget *console = new QTermWidget();

  // Добавляем шрифт терминала
  QFont font = QApplication::font();
  font.setFamily("Monospace"); // задаем шрифт monospace
  font.setPointSize(14); // задаем размер шрифта в pt

  console->setTerminalFont(font); // задаем наши характеристики шрифта в консоль

  // Показ окна
  QObject::connect(console, SIGNAL(finished()), mainWindow, SLOT(close()));
  mainWindow->setCentralWidget(console);
  mainWindow->show();

  return app.exec();
}