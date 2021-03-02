#ifndef CGUIAPPLICATION_H
#define CGUIAPPLICATION_H

#include <QGuiApplication>

class CGuiApplicationPrivate;
class CGuiApplication : public QGuiApplication {
    Q_OBJECT
  public:
    explicit CGuiApplication(int& argc, char** argv);
    ~CGuiApplication();
    int exec();

  private:
    CGuiApplicationPrivate* p;
};

#endif  // CGUIAPPLICATION_H
