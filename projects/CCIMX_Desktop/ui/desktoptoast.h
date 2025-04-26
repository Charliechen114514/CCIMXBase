#ifndef DESKTOPTOAST_H
#define DESKTOPTOAST_H
#include <QPointer>
#include <QWidget>
class QLabel;
class QPropertyAnimation;
class DesktopToast : public QWidget
{
    Q_OBJECT
public:
    explicit    DesktopToast(QWidget *parent = nullptr);
    void        set_message(const QString& message);
signals:

private:
    void        adjust_place();
    void        start_animation();
    void        start_close_animation();
    QLabel*     label;
    QPoint      startPos, endPos;
    int         animation_maintain_msec{400};
    QPointer<QPropertyAnimation> moveAnimation{nullptr};
    QPointer<QPropertyAnimation> fadeAnimation{nullptr};
    bool isOpening{false};
    bool isClosing{false};
};

#endif // DESKTOPTOAST_H
