#ifndef MATERIALMAP_H
#define MATERIALMAP_H

#include <QObject>
#include <QDomDocument>

class MaterialMap
{
public:
    struct Entry {
        QString id;
        QString txt;
    };

public:
    MaterialMap();

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

#endif // MATERIAL_H
