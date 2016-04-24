/*Author: Zane Draper
 * 
 *Purpose: Creates the movable game piece bases and attributes
 *
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MileStone4
{
    public abstract class MovableGamePiece: GamePiece
    {
        //attributes
        private int direction;


        //properties
        public int Direction { get { return direction; } set { direction = value; } }

        //constructor calls base constructor to set location and image
        public MovableGamePiece(int x, int y, string imgFile)
            : base(x, y, imgFile)
        {
            direction = 0;
        }

        //allows move method for none abstract inheriting class
        public abstract void Move();

        //overrides to show direction
        public override string ToString()
        {
            return "Direction: " + direction.ToString() + " " + base.ToString();
        }
    }
}
