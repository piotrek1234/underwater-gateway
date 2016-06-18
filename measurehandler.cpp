#include "measurehandler.h"

MeasureHandler::MeasureHandler(int interval)
{
    timer.setInterval(interval);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateMeasures()));
    timer.start();
}

void MeasureHandler::get(QStringList frame)
{
    if(frame.length() == 2)
    {
        char type = frame.at(0).at(0).toLatin1();
        auto vec = measures.find(type);
        if(vec == measures.end())
        {
            emit error("No such measure");
            return;
        }
        if(vec.value().size() == 0)
        {
            emit error("No measures for given type");
            return;
        }

        int index = frame.at(1).toInt();
        if(index >= vec.value().size() || index < 0)
        {
            emit error("Measure index out of range");
            return;
        }
        //-----------------
        //vec.value().at(index)->update();
        //-----------------
        double value = vec.value().at(index)->get();
        emit response(QStringList() << QString(handlerType()) << QString(type) << QString::number(index) << QString::number(value));

    }
    else
        emit error("Arguments count not valid");
}

void MeasureHandler::set(QStringList frame)
{
    if(frame.length() == 2)
    {
        if(frame.at(0) == "dt")
        {
            timer.setInterval(frame.at(1).toInt());
            emit response(QStringList() << QString(handlerType()) << "dt" << QString::number(timer.interval()));
            return;
        }
    }
    else
    {
        emit error("Measure::set - zla liczba argumentow");
    }
}

QString MeasureHandler::description()
{

}

void MeasureHandler::addMeasure(char type, Measure *measure)
{
    auto vec = measures.find(type);
    if(vec == measures.end())
    {
        vec = measures.insert(type, QVector<Measure*>());
    }
    vec.value().push_back(measure);
}

void MeasureHandler::updateMeasures()
{
    for(auto it = measures.begin(); it != measures.end(); ++it)
    {
        for(int i = 0; i<it.value().size(); ++i)
        {
            it.value().at(i)->update();
        }
    }
}
