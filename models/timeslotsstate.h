//
// Created by Dmitry Khrykin on 2019-07-05.
//

#ifndef MODELS_TIMESLOTSSTATE_H
#define MODELS_TIMESLOTSSTATE_H

#include <vector>

#include "timeslot.h"
#include "privatelist.hpp"
#include "notifiableonchange.h"
#include "streamablelist.h"

class TimeSlotsState :
        public PrivateList<TimeSlot>,
        public NotifiableOnChange,
        public StreamableList<TimeSlotsState> {
public:
    using Time = TimeSlot::Time;
    using Duration = TimeSlot::Duration;
    using StateSize = unsigned;

    TimeSlotsState(Time startTime,
                   Duration slotDuration,
                   StateSize numberOfSlots);

    explicit TimeSlotsState(std::vector<TimeSlot> fromVector);

    Time beginTime() const;
    void setBeginTime(Time beginTime);

    Duration slotDuration() const;
    void setSlotDuration(Duration slotDuration);

    StateSize numberOfSlots() const;
    void setNumberOfSlots(StateSize newNumberOfSlots);

    void setActivityAtIndices(const Activity *activity,
                              const std::vector<Index> &indices);

    void fillSlots(Index fromIndex, Index tillIndex);

    void populateVector(Time startTime, StateSize numberOfSlots);

    iterator findSlotWithActivity(const Activity *activity);

    void removeActivity(const Activity *activity);

    void editActivity(const Activity *oldActivity,
                      const Activity *newActivity);

    bool hasActivity(const Activity *activity);

    TimeSlotsState &operator=(const TimeSlotsState &newState);

    std::string classPrintName() const override;
private:
    Time _beginTime = 0;
    Duration _slotDuration = 0;

    void setActivityAtIndex(const Activity *activity,
                            Index slotIndex);


    Time slotBeginTime(Time globalBeginTime, Index slotIndex);
};


#endif //MODELS_TIMESLOTSSTATE_H
