#ifndef FONTSIZEMODEL_H
#define FONTSIZEMODEL_H

#include <QObject>

class FontSizeModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString increment READ increment WRITE setIncrement NOTIFY incrementChanged)

public:
    explicit FontSizeModel(QObject *parent = nullptr);


    QString increment() const;

signals:
    void incrementChanged(QString increment);

public slots:
    void setIncrement(QString increment);

private:
    QString m_increment;
};

#endif // FONTSIZEMODEL_H
