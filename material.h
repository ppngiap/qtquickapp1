#ifndef MATERIAL_H
#define MATERIAL_H

#include <QObject>
#include <QDomDocument>

class Material
{
public:
    Material();

    bool read(const QString& fileName);
    bool write(const QString& fileName);
    bool update(const QString& id, const QString& val);
    void print();

private:
    void find(const QString& id, QDomElement& de);

private:
    QDomDocument mDocument;
};

#endif // MATERIAL_H
