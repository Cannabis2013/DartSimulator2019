#ifndef REPLYTIMEOUT_H
#define REPLYTIMEOUT_H

#include <qobject.h>
#include <qnetworkreply.h>
#include <qbasictimer.h>
#include <QTimerEvent>
#include <iostream>

using namespace std;

class ReplyTimeout : public QObject
{
    Q_OBJECT
public:

    enum HandleMethod { Abort, Close };
    ReplyTimeout(QNetworkReply* reply,
                 const int timeout,
                 QObject*reciever = nullptr,
                 const char* slot = nullptr,
                 HandleMethod method = Abort) :
        QObject(reply), _method(method)
    {
        if (reply->isRunning())
        {
          _timer.start(timeout, this);
          connect(reply, &QNetworkReply::finished, this, &QObject::deleteLater);
          connect(this,SIGNAL(timeoutOccured()),reciever,slot);
        }
    }
    static void setTimer(QNetworkReply* reply,
                         const int timeout,
                         QObject*reciever = nullptr,
                         const char* slot = nullptr,
                         HandleMethod method = Abort)
    {
        new ReplyTimeout(reply, timeout,reciever,slot, method);
    }

signals:
    void timeoutOccured();

protected:
    void timerEvent(QTimerEvent * ev)
    {
        if (!_timer.isActive() || ev->timerId() != _timer.timerId())
            return;
        auto reply = static_cast<QNetworkReply*>(parent());
        if (reply->isRunning())
        {
            cout << __FILE__ << __LINE__ << endl;
          if (_method == Close)
            reply->close();
          else if (_method == Abort)
            reply->abort();

          emit timeoutOccured();
        }
        _timer.stop();
    }

private:
    QBasicTimer _timer;
    HandleMethod _method;
};

#endif // REPLYTIMEOUT_H
