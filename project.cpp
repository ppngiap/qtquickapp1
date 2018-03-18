#include "project.h"

Project* Project::s_instance = NULL;

Project* Project::instance()
{
    if (Project::s_instance == NULL) {
        Project::s_instance = new Project();
    }

    return Project::s_instance;
}


Project::Project()
{
    bool ok = m_colorMap.read("input/colormap.xml");
    Q_ASSERT(ok);

    m_basicTheme = new MaterialList(m_colorMap, "input/day.xml", "output/day.xml");
    m_lightTheme = new MaterialList(m_colorMap, "input/light.xml", "output/light.xml");
    m_darkTheme = new MaterialList(m_colorMap, "input/night.xml", "output/night.xml");
}

Project::~Project()
{
    delete m_darkTheme;
    delete m_lightTheme;
    delete m_basicTheme;
}

MaterialList* Project::basicTheme()
{
    return m_basicTheme;
}

MaterialList* Project::lightTheme()
{
    return m_lightTheme;
}

MaterialList* Project::darkTheme()
{
    return m_darkTheme;
}
