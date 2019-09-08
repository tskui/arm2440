#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QThread>
#include <QDataStream>
#include <unistd.h>
#include <QDebug>
struct HEX{
     quint32 length;
     quint32 offsetaddr[2];
     quint32 type;
     char data[256];
     quint32 chexsum;
};
extern quint8 Member[1024*4];
QDir dir;
QFile filenand("./flash/nand.flash");
QFile filenor("./flash/nor.flash");
void newflash(){
    bool flag=dir.mkdir("./flash");
    if(!flag){
        //printf("wenjian exit\n");
        filenand.open(QIODevice::WriteOnly);
        filenor.open(QIODevice::WriteOnly);
    }
    else{
        //printf("xinjian wen jin\n");
        filenand.open(QIODevice::WriteOnly);
        filenor.open(QIODevice::WriteOnly);
    }
    filenor.close();
    filenand.close();
}
quint32  download(QString namefile){

    QFile file(namefile);
    if (!file.open(QIODevice::ReadOnly))
    {   qDebug()<<"fail 、\n";
        return 0;
    }
    if (!filenand.open(QIODevice::WriteOnly))
    {   qDebug()<<"fail filenand、\n";
        return 0;
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_1);
    QDataStream out(&filenand);
    out.setVersion(QDataStream::Qt_5_1);
    quint32 i=0,j=3,n=0;
    memset(Member,0,1024*4);
    char buffer[4];
    while (!file.atEnd()) {
            n+=in.readRawData(buffer,4*sizeof(quint8));
            out.writeRawData((char*)&buffer[3],sizeof(quint8));
            out.writeRawData((char*)&buffer[2],sizeof(quint8));
            out.writeRawData((char*)&buffer[1],sizeof(quint8));
            out.writeRawData((char*)&buffer[0],sizeof(quint8));}

    file.close();
    filenand.close();
    return n;
}
void downloadhex(QString namefile){
         if (!filenand.open(QIODevice::WriteOnly))
            {   qDebug()<<"fail 、\n";
                return ;
            }
            QDataStream out(&filenand);
            out.setVersion(QDataStream::Qt_5_1);
            memset(Member,0,1024*4);
            QFile file(namefile);
            bool flag=file.open(QIODevice::ReadOnly);
            if(flag){
                qDebug()<<"ok";
                quint32 baseaddr=0;
                HEX hex;
                do{
                   char str[256];
                   file.readLine(str,256);
                   //printf("%s",str);
                   if(str[0]==0x3a){
                       int len=strlen(str);
                       for(int i=1;i<len;i++){
                           if(str[i]>='A'&&str[i]<'G'){
                               str[i]=str[i]-'A'+10;}
                           else if(str[i]>='a'&&str[i]<'g'){
                               str[i]=str[i]-'a'+10;}
                           else{
                               str[i]=str[i]-'0';
                           }
                       }

                       hex.length=((str[1])<<4)+(str[2]);

                       hex.offsetaddr[0]=((str[3])<<4)+(str[4]);
                       hex.offsetaddr[1]=((str[5])<<4)+(str[6]);

                       hex.type=((str[7])<<4)+(str[8]);

                       for(int i=0;i<hex.length;i++){
                           hex.data[i]=((str[9+i*2])<<4)+(str[10+i*2]);
                       }
                       hex.chexsum=((str[hex.length*2+9])<<4)+(str[hex.length*2+10]);
                       /*printf("leng:%x offset:%x%x type:%x chesum:%x\n",
                              hex.length,
                              hex.offsetaddr[0],hex.offsetaddr[1],
                              hex.type,
                              hex.chexsum);*/
                       switch (hex.type) {
                       case 0:
                           quint32 base;
                           base=(baseaddr<<16)+(hex.offsetaddr[0]<<8)+(hex.offsetaddr[1]);
                           //printf("base=%x\n",base);
                           for(int i=0;i<hex.length;i=i+4){
                               out.writeRawData((char*)&hex.data[i+3],sizeof(quint8));
                               out.writeRawData((char*)&hex.data[i+2],sizeof(quint8));
                               out.writeRawData((char*)&hex.data[i+1],sizeof(quint8));
                               out.writeRawData((char*)&hex.data[i+0],sizeof(quint8));
                           }
                           //printf("\n");

                           break;
                       case 1:
                           file.close();
                           filenand.close();
                           return;
                       case 2:

                           break;
                       case 3:

                           break;
                       case 4://base
                           baseaddr=0;
                           for(int i=0;i<hex.length;i++){
                               baseaddr=baseaddr<<8;
                               baseaddr+=hex.data[i];
                           }
                           break;
                       case 5:

                           break;
                       default:
                           break;
                       }

                   }
                }while(!file.atEnd());
            }
}
quint32 loadcode(){
        if (!filenand.open(QIODevice::ReadOnly))
        {   qDebug()<<"fail 、\n";
            return 0;
        }
        QDataStream in(&filenand);
        in.setVersion(QDataStream::Qt_5_1);
        quint32 i=0,n=0;
        while (!filenand.atEnd()) {
            n+=in.readRawData((char*)&Member[i++],sizeof(quint8));
              }
        //printf("%d\n",n);
        filenand.close();
        return n;

}




