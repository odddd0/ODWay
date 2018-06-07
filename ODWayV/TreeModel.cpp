
#include <ODWayP/ODPTime.h>

#include "TreeModel.h"

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_rootItem(NULL)
{
    updateSum();
}

TreeModel::~TreeModel()
{
    delete m_rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    return 2;
    //返回实际的列数 (实际是他返回了0，因为根节点用的是无参的构造)，TreeView控件会认为表是空表，不获取数据
    if (parent.isValid())
    {
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    }
    else
    {
        return m_rootItem->columnCount();
    }
}

QHash<int, QByteArray> TreeModel::roleNames() const
{
    QHash<int, QByteArray> names(QAbstractItemModel::roleNames());
    names[NAME] = "name";
    names[SIMPLIFY] = "simplify";
    return names;
}

void TreeModel::updateSum()
{
    _classifyList.clear();
    _kindFirstList.clear();
    _kindSecondList.clear();
    m_rootItem = new TreeItem;

    ODPTime::Instance()->GetCurSumList(_classifyList, _kindFirstList, _kindSecondList);
    m_daySum = ODPTime::Instance()->GetCurSum().c_str();

    for (int i = 0; i < _classifyList.size(); ++i)
    {
        auto item_I = new TreeItem(_classifyList[i], m_rootItem);
        m_rootItem->appendChild(item_I);

        for (int j = 0; j < _kindFirstList[i].size(); ++j)
        {
            auto item_J = new TreeItem(_kindFirstList[i][j], item_I);
            item_I->appendChild(item_J);

            for (int k = 0; k < _kindSecondList[i][j].size(); ++k)
            {
                auto item_K = new TreeItem(_kindSecondList[i][j][k], item_J);
                item_J->appendChild(item_K);
            }
        }
    }
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    switch (role)
    {
    case NAME:
    {
        return static_cast<TreeItem*>(index.internalPointer())->data(0);
    }
    case SIMPLIFY:
    {
        return static_cast<TreeItem*>(index.internalPointer())->data(1);
    }
    }
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return 0;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    TreeItem *parentItem;
    if (!parent.isValid())
    {
        parentItem = m_rootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == m_rootItem)
    {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
    {
        return 0;
    }

    if (!parent.isValid())
    {
        parentItem = m_rootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}
