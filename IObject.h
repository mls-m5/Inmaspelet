/*
 * IObject.h
 *
 *  Created on: 15 nov 2014
 *      Author: Mattias Larsson Sköld
 */

#pragma once

namespace Space {

class IObject {
public:
	virtual ~IObject(){};

	virtual void draw() = 0;
	virtual void update(double t) = 0;
};

} /* namespace Space */
