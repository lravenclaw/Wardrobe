#pragma once

#include <QAbstractListModel>
#include <QFile>
#include <QChar>
#include <QList>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QtGlobal>
#include <QDebug>


#include "core/model/client_info.h"

class ClientController : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(ClientInfo* currentClient READ currentClient WRITE setCurrentClient NOTIFY currentClientChanged)

   public:
    enum ClientRoles {
        IdRole = Qt::UserRole + 1,
        FullNameRole,
        PhoneRole,
        EmailRole,
        AdressRole,
        CreditBalanceRole,
        DebitBalanceRole,
    };

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    void addClient(ClientInfo* client);

    [[nodiscard]] ClientInfo* currentClient() const;
    [[nodiscard]] ClientInfo* clientAt(qsizetype index) const;

    void setCurrentClient(ClientInfo* client);

    void setDelimiter(QChar delimiter);
    void loadClients(const QString &path);
    void saveClients(const QString &path);

    [[nodiscard]] static ClientController* Init(QObject* parent = nullptr){
        return m_instance = new ClientController(parent);
    }

    [[nodiscard]] static ClientController* Instance(){
        return m_instance;
    }

   signals:
    void countChanged();
    void currentClientChanged();

   public slots:
    void updateClient(qsizetype index, const ClientInfo &client);
    void addClient(int64_t id,
                    const QString &fullName, 
                    const QString &phone, 
                    const QString &email, 
                    const QString &adress, 
                    int64_t creditBalance = 0, 
                    int64_t debitBalance = 0);
    void removeClient(qsizetype index);

   private:
    explicit ClientController(QObject* parent = nullptr);

    inline static ClientController* m_instance = nullptr;
    QChar m_delimiter;
    QList<ClientInfo*> m_clients;
    ClientInfo* m_currentClient;
};