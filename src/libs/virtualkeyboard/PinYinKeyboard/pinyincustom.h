#ifndef PINYINCUSTOM_H
#define PINYINCUSTOM_H

#include <QObject>
class frmInput;

class PinYinCustom : public QObject
{
    Q_OBJECT
public:
    explicit PinYinCustom(QObject *parent = 0);

private:
    frmInput *input;

public slots:
    void setInput(frmInput *input);

    //读取词库文件
    void readChinese();
    void readChinese(const QString &fileName, QStringList &key, QStringList &value);
    //保存当前选中汉字到文件
    void saveChinese(const QString &value, const QString &pinyin);
};

#endif // PINYINCUSTOM_H
