#include "materiallistmodel.h"

//#define DXML

MaterialListModel::MaterialListModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_project(Project::instance())
    , m_data(m_project->lightTheme())
    , m_theme("light")
{
    // Set names to the role name hash container (QHash<int, QByteArray>)
    m_roleNames[MaterialRole] = "material";
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
    switch(role) {
    case MaterialRole:
        MaterialPtr material = m_data->get(row);
#ifdef DXML
        qWarning() << "(" << material->name() << ", " << material->color() << ", " << material->id() << ")";
#endif
        return QVariant::fromValue<QObject *>(material.get());
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
        m_data = m_project->lightTheme();
    } else if (theme == "dark") {
        m_data = m_project->darkTheme();
    } else {
        m_data = m_project->basicTheme();
    }
    m_theme = theme;
    endResetModel();
}
