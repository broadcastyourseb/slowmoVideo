/*
slowmoUI is a user interface for slowmoVideo.
Copyright (C) 2011  Simon A. Eugster (Granjow)  <simon.eu@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
*/

#ifndef CANVAS_H
#define CANVAS_H

#include "nodelist.h"

#include <QWidget>
#include <QList>

class QColor;
class QPoint;
class Node;

namespace Ui {
    class Canvas;
}

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();

    enum ToolMode {ToolMode_Add, ToolMode_Select};
    enum Abort { Abort_General, Abort_Selection };

    static QColor lineCol;
    static QColor nodeCol;
    static QColor gridCol;
    static QColor selectedCol;
    static QColor backgroundCol;


public slots:
    void slotAbort(Canvas::Abort abort);
    void slotDeleteNodes();
    void slotSetToolMode(Canvas::ToolMode mode);

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void leaveEvent(QEvent *);

private:
    Ui::Canvas *ui;
    QPoint m_lastMousePos;
    QPoint m_mouseStart;
    bool m_mouseWithinWidget;
    unsigned int m_distLeft;
    unsigned int m_distBottom;
    unsigned int m_distRight;
    unsigned int m_distTop;
    float m_t0x;
    float m_t0y;
    float m_tmaxx;
    float m_tmaxy;
    unsigned int m_secResX;
    unsigned int m_secResY;

    bool m_moveAborted;

    ToolMode m_mode;

    NodeList m_nodes;

    const Node convertCanvasToTime(const QPoint &p) const;
    const QPoint convertTimeToCanvas(const Node &p) const;

    bool insideCanvas(const QPoint& pos);

    bool selectAt(const QPoint& pos, bool addToSelection = false);
};

QDebug operator<<(QDebug qd, const Canvas::ToolMode &mode);
QDebug operator<<(QDebug qd, const Canvas::Abort &abort);

#endif // CANVAS_H
