/*
* 2014 Valery Brasseur <vbrasseur@gmail.com>
*/

#ifndef RENDERTASK_SV_H
#define RENDERTASK_SV_H

#include <QtCore/QObject>
#include <QtCore/QTime>

#include "renderPreferences_sV.h"

class Project_sV;
class AbstractRenderTarget_sV;

#include <QObject>
#include <QMutex>

class RenderTask_sV : public QObject
{
    Q_OBJECT
    
public:
    RenderTask_sV(Project_sV *project);
    ~RenderTask_sV();

    /**
     * Requests the process to start
     *
     * It is thread safe as it uses #mutex to protect access to #_working variable.
     */
    void requestWork();
    /**
     *  Requests the process to abort
     *
     * It is thread safe as it uses #mutex to protect access to #_abort variable.
     */
    void abort();

    void setRenderTarget(AbstractRenderTarget_sV *renderTarget);
    void setTimeRange(qreal start, qreal end);
    void setTimeRange(QString start, QString end);

    /// Rendered frames per second
    Fps_sV fps() { return m_prefs.fps(); }
    /// Output frame resolution
    QSize resolution();

    RenderPreferences_sV& renderPreferences() { return m_prefs; }
    
private:
    /**
     *  true when Worker is doing work
     */
    bool _working;
    /**
     * Protects access to #_abort
     */
    QMutex mutex;
    
    Project_sV *m_project;
    RenderPreferences_sV m_prefs; ///< \todo Set preferences

    AbstractRenderTarget_sV *m_renderTarget;

    qreal m_timeStart;
    qreal m_timeEnd;

    QTime m_stopwatch;
    int m_renderTimeElapsed;

    bool m_initialized;
    bool m_stopRendering; //  Process is aborted when true
    qreal m_nextFrameTime;

    qreal m_prevTime;

signals:
    /**
     * This signal is emitted when the Worker request to Work
     * requestWork()
     */
    void workFlowRequested();
    /**
     * This signal is emitted when counted value is changed (every sec)
     */
    void valueChanged(const QString &value);
    /**
     * This signal is emitted when process is finished (or being aborted)
     */
    void finished();
    
public slots:
    void slotContinueRendering();
    void slotStopRendering();
    // was void doWorkFlow();

};

#endif // RENDERTASK_SV_H

