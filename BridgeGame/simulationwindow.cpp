#include "simulationwindow.h"
#include <bits/stdc++.h>
#include <QMessageBox>
#include <QRandomGenerator>
#include "ui_simulationwindow.h"
#include <algorithm>

SimulationWindow::SimulationWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SimulationWindow)
{
    ui->setupUi(this);
    setSettingsWidgetsVisibility(false);

}

SimulationWindow::~SimulationWindow()
{
    delete ui;
}

void SimulationWindow::on_startButton_clicked()
{
    ui->leftBox->setText("");
    ui->bridgeBox->setText("");
    ui->rightBox->setText("");

    lside.clear();
    rside.clear();
    returnValues.clear();
    int totalTime = 0;

    setNumberOfPeople();
    crossBridge();
}

void SimulationWindow::on_settingsButton_clicked()
{
    if(ui->settingsButton->text() == "Settings")
    {
        setSettingsWidgetsVisibility(true);
        ui->settingsButton->setText("Apply");
        ui->startButton->setEnabled(false);
    }
    else
    {
        setSettingsWidgetsVisibility(false);
        ui->settingsButton->setText("Settings");
        ui->startButton->setEnabled(true);

    }
}

void SimulationWindow::setSettingsWidgetsVisibility(bool visible)
{
    ui->numOfYoungLabel->setVisible(visible);
    ui->numOfMiddleAgedLabel->setVisible(visible);
    ui->numOfOldLabel->setVisible(visible);
    ui->numOfYoung->setVisible(visible);
    ui->numOfMiddleAged->setVisible(visible);
    ui->numOfOld->setVisible(visible);
}

void SimulationWindow::setNumberOfPeople()
{
    lside.clear();
    int numberOfYoungPeople = ui->numOfYoung->value();
    int numberOfMiddleAgedPeople = ui->numOfMiddleAged->value();
    int numberOfOldPeople = ui->numOfOld->value();

    for (int i = 0; i < numberOfYoungPeople; i++) {
        lside.push_back(1);
    }

    for (int i = 0; i < numberOfMiddleAgedPeople; i++) {
        lside.push_back(2);
    }

    for (int i = 0; i < numberOfOldPeople; i++) {
        lside.push_back(3);
    }
}

int SimulationWindow::maxSearch(QList<int> ls)
{
    int maximum = 0;
    for (int i = 0; i < ls.size(); i++) {
        if (ls[i] > maximum) maximum = ls[i];
    }
    return maximum;
}

int SimulationWindow::minSearch(QList<int> ls)
{
    int minimum = ls[0];
    for (int i = 0; i < ls.size(); i++) {
        if (ls[i] < minimum) minimum = ls[i];
    }
    return minimum;
}

int SimulationWindow::minSearch2(QList<int> ls)
{
    int minimum = ls[ls.size()-2];
    for (int i = ls[ls.size()-2]; i < ls.size(); i++) {
        if (ls[i] < minimum) minimum = ls[i];
    }
    return minimum;
}

void SimulationWindow::retValFill () {
    QList<QList<int>> tempVec;
    tempVec.push_back(lside);
    tempVec.push_back(rside);
    QList<int> tt;
    tt.push_back(totalTime);
    tempVec.push_back(tt);
    returnValues.push_back(tempVec);
}

void SimulationWindow::crossBridge() {
    bool sideSelect = false; // 0L, 1R
    retValFill();
    while (lside.size() > 0) {
        QList<int> send;
        if (sideSelect == false) {
            std::sort(lside.begin(), lside.end());
            if (rside.size() == 0 || minSearch2(lside) <= minSearch(rside)) {
                for (int i = 0; i < BRIDGE_SIZE && lside.size() > 0; i++) {
                    send.push_back(lside.takeAt(0));
                }
            } else {
                for (int i = 0; i < BRIDGE_SIZE; i++) {
                    send.push_back(lside.takeAt(lside.size()-1));
                }
            }
            totalTime += maxSearch(send);

            for (int i = 0; i < send.size(); i++) {
                rside.push_back(send[i]);
            }
            retValFill();
            sideSelect = true;
        } else if (sideSelect == true) {
            std::sort(rside.begin(), rside.end());
            send.push_back(rside.takeAt(0));

            for (int i = 0; i < send.size(); i++)
                lside.push_back(send[i]);

            totalTime += maxSearch(send);
            retValFill();
            sideSelect = false;
        }
    }

    QString leftSideText = "";
    QString rightSideText = "";
    QString bridgeText = "";
    int timeTaken;

    for (int i = 0; i < returnValues.size(); i++) {

        for (int j = 0; j < returnValues[i][0].size(); j++) {
            leftSideText.append(QString::number(returnValues[i][0][j]));
            leftSideText.append(" ");
            std::cout << returnValues[i][0][j] << " ";
        }
        leftSideText.append("\n");
        ui->leftBox->setText(leftSideText);

        bridgeText.append(" [===========] \n");
        std::cout << " [===========] ";
        ui->bridgeBox->setText(bridgeText);


        for (int j = 0; j < returnValues[i][1].size(); j++) {
            rightSideText.append(QString::number(returnValues[i][1][j]));
            rightSideText.append(" ");
            std::cout << returnValues[i][1][j] << " ";
        }
        rightSideText.append("\n");
        ui->rightBox->setText(rightSideText);

        std::cout << "\t total time taken = " << returnValues[i][2][0] << " " << std::endl;
        timeTaken = returnValues[i][2][0];
    }
    ui->timeTakenLabel->setText("Time taken: " + QString::number(timeTaken) + " minutes");
}
