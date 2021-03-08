#ifndef TGUIAPPLICATION_H
#define TGUIAPPLICATION_H

#include <QGuiApplication>

class TGuiApplicationPrivate;
class TGuiApplication : public QGuiApplication {
    Q_OBJECT
  public:
    explicit TGuiApplication(int& argc, char** argv);
    ~TGuiApplication();
    int exec();

  private:
    TGuiApplicationPrivate* p;
};

#endif  // CGUIAPPLICATION_H
