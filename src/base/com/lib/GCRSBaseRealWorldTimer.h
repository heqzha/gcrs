//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef GCRSBASEREALWORLDTIMER_H_
#define GCRSBASEREALWORLDTIMER_H_
#include <ctime>

class GCRSBaseRealWorldTimer {
public:
    GCRSBaseRealWorldTimer();
    virtual ~GCRSBaseRealWorldTimer();

    static time_t calcDuration(time_t start, time_t end);
    static void convert(char* str_time, const int size, time_t t);
};

#endif /* GCRSBASEREALWORLDTIMER_H_ */
