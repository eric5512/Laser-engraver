#include <MovementHelper.h>

MovementHelper* MovementHelper::get_instance() {
    static MovementHelper mh;

    return &mh;
}

bool MovementHelper::move(const Motor& mot, const Direction& dir, const coord_t qty) {
    switch (mot) {
    case MOT_X:
        return this->motor_x.move_mm(dir, qty);
    case MOT_Y:
        return this->motor_y.move_mm(dir, qty);
    case MOT_Z:
        return this->motor_z.move_mm(dir, qty);
    }

    return false;
}

bool MovementHelper::move(const Motor& mot, const coord_t coord) {
    DRV8822_IF *moti;
    switch (mot) {
    case MOT_X:
        moti = &this->motor_x;
        break;
    case MOT_Y:
        moti = &this->motor_y;
        break;
    case MOT_Z:
        moti = &this->motor_z;
        break;
    }

    Direction dir;
    coord_t qty;
    if (moti->pos > coord) {
        dir = CCW;
        qty = moti->pos - coord;
    } else {
        dir = CW;
        qty = coord - moti->pos;
    }
    
    return moti->move_mm(dir, qty);
}

bool MovementHelper::move(const Point& point) {
    if (!this->move(MOT_X, point.x)) 
        return false;

    if (!this->move(MOT_Y, point.y)) 
        return false;

    if (!this->move(MOT_Z, point.z)) 
        return false;

    return true;
}

void MovementHelper::origin() {
    while (!this->final_x())
        this->motor_x.move(CCW);
    for (coord_t i = 0; i < TICS_TO_MM_X; i++)
        this->motor_x.move(CW);

    while (!this->final_y())
        this->motor_y.move(CCW);
    for (coord_t i = 0; i < TICS_TO_MM_Y; i++)
        this->motor_y.move(CW);

    while (!this->final_z())
        this->motor_z.move(CW);
    for (coord_t i = 0; i < TICS_TO_MM_Z; i++)
        this->motor_z.move(CCW);

    delay(500); // Delay because the button is connected to the same pin
    coord_t ticks_z = 0, size_z = 0;
    
    while (!this->final_z()) {
        this->motor_z.move(CCW);
        ticks_z++;
        if (ticks_z >= TICS_TO_MM_Z) {
            ticks_z = 0;
            size_z++;
        }
    }
    
    for (coord_t i = 0; i < TICS_TO_MM_Z; i++)
        this->motor_z.move(CW);

    this->motor_z.max_pos = size_z;

    this->motor_x.pos = 0;
    this->motor_y.pos = 0;
    this->motor_z.pos = 0;
}

bool MovementHelper::final_x() {
    return this->motor_x.final_mot();
}

bool MovementHelper::final_y() {
    return this->motor_y.final_mot();
}

bool MovementHelper::final_z() {
    return this->motor_z.final_mot();
}

void MovementHelper::motor_pos(Point& p) {  
    p.x = this->motor_x.pos;
    p.y = this->motor_y.pos;
    p.z = this->motor_z.pos;
}

#undef MOV_DELAY_X
#undef MOV_DELAY_Y
#undef MOV_DELAY_Z
#undef TICS_TO_MM_X
#undef TICS_TO_MM_Y
#undef TICS_TO_MM_Z