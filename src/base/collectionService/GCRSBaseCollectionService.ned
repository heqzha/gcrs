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

package gcrs.src.base.collectionService;

simple GCRSBaseCollectionService{
    parameters:
        string PROTOCOL = default("");
        int ZOR_SHAPE = default(1);
        double ZOR_LENGTH = default(500);
        double ZOR_WIDTH = default(500);
        int ZOF_SHAPE = default(1);
        double ZOF_LENGTH = default(650);
        double ZOF_WIDTH = default(500);
        double LANE_WIDTH = default(0.0);
        int LANE_NUM = default(2);
        double BUILDINGINTERVAL = default(0.0);
        double UPDATEINTERVAL @unit(s)= default(0.1s);
        @class(GCRSBaseCollectionService);   
}