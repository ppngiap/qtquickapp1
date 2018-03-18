#ifndef MATERIAL_H
#define MATERIAL_H

#include <QObject>
#include <QDomDocument>
#include <QColor>
#include <memory>

class Material : QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QString id READ id WRITE setId)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QColor color READ color WRITE setColor)

    QString id() const
    {
        return m_id;
    }
    QString name() const
    {
        return m_name;
    }

    QColor color() const
    {
        return m_color;
    }

public slots:
    void setId(QString id)
    {
        m_id = id;
    }
    void setName(QString name)
    {
        m_name = name;
    }
    void setColor(QColor color)
    {
        m_color = color;
    }

private:
    QString m_id;
    QString m_name;
    QColor m_color;
};

typedef std::shared_ptr<Material> MaterialPtr;

#endif // MATERIAL_H
