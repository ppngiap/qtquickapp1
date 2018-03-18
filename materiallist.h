#ifndef MATERIALLIST_H
#define MATERIALLIST_H

#include <vector>
#include "material.h"
#include "colormap.h"
#include "colortheme.h"



class MaterialList
{
public:
    MaterialList(ColorMap &cm, const QString& colorThemeFileName, const QString& outfile);

    MaterialPtr get(int index);
    int count();
    bool set(int index, MaterialPtr material);
    bool save();

private:
    QString m_outfile;
    ColorMap &m_colorMap;
    ColorTheme m_colorTheme;
    std::vector<MaterialPtr> m_data;
};

#endif // MATERIALLIST_H
