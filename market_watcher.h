#ifndef MARKET_WATCHER_H
#define MARKET_WATCHER_H

#include <QObject>
#include <QAtomicInt>
#include <QStringList>
#include <QSet>
#include <QMultiMap>

class CThostFtdcMdApi;
class CTickReceiver;
struct CThostFtdcDepthMarketDataField;

class MarketWatcher : public QObject {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.ctp.market_watcher")
public:
    explicit MarketWatcher(QObject *parent = 0);
    ~MarketWatcher();

protected:
    QAtomicInt nRequestID;
    CThostFtdcMdApi *pUserApi;
    CTickReceiver *pReceiver;
    QSet<QString> subscribeSet;

    QByteArray brokerID;
    QByteArray userID;
    QByteArray password;
    char* c_brokerID;
    char* c_userID;
    char* c_password;

    QMultiMap<QString, QPair<QString, QString>> tradeTimeMap;
    QMultiMap<QString, QString> instrumentMap;

    void customEvent(QEvent *) override;

    void login();
    void subscribe();
    void processDepthMarketData(const CThostFtdcDepthMarketDataField&);

signals:
    void heartBeatWarning(int nTimeLapse);
    void newMarketData(const QString& instrumentID, uint time, double lastPrice, int volume, double turnover, double openInterest);

public slots:
    QString getTradingDay() const;
    QStringList getSubscribeList() const;
    void quit();
};

#endif // MARKET_WATCHER_H

