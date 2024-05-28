#include "core/controller/client_controller.h"

ClientController::ClientController(QObject *parent)
    : QAbstractListModel(parent)
    , m_delimiter(',')
    , m_clients()
    , m_currentClient(nullptr) {
}

int ClientController::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }

    return m_clients.size();
}

QVariant ClientController::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (!index.isValid() || index.row() >= m_clients.size() || index.row() < 0) {
        return QVariant();
    }

    auto* client = m_clients[index.row()];

    switch (role) {
        case IdRole:
            return QVariant::fromValue(client->id());
        case FullNameRole:
            return QVariant::fromValue(client->fullName());
        case PhoneRole:
            return QVariant::fromValue(client->phone());
        case EmailRole:
            return QVariant::fromValue(client->email());
        case AdressRole:
            return QVariant::fromValue(client->adress());
        case CreditBalanceRole:
            return QVariant::fromValue(client->creditBalance());
        case DebitBalanceRole:
            return QVariant::fromValue(client->debitBalance());
        default:
            return {};
    }
}

QHash<int, QByteArray> ClientController::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[FullNameRole] = "fullName";
    roles[PhoneRole] = "phone";
    roles[EmailRole] = "email";
    roles[AdressRole] = "adress";
    roles[CreditBalanceRole] = "creditBalance";
    roles[DebitBalanceRole] = "debitBalance";
    return roles;
}

void ClientController::addClient(ClientInfo* client) {
    beginInsertRows(QModelIndex(), m_clients.size(), m_clients.size());
    m_clients.append(client);
    endInsertRows();
    emit countChanged();
}

void ClientController::removeClient(qsizetype index) {
    if (index < 0 || index >= m_clients.size()) {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    delete m_clients[index];
    m_clients.removeAt(index);
    endRemoveRows();
    emit countChanged();
}

ClientInfo* ClientController::currentClient() const {
    return m_currentClient;
}

[[nodiscard]] ClientInfo* ClientController::clientAt(qsizetype index) const {
    if (index < 0 || index >= m_clients.size()) {
        return nullptr;
    }

    return m_clients[index];
}

void ClientController::setCurrentClient(ClientInfo* client) {
    m_currentClient = client;
    emit currentClientChanged();
}

void ClientController::setDelimiter(QChar delimiter) {
    m_delimiter = delimiter;
}

void ClientController::loadClients(const QString &path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file: " << path;
        return;
    }

    qDebug() << "Loading clients from: " << path;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(m_delimiter);
        if (fields.size() != 7) {
            continue;
        }
        auto* client = new ClientInfo(this);
        client->setId(fields[0].toLongLong());
        client->setFullName(fields[1]);
        client->setPhone(fields[2]);
        client->setEmail(fields[3]);
        client->setAdress(fields[4]);
        client->setCreditBalance(fields[5].toLongLong());
        client->setDebitBalance(fields[6].toLongLong());
        addClient(client);
    }

    file.close();
}

void ClientController::saveClients(const QString &path) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream out(&file);
    for (const auto &client : m_clients) {
        out << client->id() << m_delimiter
            << client->fullName() << m_delimiter
            << client->phone() << m_delimiter
            << client->email() << m_delimiter
            << client->adress() << m_delimiter
            << client->creditBalance() << m_delimiter
            << client->debitBalance() << "\n";
    }

    file.close();
}

void ClientController::updateClient(qsizetype index, const ClientInfo &client) {
    if (index < 0 || index >= m_clients.size()) {
        return;
    }

    m_clients[index]->setId(client.id());
    m_clients[index]->setFullName(client.fullName());
    m_clients[index]->setPhone(client.phone());
    m_clients[index]->setEmail(client.email());
    m_clients[index]->setAdress(client.adress());
    m_clients[index]->setCreditBalance(client.creditBalance());
    m_clients[index]->setDebitBalance(client.debitBalance());
}

void ClientController::addClient(int64_t id,
                                const QString &fullName, 
                                const QString &phone, 
                                const QString &email, 
                                const QString &adress, 
                                int64_t creditBalance, 
                                int64_t debitBalance) {
    beginInsertRows(QModelIndex(), m_clients.length(), m_clients.length());
    auto* client = new ClientInfo(this);
    client->setId(id);
    client->setFullName(fullName);
    client->setPhone(phone);
    client->setEmail(email);
    client->setAdress(adress);
    client->setCreditBalance(creditBalance);
    client->setDebitBalance(debitBalance);
    m_clients.append(client);
    endInsertRows();
}