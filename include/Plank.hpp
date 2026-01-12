#pragma once
#include "Exercise.hpp"
/**
 * @brief  definition of derived Plank class, one of the exercise
 */

namespace gm {
class Plank : public Exercise {
private:
    int m_time; 

public:
/**
 * @brief parametrized constructor
 */
    Plank(int sets, int time, double weight, std::string comment) : Exercise("Plank", "Abdominal", sets, weight, comment, false), m_time(time) {
        if (m_time <= 0){ 
            m_error = true;

        }
    }
    /**
     * @brief default constructor
     */
    Plank():
        Exercise(),
        m_time(0)
        {

        }
    /**
     * override method from base class with own values
     */
    double calc_volume() const override {
        if (m_weight > 0 && m_time > 0) {
        return m_sets * m_time * m_weight;
        }
        else if (m_time > 0) {
        return m_sets * m_time;
        }
        return 0;
    }
    
    /**
     * @brief add "time" field to json file
     */
    json toJson() const override {
        json data = Exercise::toJson();
        data["time"] = m_time;
        return data;
    }
};
}