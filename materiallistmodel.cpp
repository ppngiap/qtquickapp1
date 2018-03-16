#include "materiallistmodel.h"

MaterialListModel::MaterialListModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_theme("light")
{
    // Set names to the role name hash container (QHash<int, QByteArray>)
    // model.name, model.hue, model.saturation, model.brightness
    m_roleNames[NameRole] = "name";
    m_roleNames[HueRole] = "hue";
    m_roleNames[SaturationRole] = "saturation";
    m_roleNames[BrightnessRole] = "brightness";
    m_roleNames[RgbRole] = "rgb";

    // Append the color names as QColor to the data list (QList<QColor>)
    for(const QString& name : QColor::colorNames()) {
        m_dataLight.append(QColor(name));
    }

    m_data = &m_dataLight;
}

MaterialListModel::~MaterialListModel()
{
}

int MaterialListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data->count();
}

QVariant MaterialListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data->count()) {
        return QVariant();
    }
    const QColor& color = m_data->at(row);
    //qDebug() << row << role << color;
    switch(role) {
    case NameRole:
        // return the color name as hex string (model.name)
        return QColor::colorNames().at(row);
    case HueRole:
        // return the hue of the color (model.hue)
        return color.hueF();
    case SaturationRole:
        // return the saturation of the color (model.saturation)
        return color.saturationF();
    case BrightnessRole:
        // return the brightness of the color (model.brightness)
        return color.lightnessF();
    case RgbRole:
        // return the color name as hex string (model.rgb)
        return color.name();
    }
    return QVariant();
}

QHash<int, QByteArray> MaterialListModel::roleNames() const
{
    return m_roleNames;
}

QString MaterialListModel::theme() const
{
    qWarning() << "readTheme: " << m_theme;
    return m_theme;
}
void MaterialListModel::setTheme(QString theme)
{
    qWarning() << "setTheme : " << theme;
    if (m_theme == theme) {
        return;
    }

    beginResetModel();
    if (theme == "light") {
        m_data = &m_dataLight;
    } else if (theme == "dark") {
        m_data = &m_dataDark;
    } else {
        m_data = &m_dataBasic;
    }
    m_theme = theme;
    endResetModel();
}
