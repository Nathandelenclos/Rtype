/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Animatable.hpp
*/

#pragma once

#include "../networking/shared/USocket.hpp"
#include "Drawable.hpp"
#include "IComponent.hpp"
#include <iostream>
#include <memory>
#include <sys/time.h>
#include <tuple>

class Animatable : public IComponentRType
{
  public:

    /**
     * @brief Construct a new Animatable:: Animatable object
     */
    Animatable();

    /**
     * @brief getAttribute, get the attribute
     *
     * @return attribute (char *)
     */
    [[nodiscard]] char *getAttribute() const override;

    /**
     * @brief setAttribute, set the attribute
     *
     * @param attribute
     */
    void setAttribute(std::string attribute) override;

    /**
     * @brief setTarget, set the target
     *
     * @param target
     */
    void setTarget(std::shared_ptr<Drawable> target);

    /**
     * @brief getTarget, get the target
     *
     * @return target (std::shared_ptr<Drawable>)
     */
    std::shared_ptr<Drawable> getTarget();

    /**
     * @brief setTime, set the time
     *
     * @param frametime
     */
    void setTime(timeval frametime);

    /**
     * @brief getTime, get the time
     *
     * @return timeval
     */
    timeval getTime();

    timeval _now;
    timeval _diff;
    timeval _chrono;
    int _numberFrameToAnim;
    int _frameIndex;
    int _numberFrame;
    int _startFrameIndex;
    int _frameForOnePicture;

  protected:
    std::shared_ptr<Drawable> sprite;
    timeval _frametime;
};
