#include "connectionhealth.h"
#include "server.h"

#ifdef __linux__
#include "platforms/linux/linuxpingsender.h"
#else
#include "platforms/dummy/dummypingsender.h"
#endif

#include <QDebug>

// In seconds, the timeout for unstable pings.
constexpr uint32_t TIMEOUT_UNSTABLE_SEC = 5;

// In seconds, the timeout to detect no-signal pings.
constexpr uint32_t TIMEOUT_NOSIGNAL_SEC = 30;

// Gap between 1 ping and the following one, in seconds.
constexpr uint32_t WAITING_TIMEOUT_SEC = 2;

ConnectionHealth::ConnectionHealth()
{
#ifdef __linux__
    m_pingSender = new LinuxPingSender(this);
#else
    m_pingSender = new DummyPingSender(this);
#endif
    connect(m_pingSender, &PingSender::completed, this, &ConnectionHealth::pingCompleted);

    m_unstableTimer.setSingleShot(true);
    connect(&m_unstableTimer, &QTimer::timeout, [this]() {
        Q_ASSERT(m_state == Pending);
        qDebug() << "ConnectionHealth: timeout";
        m_state = Timeout;
        emit connectionUnstable();
    });

    m_noSignalTimer.setSingleShot(true);
    connect(&m_noSignalTimer, &QTimer::timeout, [this]() {
        Q_ASSERT(m_state == Timeout);
        qDebug() << "ConnectionHealth: no signal";

        m_pingSender->stop();
        wait();
        emit connectionNoSignal();
    });

    m_waitingTimer.setSingleShot(true);
    connect(&m_waitingTimer, &QTimer::timeout, [this]() {
        Q_ASSERT(m_state == Waiting);
        sendPing();
    });
}

void ConnectionHealth::start(const Server &server)
{
    qDebug() << "ConnectionHealth activated for server:" << server.hostname();

    m_gateway = server.ipv4Gateway();
    sendPing();
}

void ConnectionHealth::stop()
{
    qDebug() << "ConnectionHealth deactivated";
    m_state = Inactive;

    m_unstableTimer.stop();
    m_noSignalTimer.stop();
    m_waitingTimer.stop();
    m_pingSender->stop();
}

void ConnectionHealth::sendPing()
{
    Q_ASSERT(m_state == Waiting || m_state == Inactive);

    qDebug() << "ConnectionHealth: Sending a ping";

    m_state = Pending;
    m_pingSender->send(m_gateway);

    Q_ASSERT(!m_unstableTimer.isActive());
    m_unstableTimer.start(TIMEOUT_UNSTABLE_SEC * 1000);

    Q_ASSERT(!m_noSignalTimer.isActive());
    m_noSignalTimer.start(TIMEOUT_NOSIGNAL_SEC * 1000);

    Q_ASSERT(!m_waitingTimer.isActive());
}

void ConnectionHealth::pingCompleted()
{
    Q_ASSERT(m_state == Timeout || m_state == Pending);

    qDebug() << "ConnectionHealth: Ping completed";

    m_unstableTimer.stop();
    m_noSignalTimer.stop();

    State state = m_state;
    wait();

    if (state == Pending) {
        emit connectionStable();
    }
}

void ConnectionHealth::wait()
{
    Q_ASSERT(m_state == Timeout || m_state == Pending);

    qDebug() << "ConnectionHealth: Let's wait for the next ping to be sent";

    m_state = Waiting;
    Q_ASSERT(!m_waitingTimer.isActive());
    m_waitingTimer.start(WAITING_TIMEOUT_SEC * 1000);
}
