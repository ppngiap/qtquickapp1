#ifndef MATERIALLISTMODEL_H
#define MATERIALLISTMODEL_H

#include <QtCore>
#include <QtGui>

class MaterialListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString theme READ theme WRITE setTheme)
public:
    // Define the role names to be used
    enum RoleNames {
        NameRole = Qt::UserRole,
        HueRole = Qt::UserRole+2,
        SaturationRole = Qt::UserRole+3,
        BrightnessRole = Qt::UserRole+4,
        RgbRole = Qt::UserRole+5
    };

    explicit MaterialListModel(QObject *parent = 0);
    ~MaterialListModel();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    QString theme() const;

public slots:
    void setTheme(QString theme);

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;
private:
    QList<QColor> m_dataBasic;
    QList<QColor> m_dataLight;
    QList<QColor> m_dataDark;
    QList<QColor> *m_data;
    QHash<int, QByteArray> m_roleNames;
    QString m_theme; // one of {basic,light,dark}
};

#endif //  MATERIALLISTMODEL_H
