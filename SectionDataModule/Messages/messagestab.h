#ifndef MESSAGESTAB_H
#define MESSAGESTAB_H

#include <QWidget>

#include <QTextEdit>
#include <QVBoxLayout>
#include <QMap>

class MessagesTab : public QWidget
{
    Q_OBJECT
public:
    explicit MessagesTab(QWidget *parent = nullptr)
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
    ~MessagesTab() {}

    // void clearMessages() {}
    void updateInformation(std::vector<std::vector<std::pair<int, QString>>>& messages)
    {
        for (auto& message : messages) {
            for (auto& msg : message) {
                addMessage(msg.second, msg.first);
            }
        }
    }

private:
    void addMessage(const QString& message, int messageLevel)
    {
        textEdit->append(messageToHTML(message, messageLevel));
    }
    QString messageToHTML (const QString& message, int messageLevel)
    {
        QString style = levelStyles.value(messageLevel);
        return QString("<span style=\"%1\">%2</span>").arg(style).arg(message);
    }

    QTextEdit* textEdit;
    QVBoxLayout* layout;
    QMap <int, QString> levelStyles;
};

#endif // MESSAGESTAB_H
