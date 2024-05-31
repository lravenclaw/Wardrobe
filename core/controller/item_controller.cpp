#include "core/controller/item_controller.h"

ItemController::ItemController(QObject *parent)
    : QAbstractListModel(parent) {
}

int ItemController::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }

    return m_items.size();
}

QVariant ItemController::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (!index.isValid() || index.row() >= m_items.size() || index.row() < 0) {
        return QVariant();
    }

    auto* item = m_items[index.row()];

    auto value = magic_enum::enum_value<ItemRole>(role);
    switch (value) {
        case ItemRole::Id:
            return QVariant::fromValue(item->id());
        case ItemRole::Material:
            return QVariant::fromValue(item->material());
        case ItemRole::Size:
            return QVariant::fromValue(item->size());
        case ItemRole::Brand:
            return QVariant::fromValue(item->brand());
        case ItemRole::Details:
            return QVariant::fromValue(item->details());
        case ItemRole::Style:
            return QVariant::fromValue(item->style());
        case ItemRole::Pattern:
            return QVariant::fromValue(item->pattern());
        case ItemRole::PlaceOfPurchase:
            return QVariant::fromValue(item->placeOfPurchase());
        case ItemRole::WashPrinciple:
            return QVariant::fromValue(item->washPrinciple());
        case ItemRole::Season:
            return QVariant::fromValue(item->season());
        case ItemRole::Color:
            return QVariant::fromValue(item->color());
        case ItemRole::Price:
            return QVariant::fromValue(item->price());
        case ItemRole::Sources:
            return QVariant::fromValue(item->sources());
        default:
            return {};
    }
}

QHash<int, QByteArray> ItemController::roleNames() const {
    QHash<int, QByteArray> roles;
    for (auto& role : magic_enum::enum_values<ItemRole>()) {
        roles[magic_enum::enum_integer(role)] = QByteArray(magic_enum::enum_name(role).data());
    }
    return roles;
}

void ItemController::addItem(ItemInfo* item) {
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.append(item);
    endInsertRows();
    emit countChanged();
}

void ItemController::removeItem(qsizetype index) {
    if (index < 0 || index >= m_items.size()) {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    delete m_items[index];
    m_items.removeAt(index);
    endRemoveRows();
    emit countChanged();
}

ItemInfo* ItemController::currentItem() const {
    return m_currentItem;
}

[[nodiscard]] ItemInfo* ItemController::itemAt(qsizetype index) const {
    if (index < 0 || index >= m_items.size()) {
        return nullptr;
    }

    return m_items[index];
}

void ItemController::setCurrentItem(ItemInfo* item) {
    m_currentItem = item;
    emit currentItemChanged();
}

void ItemController::setDelimiter(QChar delimiter) {
    m_delimiter = delimiter;
}

void ItemController::loadItems(QFile &file) {
    qDebug() << "Loading items from: " << file.fileName();


    QTextStream in(&file);
    QString data = in.readAll();
    QStringList items = data.split(m_delimiter);

    qDebug() << "File data: " << data << '\n'
             << "Splited data size: " << items.size() << '\n';

    for (auto& item_str : items) {
        auto item_data = item_str.split('\n');
        if (item_data.size() != 11) {
            continue;
        }

        qDebug() << "Item data: " << item_data << '\n';

        auto* item = new ItemInfo();

        item->setId(item_data[0].toInt());
        item->setMaterial(item_data[1]);
        item->setSize(item_data[2]);
        item->setBrand(item_data[3]);
        item->setDetails(item_data[4]);
        item->setStyle(item_data[5]);
        item->setPattern(item_data[6]);
        item->setPlaceOfPurchase(item_data[7]);
        item->setWashPrinciple(item_data[8]);
        item->setSeason(item_data[9]);
        item->setPrice(item_data[10].toDouble());

        addItem(item);
    }
}

void ItemController::saveItems(QFile &file) {
    qDebug() << "Saving items to: " << file.fileName();

    QTextStream out(&file);
    for (const auto &item : m_items) {
        out << item->id() << '\n';
        out << item->material() << '\n';
        out << item->size() << '\n';
        out << item->brand() << '\n';
        out << item->details() << '\n';
        out << item->style() << '\n';
        out << item->pattern() << '\n';
        out << item->placeOfPurchase() << '\n';
        out << item->washPrinciple() << '\n';
        out << item->season() << '\n';
        out << item->price() << '\n';
        out << "-\n";
    }
}

void ItemController::updateItem(qsizetype index, const ItemInfo &item) {
    if (index < 0 || index >= m_items.size()) {
        return;
    }

    m_items[index]->setId(item.id());
    m_items[index]->setMaterial(item.material());
    m_items[index]->setSize(item.size());
    m_items[index]->setBrand(item.brand());
    m_items[index]->setDetails(item.details());
    m_items[index]->setStyle(item.style());
    m_items[index]->setPattern(item.pattern());
    m_items[index]->setPlaceOfPurchase(item.placeOfPurchase());
    m_items[index]->setWashPrinciple(item.washPrinciple());
    m_items[index]->setSeason(item.season());
    m_items[index]->setPrice(item.price());
    m_items[index]->setSources(item.sources());

    emit dataChanged();
}