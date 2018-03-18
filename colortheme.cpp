#include "colortheme.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QtGlobal>

ColorTheme::ColorTheme()
{

}

bool ColorTheme::read(const QString& fileName)
{
    if (fileName.isEmpty())
        return false;

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qWarning() << "ColorTheme::read" << " Failed to read file "
                   << fileName << ".  Got error: " << file.errorString();
        return false;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!mDocument.setContent(&file, true, &errorStr, &errorLine, &errorColumn)) {
        qWarning() << "ColorTheme read: " <<  QString("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr);
        return false;
    }

    QDomElement root = mDocument.documentElement();
    QDomElement colors = root.firstChildElement("library_colors");
    if (colors.isNull()) {
        qWarning() << "COLORTHEME Emtpy colors";
        return false;
    }
    QDomElement child = colors.firstChildElement("color");
    while (!child.isNull()) {
        QString id = child.attribute("id");

        bool ok;
        QString s = child.text();
        unsigned int rgba = s.toUInt(&ok, 16);
        Q_ASSERT(ok);
        if (!ok) {
            qWarning() << "COLORTHEME Failed to convert to hex for " << id << "with value " << s;
        }

        Entry e;
        e.id = id;
        e.color = QColor::fromRgba(rgba);

        m_data.push_back(e);

        qDebug() << "id = " << id << ", val = " << s;
        child = child.nextSiblingElement("color");
    }


    return true;
}

ColorTheme::Entry *ColorTheme::get(int index)
{
    return &m_data[index];
}

ColorTheme::Entry* ColorTheme::find(const QString &id)
{
    ColorTheme::Entry *entry = NULL;
    for (auto e : m_data) {
        if (e.id == id) {
            entry = &e;
            break;
        }
    }

    return entry;
}
int ColorTheme::count() const
{
    return m_data.size();
}

bool ColorTheme::write(const QString& fileName)
{
    const int IndentSize = 4;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qWarning() << "ColorTheme::write" << " Failed to open file "
                   << fileName << ".  Got error: " << file.errorString();
        return false;
    }

    QTextStream out(&file);
    mDocument.save(out, IndentSize);

    return true;
}

void ColorTheme::print()
{
    QDomElement root = mDocument.documentElement();
    QDomElement colors = root.firstChildElement("library_colors");
    if (colors.isNull()) return;
    QDomElement child = colors.firstChildElement("color");
    while (!child.isNull()) {
        qDebug() << "id = " << child.attribute("id") << ", val = " << child.text();
        child = child.nextSiblingElement("color");
    }
}

bool ColorTheme::update(const QString& id, const QString& val)
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
void ColorTheme::find(const QString& id, QDomElement& de)
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
