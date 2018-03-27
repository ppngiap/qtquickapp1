#ifndef MATERIALLISTMODEL_H
#define MATERIALLISTMODEL_H

#include <QtCore>
#include <QtGui>

#include "project.h"

class MaterialListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString theme READ theme WRITE setTheme)
public:
    // Define the role names to be used
    enum RoleNames {
        MaterialRole = Qt::UserRole
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
    Project *m_project;
    MaterialList *m_data;
    QHash<int, QByteArray> m_roleNames;
    QString m_theme; // one of {basic,light,dark}
};

#endif //  MATERIALLISTMODEL_H
