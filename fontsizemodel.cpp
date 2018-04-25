#include "fontsizemodel.h"
#include <QDebug>

FontSizeModel::FontSizeModel(QObject *parent)
    : QObject(parent)
    , m_increment("2")
{

}

QString FontSizeModel::increment() const
{
    qDebug() << "FonSizeModel::increment "  << m_increment;
    return m_increment;
}

void FontSizeModel::setIncrement(QString increment)
{
    if (m_increment == increment)
        return;

    m_increment = increment;
    qDebug() << "FontSizeModel::setIncrement " << increment;
    emit incrementChanged(m_increment);
}
