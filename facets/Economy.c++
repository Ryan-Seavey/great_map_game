//
// Created by diogenes on 4/25/25.
//

#include "Economy.h++"

#include "../RyUtil.h++"


Economy::Economy():
unemployment_{RyUtil::random(0.f,100.f)},
inflation_{RyUtil::random(0.00f,100.f)},
GDP_{1},
willingness_to_invest_{RyUtil::random(0.f,100.f)},
poverty_rate_{RyUtil::random(0.00f,1.00f)},
population_{RyUtil::random(1e6f,1e9f)}
{
}
