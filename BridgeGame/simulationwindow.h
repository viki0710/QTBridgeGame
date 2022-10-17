#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class SimulationWindow; }
QT_END_NAMESPACE

class SimulationWindow : public QMainWindow
{
    Q_OBJECT

public:
    SimulationWindow(QWidget *parent = nullptr);
    ~SimulationWindow();

private slots:
    void on_startButton_clicked();
    void on_settingsButton_clicked();

private:
    Ui::SimulationWindow *ui;
    void setNumberOfPeople();
    void setSettingsWidgetsVisibility(bool visible);

    int maxSearch(QList<int> ls);
    int minSearch(QList<int> ls);
    int minSearch2(QList<int> ls);
    void retValFill();
    void crossBridge();

    const int BRIDGE_SIZE = 3;
    const int youngSpeed = 1;
    const int middleAgedSpeed = 2;
    const int oldSpeed = 3;

    QList<int> lside;
    QList<int> rside;
    QList<QList<QList<int>>> returnValues;
    int totalTime = 0;
};
#endif // SIMULATIONWINDOW_H
