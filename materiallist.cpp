#include "materiallist.h"

MaterialList::MaterialList(ColorMap &cm, const QString& colorThemeFileName, const QString& outfile)
    : m_outfile(outfile), m_colorMap(cm)
{
    bool ok = m_colorTheme.read(colorThemeFileName);
    Q_ASSERT(ok);

    for (int i = 0; i < m_colorMap.count(); i++) {
        ColorMap::Entry *cme = m_colorMap.get(i);
        ColorTheme::Entry *cte = m_colorTheme.find(cme->id);
        Q_ASSERT(cte);
        MaterialPtr material(new Material());
        material->setColor(cte->color);
        material->setId(cte->id);
        material->setName(cme->txt);
        m_data.push_back(material);
    }
}


MaterialPtr MaterialList::get(int index)
{
    //TODO: verify index
    return m_data[index];
}

int MaterialList::count()
{
    return m_data.size();
}

bool MaterialList::set(int index, MaterialPtr material)
{
    //TODO: need to verify the data
    m_data[index] = material;
    return true;
}

bool MaterialList::save()
{
    // todo need to implement this
    return true;
}
