#pragma once

#include <QObject>
#include <QString>
#include <QTextStream>
#include <cstdint>

class ItemInfo : public QObject {
    Q_OBJECT

    Q_PROPERTY(int64_t id READ id WRITE setId NOTIFY idChanged REQUIRED)
    Q_PROPERTY(QString material READ material WRITE setMaterial NOTIFY materialChanged)
    Q_PROPERTY(QString size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QString brand READ brand WRITE setBrand NOTIFY brandChanged)
    Q_PROPERTY(QString details READ details WRITE setDetails NOTIFY detailsChanged)
    Q_PROPERTY(QString style READ style WRITE setStyle NOTIFY styleChanged)
    Q_PROPERTY(QString pattern READ pattern WRITE setPattern NOTIFY patternChanged)
    Q_PROPERTY(QString placeOfPurchase READ placeOfPurchase WRITE setPlaceOfPurchase NOTIFY placeOfPurchaseChanged)
    Q_PROPERTY(QString washPrinciple READ washPrinciple WRITE setWashPrinciple NOTIFY washPrincipleChanged)
    Q_PROPERTY(QString season READ season WRITE setSeason NOTIFY seasonChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(double price READ price WRITE setPrice NOTIFY priceChanged REQUIRED)
    Q_PROPERTY(QVector<QString> sources READ sources WRITE setSources NOTIFY sourcesChanged)

   public:
    explicit ItemInfo(QObject *parent = nullptr);

    [[nodiscard]] int64_t id() const;
    void setId(int64_t id);

    [[nodiscard]] QString material() const;
    void setMaterial(const QString &material);

    [[nodiscard]] QString size() const;
    void setSize(const QString &size);

    [[nodiscard]] QString brand() const;
    void setBrand(const QString &brand);

    [[nodiscard]] QString details() const;
    void setDetails(const QString &details);

    [[nodiscard]] QString style() const;
    void setStyle(const QString &style);

    [[nodiscard]] QString pattern() const;
    void setPattern(const QString &pattern);

    [[nodiscard]] QString placeOfPurchase() const;
    void setPlaceOfPurchase(const QString &placeOfPurchase);

    [[nodiscard]] QString washPrinciple() const;
    void setWashPrinciple(const QString &washPrinciple);

    [[nodiscard]] QString season() const;
    void setSeason(const QString &season);

    [[nodiscard]] QString color() const;
    void setColor(const QString &color);

    [[nodiscard]] double price() const;
    void setPrice(double price);

    [[nodiscard]] QVector<QString> sources() const;
    void setSources(const QVector<QString> &sources);
    void addSource(const QString &source);

   signals:
    void idChanged();
    void materialChanged();
    void sizeChanged();
    void brandChanged();
    void detailsChanged();
    void styleChanged();
    void patternChanged();
    void placeOfPurchaseChanged();
    void washPrincipleChanged();
    void seasonChanged();
    void colorChanged();
    void priceChanged();
    void sourcesChanged();

   private:
    int64_t m_id;
    QString m_material;
    QString m_size;
    QString m_brand;
    QString m_details;
    QString m_style;
    QString m_pattern;
    QString m_placeOfPurchase;
    QString m_washPrinciple;
    QString m_season;
    QString m_color;
    double m_price;

    QVector<QString> m_sources;
};