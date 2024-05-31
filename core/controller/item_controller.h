#pragma once

#include <QAbstractListModel>
#include <QChar>
#include <QDebug>
#include <QFile>
#include <QList>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QtGlobal>
#include <magic_enum_all.hpp>

#include "core/model/item_info.h"

class ItemController : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(ItemInfo* currentItem READ currentItem WRITE setCurrentItem NOTIFY currentItemChanged)

   public:
    enum class ItemRole {
        Id = Qt::UserRole + 1,
        Material,
        Size,
        Brand,
        Details,
        Style,
        Pattern,
        PlaceOfPurchase,
        WashPrinciple,
        Season,
        Color,
        Price,
        Sources
    };

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    void addItem(ItemInfo* item);

    [[nodiscard]] ItemInfo* currentItem() const;
    [[nodiscard]] ItemInfo* itemAt(qsizetype index) const;

    void setCurrentItem(ItemInfo* item);

    // Curently working with txt files
    // In future will be changed to work with csv file or
    // database files
    void setDelimiter(QChar delimiter);
    void loadItems(QFile &file);
    void saveItems(QFile &file);

    [[nodiscard]] static ItemController* init(QObject* parent = nullptr){
        return m_instance = new ItemController(parent);
    }

    [[nodiscard]] static ItemController* instance(){
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