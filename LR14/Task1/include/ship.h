#ifndef SHIP_H
#define SHIP_H

struct Ship {
    int crewSize;
    double displacement;
    char shipClass;
    bool isActive;
    static constexpr int maxNameSize = 50;
    static constexpr int maxLevelsSize = 5;
    char name[maxNameSize];
    int cargoWeights[maxLevelsSize];
    inline static constexpr char validClasses[] = "ABCDE";
};

#endif