#ifndef COLORTHEME_H
#define COLORTHEME_H

#include <QObject>
#include <QDomDocument>
#include <QColor>

class ColorTheme
{
public:
    struct Entry {
        QString id;
        QColor color;
    };
public:
    ColorTheme();

    bool read(const QString &fileName);
    bool write(const QString &fileName);
    bool update(const QString &id, const QString& val);
    void print();

    Entry* get(int index);
    Entry* find(const QString &id);
    int count() const;

private:
    void find(const QString& id, QDomElement& de);

private:
    QDomDocument mDocument;
    std::vector<Entry> m_data;
};

#endif // COLORTHEME_H
