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
    else if(frame.length() == 4)
    {
        if(frame.at(0) == "o")
        {
            char type = frame.at(1).at(0).toLatin1();
            int number = frame.at(2).toInt();
            double value = frame.at(3).toDouble();

            auto m = measures.find(type);
            if(m != measures.end())
            {
                if(number < m.value().size())
                {
                    m.value().at(number)->setOffset(value);
                    emit response(QStringList() << QString(handlerType()) << "o" << QString(type) << \
                                  QString::number(number) << QString::number(value));
                    return;
                }
                else
                {
                    emit error("Measure::set (offset) Index out of range");
                    return;
                }
            }
            else
            {
                emit error("Measure::set (offset) Type not known");
                return;
            }
        }
        else if(frame.at(0) == "m")
        {

            char type = frame.at(1).at(0).toLatin1();
            int number = frame.at(2).toInt();
            double value = frame.at(3).toDouble();

            auto m = measures.find(type);
            if(m != measures.end())
            {
                if(number < m.value().size())
                {
                    m.value().at(number)->setMultiplier(value);
                    emit response(QStringList() << QString(handlerType()) << "m" << QString(type) << \
                                  QString::number(number) << QString::number(value));
                    return;
                }
                else
                {
                    emit error("Measure::set (multiplier) Index out of range");
                    return;
                }
            }
            else
            {
                emit error("Measure::set (multiplier) Type not known");
                return;
            }
        }
        else
        {
            emit error("Measure::set Args: 4, but not offset or multiplier");
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
    //todo
    return "Measure";
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
