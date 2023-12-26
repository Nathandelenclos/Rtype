//
// Created by talleux on 12/13/23.
//

#ifndef BOOTSTRAP_IGAME_HPP
#define BOOTSTRAP_IGAME_HPP

class IGame {
public:
    virtual ~IGame() = default;
    virtual void run() = 0;
};

#endif //BOOTSTRAP_IGAME_HPP
