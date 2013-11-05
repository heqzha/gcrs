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

#ifndef GCRSBASECOMNIN_H_
#define GCRSBASECOMNIN_H_
/*
 * Network Identification Number
 */
class GCRSBaseComNin {
public:
    typedef long NinL3Type;
    static const NinL3Type NINL3NULL;
public:
    static inline bool isNinL3NULL(const NinL3Type& nin) {
        return nin == NINL3NULL;
    }
};

#endif /* GCRSBASECOMNIN_H_ */
