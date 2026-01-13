    #pragma once
    gm {
    /**
     * @brief function that returns current system date
     * 
     */

        std::string get_date(){
        time_t timestamp = time(&timestamp);
        struct tm datetime = *localtime(&timestamp);

    

    /**
     * convert date (int) to string
     */
        return std::to_string(datetime.tm_mday) + "-" + std::to_string(datetime.tm_mon + 1) + "-" + std::to_string(datetime.tm_year + 1900); 
        }
}