//
//  main.cpp
//  testsForMathLib
//
//  Created by Andrey on 01.08.16.
//  Copyright © 2016 Andrey. All rights reserved.
//

#include <iostream>

#include "/Users/Andrey/Documents/dev/Xcode Projects/mathLibMac0/rcbPlane.h"

bool testPlane(const rcbUnitVector3D& normal,
               const rcbVector3D& expected)
{
    rcbPlane plane(normal, rcbVector3D(0.0, 0.0, 1.0));
    
    rcbVector3D vc(1.0, 0.0, 1.0);
    
    rcbVector3D res = plane.projection(vc);
    
    bool good = true;
    
    good &= fabs(expected.getX() - res.getX()) < 0.01;
    good &= fabs(expected.getY() - res.getY()) < 0.01;
    good &= fabs(expected.getZ() - res.getZ()) < 0.01;
    good &= vc.square_norm() >= res.square_norm();
    
    return good;
}

int main(int argc, const char * argv[]) {
    
    bool test = true;
    
    test &= testPlane(rcbUnitVector3D::ort_z(), rcbVector3D(1.0, 0.0, 0.0));
    test &= testPlane(rcbUnitVector3D::ort_x(), rcbVector3D(0.0, 0.0, 1.0));
    test &= testPlane(rcbUnitVector3D::ort_y(), rcbVector3D(1.0, 0.0, 1.0));
    test &= testPlane(rcbUnitVector3D(1.0, 0.0, 1.0), rcbVector3D(0.0, 0.0, 0.0));
    test &= testPlane(rcbUnitVector3D(-1.0, 0.0, 1.0), rcbVector3D(1.0, 0.0, 1.0));
    test &= testPlane(rcbUnitVector3D(-1.0, 0.0, 2.0), rcbVector3D(1.2, 0.0, 0.6));
    
    if (!test)
    {
        std::cout << "FAILED, sorry :(\n";
    }
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
