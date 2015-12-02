/*
 * Copyright (C) 2015 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UNITY_WINDOWINPUTMONITOR_H
#define UNITY_WINDOWINPUTMONITOR_H

#include <QQuickItem>
#include <QPointer>

#include "Timer.h"
#include "ElapsedTimer.h"

/*
  Signals when the home key seems to be have been intentionally tapped.

  It only says the home key has been activated if it has been tapped in isolation,
  that is, without being accompanied by touches on the screen. Home key taps that
  happen along with (or immediately after, or immediately before) touches on the
  screen are considered to have happened unintentionally and are thus ignored.

  Rationale being that it's easy to accidentally hit the home key while performing
  a swipe from a screen edge, for instance. That's particularly the case when the
  home key is a capacitive key.

  Additionally, this class monitors for generic touch events on the screen, to
  help with hiding/revealing the mouse pointer.
 */
class WindowInputMonitor : public QQuickItem
{
    Q_OBJECT
public:

    WindowInputMonitor(QQuickItem *parent = 0);

    // for testing
    WindowInputMonitor(UnityUtil::AbstractTimer *timer,
            UnityUtil::AbstractElapsedTimer *elapsedTimer,
            QQuickItem *parent = 0);

    virtual ~WindowInputMonitor();

    bool eventFilter(QObject *watched, QEvent *event) override;

    void update(QEvent *event);

    const qint64 msecsWithoutTouches = 150;

Q_SIGNALS:
    // Emitted when the home key has been intentionally tapped
    void homeKeyActivated();

    void touchBegun();
    void touchEnded(const QPointF &pos);

private Q_SLOTS:
    void setupFilterOnWindow(QQuickWindow *window);
    void emitActivatedIfNoTouchesAround();

private:
    QPointer<QQuickWindow> m_filteredWindow;
    bool m_windowBeingTouched;
    bool m_homeKeyPressed;
    UnityUtil::AbstractElapsedTimer *m_windowLastTouchedTimer;
    UnityUtil::AbstractTimer *m_activationTimer;
};

#endif // UNITY_WINDOWINPUTMONITOR_H
