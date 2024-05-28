#include "core/model/item_info.h"

ItemInfo::ItemInfo(QObject *parent)
    : QObject(parent)
    , m_id(0)
    , m_price(0.0) {
}

int64_t ItemInfo::id() const {
    return m_id;
}

void ItemInfo::setId(int64_t id) {
    if (m_id == id) {
        return;
    }

    m_id = id;
    emit idChanged();
}

QString ItemInfo::material() const {
    return m_material;
}

void ItemInfo::setMaterial(const QString &material) {
    if (m_material == material) {
        return;
    }

    m_material = material;
    emit materialChanged();
}

QString ItemInfo::size() const {
    return m_size;
}

void ItemInfo::setSize(const QString &size) {
    if (m_size == size) {
        return;
    }

    m_size = size;
    emit sizeChanged();
}

QString ItemInfo::brand() const {
    return m_brand;
}

void ItemInfo::setBrand(const QString &brand) {
    if (m_brand == brand) {
        return;
    }

    m_brand = brand;
    emit brandChanged();
}

QString ItemInfo::details() const {
    return m_details;
}

void ItemInfo::setDetails(const QString &details) {
    if (m_details == details) {
        return;
    }

    m_details = details;
    emit detailsChanged();
}

QString ItemInfo::style() const {
    return m_style;
}

void ItemInfo::setStyle(const QString &style) {
    if (m_style == style) {
        return;
    }

    m_style = style;
    emit styleChanged();
}

QString ItemInfo::pattern() const {
    return m_pattern;
}

void ItemInfo::setPattern(const QString &pattern) {
    if (m_pattern == pattern) {
        return;
    }

    m_pattern = pattern;
    emit patternChanged();
}

QString ItemInfo::placeOfPurchase() const {
    return m_placeOfPurchase;
}

void ItemInfo::setPlaceOfPurchase(const QString &placeOfPurchase) {
    if (m_placeOfPurchase == placeOfPurchase) {
        return;
    }

    m_placeOfPurchase = placeOfPurchase;
    emit placeOfPurchaseChanged();
}

QString ItemInfo::washPrinciple() const {
    return m_washPrinciple;
}

void ItemInfo::setWashPrinciple(const QString &washPrinciple) {
    if (m_washPrinciple == washPrinciple) {
        return;
    }

    m_washPrinciple = washPrinciple;
    emit washPrincipleChanged();
}

QString ItemInfo::season() const {
    return m_season;
}

void ItemInfo::setSeason(const QString &season) {
    if (m_season == season) {
        return;
    }

    m_season = season;
    emit seasonChanged();
}

QString ItemInfo::color() const {
    return m_color;
}

double ItemInfo::price() const {
    return m_price;
}

void ItemInfo::setPrice(double price) {
    if (qFuzzyCompare(m_price, price)) {
        return;
    }

    m_price = price;
    emit priceChanged();
}

QVector<QString> ItemInfo::sources() const {
    return m_sources;
}

void ItemInfo::setSources(const QVector<QString> &sources) {
    if (m_sources == sources) {
        return;
    }

    m_sources = sources;
    emit sourcesChanged();
}

void ItemInfo::addSource(const QString &source) {
    m_sources.append(source);
    emit sourcesChanged();
}
