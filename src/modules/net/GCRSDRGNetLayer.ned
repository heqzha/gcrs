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

package gcrs.src.modules.net;

import gcrs.src.base.net.GCRSBaseNetLayer;

simple GCRSDRGNetLayer extends GCRSBaseNetLayer{
	parameters:
		double MAXBOD = default(0.01s) @unit(s);
		double LONGBOD = default(2.5s) @unit(s);
		int MAXRETX = default(2);
		double MINCW = default(0.0 s) @unit(s);
		double MAXCW = default(0.002 s) @unit(s);
		double SD = default(1.0);
		double EPSILON = default(0.5);
		double MAXCRITERIONANGLE = default(135 degree) @unit(degree);
		int MAXMESSAGEBUFFERSIZE = default(30);
    	@class(GCRSDRGNetLayer);
}