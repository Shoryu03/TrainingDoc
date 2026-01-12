#pragma once
#include "Exercise.hpp"
/**
 * @brief  definition of derived Dips class, one of the exercise
 */
namespace gm {

class Custom : public Exercise {
private:
    int m_reps;
    int m_time;
    double m_volume_coef;

public:
/**
 * @brief parametrized constuctor
 */
    Custom(std::string name, std::string info, int sets, int reps, double weight, int time, double volume_coef,  std::string comment) : Exercise(name, info, sets, weight, comment, false), m_reps(reps), m_time(time), m_volume_coef(volume_coef) {
        if (m_reps < 0 || m_time < 0 || m_volume_coef <= 0 || (m_reps > 0 && m_time > 0)) {
            m_error = true;
        }
    }
    /**
     * @brief default constructor
     */
    Custom():
    
        Exercise(),
        m_reps(0),
        m_time(0),
        m_volume_coef(0.0){
        }
    /**
     * override method from base class with own values
     */
    double calc_volume() const override {
        if (m_time > 0 && m_reps == 0) {
            if (m_weight == 0) {
                return m_sets * m_time * m_volume_coef;
            }
            else {
            return m_sets * m_time * m_weight * m_volume_coef;
            }
        } else if (m_time <= 0 && m_reps > 0){
            if (m_weight == 0) {
            return m_sets * m_reps * m_volume_coef;
            } else {
            return m_sets * m_reps * m_weight * m_volume_coef;
            }
        } return 0.0;   
    }
    /**
     * @brief add "reps" field to json file, depends on what value has been given
     */
    json toJson() const override {
        json data = Exercise::toJson();
        if(m_reps > 0) {
            data["reps"] = m_reps;
        }
        if (m_time > 0) {
            data["time"] = m_time;
        }
        return data;

    }
};
}