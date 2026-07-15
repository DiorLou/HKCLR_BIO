#ifndef PINYINHELPER_H
#define PINYINHELPER_H

#include <QLabel>
#include <QStringList>
class frmInput;

class PinYinHelper : public QObject
{
    Q_OBJECT
public:
    explicit PinYinHelper(QObject *parent = 0);

    //获取当前鼠标所在屏幕索引+尺寸
    static QList<QRect> getScreenRects(bool available);
    static int getScreenIndex();
    static QRect getScreenRect(bool available = true);

private:
    frmInput *input;

    //当前拼音索引
    int pinyinIndex{0};
    //当前显示的汉字标签的数量
    int pinyinCount{0};
    //所有拼音链表
    QStringList pinyinAll;
    //拼音字母
    QString pinyin;

    //固定数量汉字标签数组(硬键盘展示用)
    QList<QLabel *>labCh;
    //顶部汉字标签数组
    QList<QLabel *>labCn;
    //更多汉字标签数组
    QList<QLabel *>labMore;

public:
    void setInput(frmInput *input);
    void setLabs(QList<QLabel *>labCh, QList<QLabel *>labCn, QList<QLabel *>labMore);
    int getCount();

    //移动到合适的位置
    void movePosition();

    //插入汉字
    bool appendChinese(const QString &text, bool insert);
    //查询汉字
    void selectChinese(const QString &pinyin);

    //显示+隐藏+清空 汉字
    void showChinese();
    QString getText(const QString &text);
    void hideChinese();
    void clearChinese();

    //上下翻页显示汉字
    void showPrevious();
    void showNext();

    //计算当前汉字长度自动隐藏标签
    void checkChinese(const QString &pinyin);
    void setChVisible(int index);
};

#endif // PINYINHELPER_H
