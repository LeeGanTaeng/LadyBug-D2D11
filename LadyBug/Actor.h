#pragma once

#include "Framework/Collision.h"
#include "Framework/Vector.h"

#include "Object.h"

class Actor abstract : public Object
{
public:
    virtual void Validate(Vector<2> const & location) abstract;

    bool GetValid()
    {
        return Valid;
    }

protected:
    Collision::Component * Body = nullptr; 
    //�浹ü component ����
   

    bool Valid = false;
};