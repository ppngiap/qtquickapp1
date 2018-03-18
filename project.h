#ifndef PROJECT_H
#define PROJECT_H

#include "materiallist.h"



class Project
{
public:
    Project();
    ~Project();

    static Project *instance();

    MaterialList* basicTheme();
    MaterialList* lightTheme();
    MaterialList* darkTheme();

private:
    static Project *s_instance;
    ColorMap     m_colorMap;
    MaterialList *m_basicTheme;
    MaterialList *m_lightTheme;
    MaterialList *m_darkTheme;

};

#endif // PROJECT_H
