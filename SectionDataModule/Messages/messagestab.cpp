#include "messagestab.h"

MessagesTab::MessagesTab(QWidget *parent)
    : QWidget{parent}
{
    levelStyles[0] = "color: blue;";
    levelStyles[1] = "color: orange;";
    levelStyles[2] = "color: red;";

    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(textEdit);
    setLayout(layout);
}

void MessagesTab::addMessage (const QString &message, int messageLevel)
{
    textEdit->append(messageToHTML(message, messageLevel));
}

QString MessagesTab::messageToHTML (const QString &message, int messageLevel)
{
    QString style = levelStyles.value(messageLevel);
    return QString("<span style=\"%1\">%2</span>").arg(style).arg(message);
}

void MessagesTab::updateInformation(std::vector<std::vector<std::pair<int, QString>>>& messages)
{
    for (auto& message : messages) {
        for (auto& msg : message) {
            addMessage(msg.second, msg.first);
        }
    }
}

MessagesTab::~MessagesTab() {}
