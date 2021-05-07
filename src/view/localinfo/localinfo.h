/*
 * Copyright (C) 2020, KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef LOCALINFO_H
#define LOCALINFO_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

#include "../common/globalsizedata.h"

class LocalInfo : public QWidget
{
    Q_OBJECT
public:
    explicit LocalInfo(QWidget *parent = nullptr);
    ~LocalInfo();

    // 初始化组件
    void setWidgetUi();

    // 设置组件样式
    void setWidgetStyle();
    int w;
    int h;

    QLabel *u_LabelIcon;//头像
    QLabel *s_LabelIcon;//搜索图标
    QLabel *u_LabelName;/*名字*/
    QLabel *u_LabelIp;/*IP*/
    QPushButton *u_ButtonUpdate;/*修改本机昵称按钮*/
    QPushButton *u_ButtonFile;/*打开文件保存目录按钮*/

    void setText(QString name,QString IP);

    QLineEdit *s_EditSearch;

private:
    QVBoxLayout *m_localInfoLayout; // 本机信息总体布局
    QHBoxLayout *m_nameLayout;      // 本机昵称布局
    QVBoxLayout *m_ipLayout;        // 本机IP布局
    QHBoxLayout *m_avatarLayout;    // 本机头像布局
    QHBoxLayout *m_searchLayout;    // 搜索图像布局文本框

private slots:
    // 进行置顶、最小化、关闭操作
    void onClicked();
    bool eventFilter(QObject *watch,QEvent *e);
};




#endif // LOCALINFO_H
