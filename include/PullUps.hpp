#pragma once
#include "Exercise.hpp"

/**
 * @brief  definition of derived PullUps class, one of the exercise
 */

namespace gm{
class PullUps : public Exercise {
private:
    int m_reps; 

public:
    /**
    * @brief parametrized constuctor
    */
    PullUps(int sets, int reps, double weight, std::string comment) : Exercise("Pull ups", "Biceps, back", sets, weight, comment, false), m_reps(reps){
        if (m_reps <= 0){ 
            m_error = true;

        }
    }
    /**
     * @brief default constructor
     */
    PullUps():
        Exercise(),
        m_reps(0)
    {

    }
    /**
     * override method from base class with own values
     */
    double calc_volume() const override {
        if (m_weight > 0) {
        return m_sets * m_reps * m_weight;
        }
        else {
        return m_sets * m_reps;
        } 
    }
    /**
     * @brief add "reps" field to json file
     */
    json toJson() const override {
        json data = Exercise::toJson();
        data["reps"] = m_reps;
        return data;
    }
    };
}