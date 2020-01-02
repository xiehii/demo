﻿#ifndef SQLITECLASS_H
#define SQLITECLASS_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>

#define SCDebug  qDebug() <<"[Debug]["<<__FILE__<<"]$"<<0<<"$"<<"["<<__LINE__<<"]["<<__FUNCTION__ <<"]:"
#define SCInfo  qInfo() <<"[Info]["<<__FILE__<<"]$"<<0<<"$"<<"["<<__LINE__<<"]["<<__FUNCTION__<<"]:"
#define SCWarning  qWarning()<<"[Warning][" <<__FILE__<<"]$"<<0<<"$"<<"["<<__LINE__<<"]["<<__FUNCTION__<<"]:"
#define SCritical  qCritical() <<"[Error]["<<__FILE__<<"]$"<<0<<"$"<<"["<<__LINE__<<"]["<<__FUNCTION__<<"]:"

class ProtocolClass{
public:
    ProtocolClass(){}
    ~ProtocolClass(){

        ReqValueReqMap.clear();
        ReqValueReqDescriptionMap.clear();
        ReqValuePortMap.clear();
    }

    /**
     * @brief addData - 获取数据库中API的编号、端口号及其中英文的描述
     * @param reqValue - API编号
     * @param port - API对应的端口号
     * @param req - API名称（英文描述）
     * @param reqDescription - API的中文描述
     */
    void addData(
            int reqValue,
            int port,
            const QString & req,
            const QString & reqDescription)
    {
        ReqValueReqMap.insert(reqValue,req);
        ReqValueReqDescriptionMap.insert(reqValue,reqDescription);
        ReqValuePortMap.insert(reqValue,port);
    }

    /**
     * @brief getReqDescription - 根据数据库中 reqValue 获取数据库中 reqDescription 字段
     * @param reqValue - 索引值
     * @return
     */
    QString getReqDescription(int reqValue) const {
        return ReqValueReqDescriptionMap.value(reqValue);
    }

    /**
     * @brief getReq - 根据数据库中 reqValue 获取数据库中 req 字段
     * @param reqValue - 索引值
     * @return
     */
    QString getReq(int reqValue) const {
        return ReqValueReqMap.value(reqValue);
    }

    /**
     * @brief getPort - 根据数据库中 reqValue 获取数据库中 port 字段
     * @param reqValue - 索引值
     * @return
     */
    int getPort(int reqValue) const {
        return ReqValuePortMap.value(reqValue);
    }

    //QMap<reqValue, req>
    QMap<int,QString> ReqValueReqMap;
    //QMap<reqValue, reqDescription>
    QMap<int,QString> ReqValueReqDescriptionMap;
    //QMap<reqValue, port>
    QMap<int,int> ReqValuePortMap;

};

class SqliteClass : public QObject
{
    Q_OBJECT
public:
    explicit SqliteClass(QObject *parent = nullptr);
    ~SqliteClass();

    /**
     * @brief errorString - 获取错误描述
     * @return
     */
    QString errorString() const;

    /**
     * @brief setErrorString - 设置错误描述
     * @param errorString - 错误描述字符串
     */
    void setErrorString(const QString &errorString);

    /**
     * @brief dbConnection - 打开数据库
     * @return
     */
    QSqlDatabase dbConnection();

    /**
     * @brief createConnection - 连接数据库
     * @param filePath - 数据库文件所在的路径
     * @return
     */
    bool createConnection(const QString &filePath);

    ProtocolClass *queryProtocol();
    ProtocolClass *getProtocol();
signals:

public slots:
private:
    QString _connectionName; //连接 db 名(用于多个db库访问时)
    QString _errorString;
    ProtocolClass * _pProtocolClass  = Q_NULLPTR;
};

#endif // SQLITECLASS_H
