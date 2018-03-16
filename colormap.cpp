#include "colormap.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QtGlobal>

ColorMap::ColorMap()
{

}

bool ColorMap::read(const QString& fileName)
{
    if (fileName.isEmpty())
        return false;

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qWarning() << "ColorMap::read" << " Failed to read file "
                   << fileName << ".  Got error: " << file.errorString();
        return false;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!mDocument.setContent(&file, true, &errorStr, &errorLine, &errorColumn)) {
        qWarning() << "ColorMap read: " <<  QString("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr);
        return false;
    }

    QDomElement root = mDocument.documentElement();
    QDomElement child = root.firstChildElement("color");
    while (!child.isNull()) {
        Entry e;
        e.id = child.attribute("id");
        e.txt = child.attribute("txt");
        m_data.push_back(e);
//        qDebug() << "id = " << child.attribute("id") << ", txt = " << child.attribute("txt");
        child = child.nextSiblingElement("color");
    }


    return true;
}

const ColorMap::Entry& ColorMap::get(int index)
{
    return m_data[index];
}

bool ColorMap::write(const QString& fileName)
{
    const int IndentSize = 4;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qWarning() << "ColorMap::write" << " Failed to open file "
                   << fileName << ".  Got error: " << file.errorString();
        return false;
    }

    QTextStream out(&file);
    mDocument.save(out, IndentSize);

    return true;
}

void ColorMap::print()
{
    for (auto e : m_data) {
        qDebug() << "id = " << e.id << ", txt = " << e.txt;
    }
}

bool ColorMap::update(const QString& id, const QString& val)
{
    QDomElement de;

    this->find(id, de);
    if (de.isNull()) {
        return false;
    }

    QDomNode dn = de.firstChild();
    if (!dn.isNull() && dn.nodeType() == QDomNode::NodeType::TextNode) {
        QDomText *dt = (QDomText *)&dn;
        dt->setData(val);
    }

    return true;
}

//de.isNull() is true if cannot find the id
void ColorMap::find(const QString& id, QDomElement& de)
{
    QDomElement root = mDocument.documentElement();
    QDomElement colors = root.firstChildElement("library_colors");
    if (colors.isNull()) return;
    QDomElement child = colors.firstChildElement("color");
    while (!child.isNull()) {
        qDebug() << "id = " << child.attribute("id") << ", val = " << child.text();
        if (child.attribute("id") ==  id) {
            de = child;
            return;
        }
        child = child.nextSiblingElement("color");
    }
}
