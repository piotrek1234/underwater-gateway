#include "frameparser.h"

FrameParser::FrameParser(QObject *parent) : QObject(parent)
{

}

FrameParser::~FrameParser()
{

}

void FrameParser::addHandler(Handler *handler)
{
    handlers.insert(QString(handler->handlerType()), handler);
    QObject::connect(handler, SIGNAL(response(QStringList)), this, SLOT(buildFrame(QStringList)));
    QObject::connect(handler, SIGNAL(error(QString)), this, SLOT(buildErrorFrame(QString)));
}

Handler *FrameParser::getHandler(char type)
{
    auto it = handlers.find(QString(type));
    if(it != handlers.end())
        return it.value();
    return nullptr;
}

void FrameParser::parseFrame(QString frame)
{
    QStringList args = frame.split(",", QString::KeepEmptyParts);

    // echo request
    if(args.at(0) == QString(Frame::FRAME_TYPE_ECHO))
    {
        buildFrame(QStringList() << "alive");
        return;
    }

    if(args.length() < 2)
    {
        buildErrorFrame("Incomplete frame (only one element)");
        return;
    }

    Handler* handler;
    auto it = handlers.find(args.at(1));
    if(it == handlers.end())
    {
        buildErrorFrame("No known handler for type: "+args.at(1));
        return;
    }
    else
        handler = it.value();

    if(args.at(0) == QString(Frame::FRAME_TYPE_GET))
    {
        args.erase(args.begin(), args.begin()+2);
        handler->get(args);
    }
    else if(args.at(0) == QString(Frame::FRAME_TYPE_SET))
    {
        args.erase(args.begin(), args.begin()+2);
        handler->set(args);
    }
    else
        buildErrorFrame("Invalid frame type (required "+QString(Frame::FRAME_TYPE_GET)+\
                        " or "+QString(Frame::FRAME_TYPE_SET)+")");
}

void FrameParser::buildFrame(QStringList args)
{
    QString frame = "";
    frame += Frame::FRAME_START;
    frame += Frame::FRAME_TYPE_RESPONSE;
    frame += Frame::FRAME_SEPARATOR;
    frame += args.join(",");
    frame += Frame::FRAME_END;

    emit sendFrame(frame);
}

void FrameParser::buildErrorFrame(QString content)
{
    QString frame = "";
    frame += Frame::FRAME_START;
    frame += Frame::FRAME_TYPE_ERROR;
    frame += Frame::FRAME_SEPARATOR;
    frame += content;
    frame += Frame::FRAME_END;

    emit sendFrame(frame);
}

void FrameParser::printFrame(QString frame)
{
    std::cout << frame.toStdString() << std::endl;
}

