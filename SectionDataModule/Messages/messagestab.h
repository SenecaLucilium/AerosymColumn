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
    explicit MessagesTab(QWidget *parent = nullptr);
    ~MessagesTab();

    void clearMessages();
    void updateInformation(std::vector<std::vector<std::pair<int, QString>>>& messages);

private:
    void addMessage(const QString& message, int messageLevel);
    QString messageToHTML (const QString& message, int messageLevel);

    QTextEdit* textEdit;
    QVBoxLayout* layout;
    QMap <int, QString> levelStyles;
};

#endif // MESSAGESTAB_H
