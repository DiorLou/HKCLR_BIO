#pragma once

#include<QString>
#include<QStringList>
#include<QDebug>

class CubeSize
{
public:
    CubeSize()
    {
        m_length = 0.0;
        m_width = 0.0;
        m_height = 0.0;
    }

    CubeSize(const double &length, const double &width, const double &height)
    {
        m_length = length;
        m_width = width;
        m_height = height;
    }
    CubeSize(const CubeSize &other)
    {
        m_length = other.m_length;
        m_width = other.m_width;
        m_height = other.m_height;
    }

    CubeSize &operator=(const CubeSize &other)
    {
        m_length = other.m_length;
        m_width = other.m_width;
        m_height = other.m_height;
        return (*this);
    }

    bool operator==(const CubeSize &other) const
    {
        bool a = fabs(this->m_length - other.m_length) < 0.000001;
        bool b = fabs(this->m_width - other.m_width) < 0.000001;
        bool c = fabs(this->m_height - other.m_height) < 0.000001;
        return a && b && c;
    }

    double length()const{
        return  m_length;
    }
    void length(const double &length){
        m_length = length;
    }

    double width()const{
        return  m_width;
    }
    void width(const double &width){
        m_width = width;
    }

    double height()const{
        return  m_height;
    }
    void height(const double &height){
        m_height = height;
    }

    static QString CubeSize2String(const CubeSize &size){
        return QString("%1,%2,%3")
            .arg(QString::number(size.m_length, 'f', 6))
            .arg(QString::number(size.m_width, 'f', 6))
            .arg(QString::number(size.m_height, 'f', 6));
    }

    static CubeSize String2CubeSize(const QString &str){
        CubeSize size;
        QStringList sizeStrList = str.split(",", Qt::SkipEmptyParts);
        size.m_length = sizeStrList.at(0).toDouble();
        size.m_width = sizeStrList.at(1).toDouble();
        size.m_height = sizeStrList.at(2).toDouble();
        return size;
    }


private:
    double m_length;
    double m_width;
    double m_height;

};
