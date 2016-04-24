/*Author: Zane Draper
 * 
 *Purpose: Creates the walls
 *
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MileStone4
{
    class Wall : GamePiece
    {
        //constructor - calls base constructor to set location
        public Wall(int x, int y) : base(x, y, GameVariables.WallImage) { }


        //over ride to add on object type
        public override string ToString()
        {
            return "Wall: " + base.ToString();
        }
    }
}
