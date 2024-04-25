

#include "friendItemDelegate.h"

FriendItemDelegate::FriendItemDelegate()
{
}

FriendItemDelegate::~FriendItemDelegate()
{
}

QSize FriendItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QSize(350, 70);
}

void FriendItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid()) {
        // QPainter *savePainter = new QPainter();
        // savePainter = painter;
        painter->save();

        // 反锯齿
        painter->setRenderHint(QPainter::Antialiasing);
        
        // 获取数据
        QString avatar = index.data(FriendListModel::Avatar).toString();
        QString nickname = index.data(FriendListModel::Nickname).toString();
        QString msgContent = index.data(FriendListModel::RecentMsgContent).toString();
        QString msgTime = index.data(FriendListModel::RecentMsgTime).toString();
        QString msgNum = index.data(FriendListModel::UnreadMsgNum).toString();

        // item 矩形区域
        QRectF itemRect;
        itemRect.setX(option.rect.x());
        itemRect.setY(option.rect.y());
        itemRect.setWidth(option.rect.width() - 1);
        itemRect.setHeight(option.rect.height() - 1);

        QPainterPath path;
        // 鼠标悬停或者选中时改变背景色
        if (option.state.testFlag(QStyle::State_MouseOver)) {
            // painter->setPen(QPen(QColor("#ebeced")));
            path.setFillRule( Qt::WindingFill );   //设置填充方式
            path.addRoundedRect(itemRect, 0, 0);
            painter->fillPath(path, QBrush(QColor("#EBEBEB")));
        }

        // 好友头像
        QPoint avatarPoint(itemRect.left() + 16, itemRect.top() + 10);
        QSize avatarSize(50, 50);
        QRectF avatarRect = QRect(avatarPoint, avatarSize);
        // 画圆
        QPainterPath avatarPath;
        avatarPath.setFillRule( Qt::WindingFill );   //设置填充方式
        avatarPath.addRoundedRect(avatarRect, 30, 30);
        painter->fillPath(avatarPath,  QBrush(QColor(55, 144, 250)));

        // // 设置背景色
        // painter->setBrush(Qt::blue);
        // painter->drawRect(avatarRect);

        // 好友昵称或备注
        QPoint nicknamePoint(avatarRect.right() + 8, itemRect.top() + 10);
        QSize nicknameSize(170, 25);
        QRectF nicknameRect = QRect(nicknamePoint, nicknameSize);

        // 最近聊天内容
        QPoint contentPoint(avatarRect.right() + 8, itemRect.bottom() - 34);
        QSize contentSize(186, 20);
        QRectF contentRect = QRect(contentPoint, contentSize);
        // contentRect.setBottom(itemRect.bottom() - 16);

        // 最近聊天时间
        QPoint timePoint(itemRect.right() - 80, itemRect.top() + 10);
        QSize timeSize(60, 20);
        QRectF timeRect = QRect(timePoint, timeSize);
        timeRect.setRight(itemRect.right() - 20);

        // 未读消息数
        QPoint msgNumPoint(itemRect.right() - 50, itemRect.bottom() - 30);
        QSize msgNumSize(30, 20);
        QRectF msgNumRect = QRect(msgNumPoint, msgNumSize);
        msgNumRect.setRight(itemRect.right() - 20);
        // 画圆
        QPainterPath numPath;
        numPath.setFillRule( Qt::WindingFill );   //设置填充方式
        numPath.addRoundedRect (msgNumRect, 10, 10);
        painter->fillPath(numPath,  QBrush(QColor(250, 55, 55)));

        //绘制文字
        QTextOption option;
        QFont textFont = painter->font();

        option.setAlignment(Qt::AlignLeft | Qt::AlignTop);
        textFont.setPixelSize(16);
        painter->setFont(textFont);
        painter->drawText(nicknameRect, nickname, option);

        // 白色的字
        painter->setPen(QPen(Qt::white));
        option.setAlignment(Qt::AlignCenter);

        textFont.setPixelSize(22);
        painter->setFont(textFont);
        painter->drawText(avatarRect, avatar, option);
        
        textFont.setPixelSize(12);
        painter->setFont(textFont);
        painter->drawText(msgNumRect, msgNum, option);

        // 灰色的字
        painter->setPen(QPen(QColor("#8C8C8C")));

        option.setAlignment(Qt::AlignLeft | Qt::AlignTop);
        textFont.setPixelSize(14);
        painter->setFont(textFont);
        painter->drawText(contentRect, msgContent, option);

        option.setAlignment(Qt::AlignRight | Qt::AlignTop);
        painter->setFont(QFont(painter->fontInfo().family(), 12));
        painter->drawText(timeRect, msgTime, option);

        // QObject::setProperty("isWindowButton", 0x1);
        // QObject::setProperty("useIconHighlightEffect", 0x2);
        // setFlat(true);
        painter->restore();
    }
}

// bool FriendItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
// {

// }