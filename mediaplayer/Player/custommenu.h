#ifndef CUSTOMMENU_H
#define CUSTOMMENU_H

#include <QMenu>
#include <QHelpEvent>
#include <QToolTip>

class Menu : public QMenu {
    Q_OBJECT
public:
    Menu(const QString &t) : QMenu(t) { }
    bool event(QEvent *e)
    {
        const QHelpEvent *helpEvent = static_cast<QHelpEvent *>(e);
        if (helpEvent->type() == QEvent::ToolTip && activeAction() != 0) {
            QToolTip::showText(helpEvent->globalPos(), activeAction()->toolTip());
        } else {
            QToolTip::hideText();
        }
        return QMenu::event(e);
    }
};

#endif // CUSTOMMENU_H
