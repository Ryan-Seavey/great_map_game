//
// Created by diogenes on 4/17/25.
//

#ifndef MILITARY_H
#define MILITARY_H



struct Military {
    //Hypothetical
    float war_weariness_percent_ = 0;
    float logistic_efficiency_percent_= 100;
    float high_command_competency_percent_ = 100;
    //General
    float fuel_ = 0;
    unsigned manpower_;
    float rations = 0;
    //Ground
    unsigned infantry_;
    unsigned infantry_equipment_;
    unsigned tanks_;
    unsigned trucks_;
    //Sea
    unsigned screens_ = 0;
    unsigned battleships_ = 0;
    unsigned carriers_ = 0;
    //Air
    unsigned fighters_ = 0;
    unsigned CAS_ = 0;
    //WMD
    unsigned ICBMs_ = 0;
    unsigned nukes_ = 0;
    unsigned wunderwaffe_ = 0;

    static bool doBattle(Military& def, Military& atk);
};



#endif //MILITARY_H
