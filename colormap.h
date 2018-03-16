#ifndef COLORMAP_H
#define COLORMAP_H

#include <QObject>
#include <QDomDocument>

class ColorMap
{
public:
    struct Entry {
        QString id;
        QString txt;
    };

public:
    ColorMap();

    bool read(const QString& fileName);
    bool write(const QString& fileName);
    bool update(const QString& id, const QString& val);
    void print();

    const Entry& get(int index);

private:
    void find(const QString& id, QDomElement& de);

private:
    QDomDocument mDocument;
    std::vector<Entry> m_data;
};

#endif // COLORMAP_H
