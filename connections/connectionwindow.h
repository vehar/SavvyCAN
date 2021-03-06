#ifndef CONNECTIONWINDOW_H
#define CONNECTIONWINDOW_H



#include <QSerialPortInfo>
#include <QDialog>
#include <QDebug>
#include <QSettings>
#include <QTimer>
#include <QItemSelection>
#include "canconnectionmodel.h"
#include "connections/canconnection.h"


class CANConnectionModel;

namespace Ui {
class ConnectionWindow;
}


class ConnectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionWindow(QWidget *parent = 0);
    ~ConnectionWindow();
    void showEvent(QShowEvent *);

    CANCon::type getConnectionType();
    bool getSWMode();

signals:
    void updateBusSettings(CANBus *bus);
    void updatePortName(QString port);

public slots:
    void setSpeed(int speed0);
    void setSWMode(bool mode);

    void setSuspendAll(bool pSuspend);

private slots:
    void handleOKButton();
    void handleConnTypeChanged();
    void currentRowChanged(const QModelIndex &current, const QModelIndex &previous);
    void handleRemoveConn();
    void handleEnableAll();
    void handleDisableAll();
    void handleRevert();
    void handleNewConn();
    void connectionStatus(CANCon::status);

private:
    Ui::ConnectionWindow *ui;
    QList<QSerialPortInfo> ports;
    QSettings *settings;
    CANConnectionModel *connModel;

    void selectSerial();
    void selectKvaser();
    void selectSocketCan();
    bool isSocketCanAvailable();
    int getSpeed();
    QString getPortName();
    void setPortName(CANCon::type pType, QString pPortName);

    void setActiveAll(bool pActive);
    CANConnection* create(CANCon::type pTye, QString pPortName);
    void loadConnections();
    void saveConnections();
};

#endif // CONNECTIONWINDOW_H
