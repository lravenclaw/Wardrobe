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


#include "core/model/item_info.h"

class ItemController : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(ItemInfo* currentItem READ currentItem WRITE setCurrentItem NOTIFY currentItemChanged)

   public:
    enum ItemRoles {
        IdRole = Qt::UserRole + 1,
        MaterialRole,
        SizeRole,
        BrandRole,
        DetailsRole,
        StyleRole,
        PatternRole,
        PlaceOfPurchaseRole,
        WashPrincipleRole,
        SeasonRole,
        ColorRole,
        PriceRole,
        SourcesRole
    };

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    void addItem(ItemInfo* item);

    [[nodiscard]] ItemInfo* currentItem() const;
    [[nodiscard]] ItemInfo* itemAt(qsizetype index) const;

    void setCurrentItem(ItemInfo* item);

    void setDelimiter(QChar delimiter);
    void loadItems(QFile &file);
    void saveItems(QFile &file);

    [[nodiscard]] static ItemController* Init(QObject* parent = nullptr){
        return m_instance = new ItemController(parent);
    }

    [[nodiscard]] static ItemController* Instance(){
        return m_instance;
    }

   signals:
    void countChanged();
    void currentItemChanged();
    void dataChanged();

   public slots:
    void updateItem(qsizetype index, const ItemInfo &client);
    void removeItem(qsizetype index);

   private:
    explicit ItemController(QObject* parent = nullptr);

    inline static ItemController* m_instance = nullptr;
    QChar m_delimiter = '-';
    QList<ItemInfo*> m_items;
    ItemInfo* m_currentItem = nullptr;
};