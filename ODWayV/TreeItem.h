#ifndef TREEITEM_H
#define TREEITEM_H

#include "ODMBase/ODBaseTypes.h"

#include <QList>
#include <QVariant>
#include <QStringList>
#include <QModelIndex>

class TreeItem
{
public:
    TreeItem();
    TreeItem(const StringList &data, TreeItem* parent);
    ~TreeItem();

    void appendChild(TreeItem *child);
    void deleteAllChild();

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parent();
    void setParent(TreeItem *parent);

private:
    TreeItem *m_parentItem;
    QList<TreeItem*> m_childItems;
    StringList m_itemData;
};

#endif // TREEITEM_H
